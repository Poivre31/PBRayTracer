export module Vega;

export import Core;
export import Math;
export import Io;
export import Utility;
export import Render;
export import Entities;
export import Gui;
export import DataContainer;

namespace Vega {

	export class Systems {
	public:
		static Application* Application() {
			return Application::Get();
		}
		static Window* Window() {
			return Application::Get()->GetWindow();
		}
		static GuiLayer* Gui() {
			return Application::Get()->GetGUI();
		}
		static IOData IoData() {
			return Application::Get()->GetIOData();
		}
		static DrawingLayer* DrawStack() {
			return Application::Get()->GetDrawStack();
		}
	};

}