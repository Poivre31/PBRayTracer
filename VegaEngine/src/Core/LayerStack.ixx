export module Core:LayerStack;
import :Layer;
import :Log;
import std;

namespace Vega {

	export class LayerStack final
	{
	public:
		LayerStack();
		~LayerStack();

		void AttachLayer(Layer* layer);
		void DetachLayers(Layer* layer);

		void ClearLayers();

		auto begin() -> std::vector<Layer*>::iterator {
			return _layers.begin();
		}
		auto end() -> std::vector<Layer*>::iterator {
			return _layers.end();
		}

	private:
		std::vector<Layer*> _layers;
		std::vector<Layer*> _layerHistory;
	};
}