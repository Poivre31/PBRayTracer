#include "TextureManager.h"
#include "Core/Log.h"

namespace Vega {

	void TextureManager::BindTextureSlot(Texture& image, GLSlot slot) {
		TextureData data = image.GetData();
		glBindImageTexture(slot.index, image.GetID(), 0, GL_FALSE, 0, GL_READ_WRITE, data.type);
		if (_slots.find(slot) == _slots.end()) {
			_slots.insert({ slot, &image });
		}
		else {
			Log::warn("Texture bound to already used slot, try to unbind used slot before binding new texture");
			_slots.at(slot) = &image;
		}
	}

	void TextureManager::UnbindTextureSlot(GLSlot slot) {
		if (_slots.find(slot) == _slots.end()) {
			Log::warn("Trying to unbind unused texture slot");
		}
		else {
			_slots.erase(slot);
		}
	}

	void TextureManager::UpdateTexture(Texture& texture, GLuint width, GLuint height) {
		TextureData data = texture.GetData();
		if (width == data.width && height == data.height) return;
		texture.Update(width, height);
		for (const auto& slot : _slots)
		{
			if (slot.second == &texture) {
				switch (slot.first.readMode) {
				case(TextureReadMode::Image): {
					glBindImageTexture(slot.first.index, texture.GetID(), 0, GL_FALSE, 0, GL_READ_WRITE, data.type);
					break;
				}
				case(TextureReadMode::Sampler): {
					glBindTextureUnit(slot.first.index, texture.GetID());
					break;
				}
				}
			}
		}
	}

	void TextureManager::DeleteTexture(Texture& texture) {
		texture.Delete();
		for (auto it = _slots.begin(); it != _slots.end();)
		{
			if (it->second == &texture) {
				it = _slots.erase(it);
			}
			else it++;
		}
	}

	GLSlot TextureManager::FindTextureSlot(Texture& image) {
		bool foundOne = false;
		GLSlot result = { TextureReadMode::Image, GLuint(-1) };
		for (const auto& slot : _slots)
		{
			if (slot.second == &image) {
				result = slot.first;
				if (foundOne) {
					Log::warn("Multiple slots use texture when trying to find one slot, returning last one");
				}
				foundOne = true;
			}
		}
		if (result.index == GLuint(-1)) {
			Log::info("No slot using texture was found");
			return result;
		}
		return result;
	}
}


