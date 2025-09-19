export module Math:VecTypes;
import :Vec3;
import std;

export namespace Vega::Math {

	struct float4 {
		float x;
		float y;
		float z;
		float w;
	};

	struct int4 {
		int x; 
		int y;
		int z;
		int w;
	};

	template<std::floating_point T>
	float4 toFloat4(Vec3<T> v) {
		return { v.x, v.y, v.z, 0 };
	}

}