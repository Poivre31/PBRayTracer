export module Core:Entity;
export import :Components.Camera;
export import :Components.Controller;
export import :Components.RigidBody;
export import :Components.Transform;
export import :Components.RTPrimitive;
import std;

export namespace Vega {

	class Entity {

	public:
		size_t GetID() const {
			return _ID;
		}

		virtual void Random() {

		}

		virtual void OnCreate() {

		}

		virtual void OnUpdate() {

		}

		virtual void OnPhysicsUpdate(double deltaTime) {

		}

		virtual void OnDestroy() {

		}

	private:
		size_t _ID;
	};

	template<std::derived_from<Entity> T>
	T RandomEntity() {
		auto e = T();
		e.Random();
		return e;
	}

}