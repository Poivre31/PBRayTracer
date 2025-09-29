export module Entities:Entity;
export import :Components.Camera;
export import :Components.Controller;
export import :Components.RigidBody;
export import :Components.Transform;
export import :Components.RTPrimitive;
import std;

export namespace Vega {

	class Entity {
	public:
		Entity() {
			_ID = _counter;
			_counter++;
		}

		size_t GetID() const {
			return _ID;
		}

		virtual void Random() {

		}

		virtual void OnCreate() {

		}

		virtual void OnUpdate(double deltaTime) {

		}

		virtual void OnDestroy() {

		}

	private:
		size_t _ID;
		static inline size_t _counter = 0;
	};

	template<std::derived_from<Entity> T>
	T RandomEntity() {
		auto e = T();
		e.Random();
		return e;
	}

}