module;
#include "OpenGL.h"
export module Core:TextureManager;
import :Texture;
import std;

export namespace Vega {

	enum TextureReadMode {
		Image,
		Sampler,
	};

	struct GLSlot {
		TextureReadMode readMode;
		GLuint index;

		bool operator <(const GLSlot& rhs) const
		{
			if (readMode == rhs.readMode) {
				return index < rhs.index;
			}
			return readMode < rhs.readMode;
		}
	};

	class TextureManager final
	{
	public:
		~TextureManager() {
			_slots.clear();
		}

		static void BindTextureSlot(Texture& image, GLSlot slot);

		static void UnbindTextureSlot(GLSlot slot);

		static void UpdateTexture(Texture& texture, GLuint width, GLuint height);

		static void DeleteTexture(Texture& texture);

		static GLSlot FindTextureSlot(Texture& image);

	private:
		static inline std::map<GLSlot, Texture*> _slots;
	};

}

