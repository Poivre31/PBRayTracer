#pragma once
#include "Components/Camera.h"
#include "Components/Controller.h"
#include "Components/RigidBody.h"
#include "Components/RTPrimitive.h"
#include "Components/Transform.h"

namespace Vega {

	class Entity {

	public:
		size_t GetID() {
			return _ID;
		}

		virtual void OnUpate() {

		}

		virtual void OnPhysicsUpdate(double deltaTime) {

		}

	private:
		size_t _ID;
	};

}