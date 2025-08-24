#pragma once
#include "Layer.h"
#include <vector>

namespace Vega {

	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void AttachLayer(Layer* layer);
		void DetachLayer(Layer* layer);

		void ClearLayers();

		auto begin() -> std::vector<Layer*>::iterator {
			return _layers.begin();
		}
		auto end() -> std::vector<Layer*>::iterator {
			return _layers.end();
		}

	private:
		std::vector<Layer*> _layers;
	};
}

