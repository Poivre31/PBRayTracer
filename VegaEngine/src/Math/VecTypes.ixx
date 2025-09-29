export module Math:VecTypes;
import :Vec3;
import std;

export namespace Vega::Math {

	typedef std::array<float, 2> float2;
	typedef std::array<float, 3> float3;
	typedef std::array<float, 4> float4;

	typedef std::array<int, 2> int2;
	typedef std::array<int, 3> int3;
	typedef std::array<int, 4> int4;

	template<std::floating_point T>
	float4 toFloat4(Vec3<T> v) {
		return { v.x, v.y, v.z, 0 };
	}

}