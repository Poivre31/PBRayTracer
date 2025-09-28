export module Core:IOLayer;
import :Window;
import :Layer;
import IO;
import Utility;

using enum Vega::KeyEvent;

namespace Vega {

	class IOData {
	public:
		Keys inputs;
	};

	class IOLayer : public Layer {
	public:
		IOLayer(Window* window) : _window(window) {}

		void OnUpdate() override {
			_data.inputs.Update();

			_window->CenterCursor(_data.inputs.KeyStatus(Key::MouseRight, Down));
		}

		IOData GetData() const {
			return _data;
		}

	private:
		Window* _window = nullptr;
		IOData _data{};
	};

}