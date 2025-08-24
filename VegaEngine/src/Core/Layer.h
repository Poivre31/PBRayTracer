#pragma once
#include <vector>

namespace Vega {

	class Layer
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
	};
}

