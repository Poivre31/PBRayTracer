#pragma once
#include <string>
#include "imgui.h"

namespace Vega {

	class ImGuiCanvas
	{
	public:
		ImGuiCanvas() = default;
		virtual ~ImGuiCanvas() = default;

		virtual void Draw() = 0;
	};

}

