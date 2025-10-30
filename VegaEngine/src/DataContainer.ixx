export module DataContainer;
import std;
import Math;
import Gui;
import Render;



export namespace Vega {

	template<typename T>
	struct array_type {
		using type = T;
	};

	template<typename T, size_t N>
	struct array_type<std::array<T, N>> {
		using type = T;
	};

	template <typename T>
	requires std::is_arithmetic_v<typename array_type<T>::type>
	class DataContainer {
	public:
		using U = array_type<T>::type;
		DataContainer(const char* name, T data, U min, U max) : _name(name), _data(data), _min(min), _max(max) {};

		void AddGuiInput() {
			Slider(_name, _data, _min, _max);
		}

		void SendToShader(Shader* shader) {
			shader->SetVariable(_name, _data);
		}

		T Get() {
			return _data;
		}

		void Set(T& data) {
			_data = data;
		}

	private:
		const char* _name;
		T _data;
		U _min;
		U _max;
	};
}