#pragma once
#include "Keys.h"
#include "Core/Layer.h"
#include "Core/Window.h"

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

		IOData GetData() {
			return _data;
		}

	private:
		Window* _window = nullptr;
		IOData _data{};
	};

}