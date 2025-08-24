#pragma once
#include <string>
#include "imgui.h"

namespace Vega {

	class ImGuiInterface
	{
	public:
		virtual void Draw() = 0;
	};

}

