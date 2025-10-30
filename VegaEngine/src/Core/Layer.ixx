module;
#include "OpenGL.h"


export module Core:Layer;
import Utility;
import std;

namespace Vega {

	export class Layer
	{
	public:
		Layer() = default;
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnResize(int width, int height) {}
		virtual void OnUpdate(double deltaTime) {}
	};

}

