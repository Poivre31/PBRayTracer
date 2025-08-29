#include "LayerStack.h"
#include "Log.h"

namespace Vega {

	LayerStack::LayerStack() = default;

	LayerStack::~LayerStack() {
		ClearLayers();
		for (auto* layer : _layerHistory)
		{
			delete layer;
		}
		_layerHistory.clear();
	}

	void LayerStack::AttachLayer(Layer* layer) {
		layer->OnAttach();
		_layers.push_back(layer);
		_layerHistory.push_back(layer);
	}

	void LayerStack::DetachLayers(Layer* layer) {
		for (auto it = _layers.begin(); it!= _layers.end();)
		{
			if (layer == *it) {
				layer->OnDetach();
				it = _layers.erase(it);
#ifdef DEBUG
				Log::debug(std::format("Detached layer: '{}'", layer->GetName()));
#endif 
			}
			else {
				it++;
			}
		}
	}

	void LayerStack::ClearLayers() {
		for (auto layer: _layers)
		{
			layer->OnDetach();
		}
		_layers.clear();
	}
}