module;
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "OpenGL.h"

export module Gui:Viewport;
import :Grid;
import :Primitives;
import :Widgets;
import :WidgetsManager;
import Math;
import Render;
import Io;
import std;

struct ViewSettings {
	bool grid = false;
};

const char* vertShader = "defaults/default.vert";
const char* fragShader = "defaults/default.frag";
const char* gridShader = "defaults/viewport/grid.frag";
const char* widgetsShader = "defaults/viewport/widgets.frag";

export namespace Vega {


	class Viewport {
	public:

		Viewport() {
			_gridShader = new Shader(vertShader, gridShader);
			_widgetsShader = new Shader(vertShader, widgetsShader);
			_shaders.push_back(_gridShader);
			_shaders.push_back(_widgetsShader);
		}

		template<std::derived_from<Widget> W, class ...Args>
		void AddWidget(Args... args) {
			_widgetsManager.Add<W>(args...);
		}

		template<std::derived_from<Widget> W>
		void AddWidget(W* w) {
			_widgetsManager.Add(w);
		}

		void AddShader(Shader* shader) {
			_shaders.push_back(shader);
		}

		ViewSettings* GetViewSettings() {
			return &_settings;
		}

		GridSettings* GetGridSettings() {
			return _grid.Settings();
		}

		void Update(Vec2<int> size) {
			if (Keys::Pressed(Key::R)) {
				for (auto* shader : _shaders)
				{
					shader->Reload();
				}
			}
			_size = size;
			_frontBuffer.NewFrame(_size);
			_backBuffer.NewFrame(_size);

			auto status = _widgetsManager.Update(_size, _widgetsShader, &_grid);

			if (status == Status::Moving)
				_grid.Settings()->interactible = false;
			else
				_grid.Settings()->interactible = true;

			_grid.Update(_size, _gridShader);


			bool front = true;
			for (size_t i = _shaders.size()-1; i < _shaders.size(); i--)
			{
				if (front) {
					_frontBuffer.RunShader(_shaders[i]);
					TextureManager::BindTextureSlot(_frontBuffer.GetTexture(), { TextureReadMode::Sampler,0 });
				}
				else {
					_backBuffer.RunShader(_shaders[i]);
					TextureManager::BindTextureSlot(_backBuffer.GetTexture(), { TextureReadMode::Sampler,0 });
				}
				front = !front;
			}
			if(!front)
				ImGui::Image(_frontBuffer.GetTexture()->GetID(), ImVec2((float)_size.x, (float)_size.y));
			else
				ImGui::Image(_backBuffer.GetTexture()->GetID(), ImVec2((float)_size.x, (float)_size.y));
		}

	private:
		Vec2<int> _size;

		FrameBuffer _frontBuffer;
		FrameBuffer _backBuffer;
		ViewSettings _settings;

		Grid _grid;
		WidgetsManager _widgetsManager;

		Shader* _gridShader;
		Shader* _widgetsShader;
		std::vector<Shader*> _shaders;
	};

}