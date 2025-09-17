export module Core:ScreenQuad;
import :Mesh2D;
import :Shader;
import :Layer;
import :Log;

export namespace Vega {

	class ScreenQuadDisplay : public Layer {
	public:
		ScreenQuadDisplay() {
			_screenQuad = Mesh2D::CreateScreenQuad();
		}

		ScreenQuadDisplay(Shader* shader) : _shader(shader) {
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