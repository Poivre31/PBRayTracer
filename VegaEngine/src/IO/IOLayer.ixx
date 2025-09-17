export module Core:IOLayer;
import :Window;
import :Layer;
import :Keys;
import :Log;
namespace Vega {

	class IOData {
	public:
		Keys mainControls;
	};

	class IOLayer : public Layer {
	public:
		IOLayer(Window* window) : _window(window) {}

		void OnUpdate() override {
			_data.mainControls.SetKeysFromInput();

			_window->CenterCursor(_data.mainControls.GetMouseRight());
		}

		IOData GetData() const {
			return _data;
		}

	private:
		Window* _window = nullptr;
		IOData _data{};
	};

}