export module Core:ScreenQuad;
import :Layer;
import Utility;
import Render;

export namespace Vega {

	class ScreenQuad : public Layer {
	public:
		ScreenQuad() {
			_screenQuad = Mesh2D::CreateScreenQuad();
		}

		ScreenQuad(Shader* shader) : _shader(shader) {
			_screenQuad = Mesh2D::CreateScreenQuad();
		}

		void SetShader(Shader* shader) {
			_shader = shader;
		}

		void OnUpdate() override {
			if (!_shader) {
				Log.error("No shader set for screen quad");
				return;
			}
			_screenQuad.Draw(_shader);
		}

	private:
		Mesh2D _screenQuad;
		Shader* _shader = nullptr;
	};

}