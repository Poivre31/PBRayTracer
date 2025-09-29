export module Math:Random;
import :Vec3;
import std;
import <random>;

export namespace Vega::Math {

	std::mt19937_64 engine;

	class Random {
	public:
		template <std::floating_point T>
		static T Randf(T a, T b) {
			std::uniform_real_distribution<T> distrib{a,b};
			return distrib(engine);
		}
		//static double RandDouble(double a, double b) {
		//	return (b - a) * double(rand()) / RAND_MAX + a;
		//}

		template <std::floating_point T>
		static Vec3<T> Rand3f(T a, T b) {
			return Vec3(Randf<T>(a, b), Randf<T>(a, b), Randf<T>(a, b));
		}

		template <std::floating_point T>
		static Vec3<T> Rand3fUnitSphere() {
			T phi = Randf<T>(0., 2 * std::numbers::pi);
			T theta = Randf<T>(-1., 1.);
			theta = acos(theta);

			return Vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
		}

		template <std::integral T>
		static T Randi(T a, T b) {
			return a + rand() % (b - a);
		}

	private:
	};

}