#include "LayerStack.h"
#include "Log.h"

namespace Vega {

	LayerStack::LayerStack() = default;

	LayerStack::~LayerStack() = default;

	void LayerStack::AttachLayer(Layer* layer) {
		layer->OnAttach();
		_layers.push_back(layer);
	}

	void LayerStack::DetachLayer(Layer* layer) {
		int i = 0;
		for (Layer* layerIt : _layers)
		{
			if (layer == layerIt) {
				layer->OnDetach();
				_layers.erase(begin() + i);
				return;
			}
			i++;
		}
		spdlog::warn("Layer not found in Layer Stack during detach call");
	}

	void LayerStack::ClearLayers() {
		_layers.clear();
	}
} // namespace Vega