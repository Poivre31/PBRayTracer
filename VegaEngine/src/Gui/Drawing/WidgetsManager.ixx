export module Gui:WidgetsManager;
import :Widgets;
import :Primitives;
import :Grid;
import Render;
import Math;
import std;

struct State {

	unsigned int moving : 1;

};

export namespace Vega {

	class WidgetsManager {
	public:

		template<std::derived_from<Widget> W, class ...Args>
		void Add(Args... args) {
			_widgets.push_back(new W(args...));
		}

		template<std::derived_from<Widget> W>
		void Add(W* w) {
			_widgets.push_back(w);
		}


		Status Update(Vec2<int> size, Shader* shader, Grid* grid) {
			_primitives.clear();
			auto status = Status::Idle;
			int selectionIndex = -1, i = 0;
			bool lock = false;
			for (auto* w : _widgets)
			{
				auto s = w->Update(&_primitives, size, grid, lock);
				if (s == Status::Deleting) {
					selectionIndex = i;
				}
				//if (s == Status::Hovering && status != Status::Moving) {
				//	status = Status::Hovering;
				//	lock = true;
				//}
				if (s == Status::Moving) {
					status = Status::Moving;
					lock = true;
				}
				i++;
			}
			if(selectionIndex >= 0)
				_widgets.erase(_widgets.begin() + selectionIndex);

			_primitivesBuffer.SetData(_primitives);
			_primitivesBuffer.Bind(7);

			shader->SetInt("nPrimitives", (int)_primitives.size());

			return status;
		}

	private:

		std::vector<Widget*> _widgets;
		std::vector<Primitive> _primitives;
		LinkedSSBO<Primitive, GpuPrimitive> _primitivesBuffer;
	};

}