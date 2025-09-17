export module Core:Entity;
export import :Components.Camera;
export import :Components.Controller;
export import :Components.RigidBody;
export import :Components.Transform;
export import :Components.RTPrimitive;

namespace Vega {

	class Entity {

	public:
		size_t GetID() const {
			return _ID;
		}

		virtual void OnCreate() {

		}

		virtual void OnUpate() {

		}

		virtual void OnPhysicsUpdate(double deltaTime) {

		}

		virtual void OnDestroy() {

		}

	private:
		size_t _ID;
	};

}