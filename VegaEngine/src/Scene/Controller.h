#pragma once
#include "Object.h"
#include "imgui.h"
#include "IO/Keys.h"
#include "Math/Vec3Math.h"
#include "Math/Mat3x3.h"

const double fac = .5 * log(2. * exp(1.) - 1.);

namespace Vega {

	class Controller
	{
	public:
		static void Move(RigidBody* object, Keys keys, const Mat3x3& movementBase,
			double maxSpeed = 15., double minSpeed =  0.0001, double sprintTime = 5., double stopTime = 0.05
		) {
			Vec3<double> velocity = object->GetVelocity();
			if (abs(velocity.x) < minSpeed) velocity.x = 0;
			if (abs(velocity.y) < minSpeed) velocity.y = 0;
			if (abs(velocity.z) < minSpeed) velocity.z = 0;
			object->SetVelocity(velocity);

			Mat3x3 invBase = movementBase;

			Vec3<double> forceDirection = Vec3(0.);
			Vec3<bool> moving = Vec3(false);
			if (keys.GetKeyZ()) {
				forceDirection.x += 1.;
				moving.x = true;
			}
			if (keys.GetKeyS()) {
				forceDirection.x -= 1.;
				moving.x = !moving.x;
			}
			if (keys.GetKeyQ()) {
				forceDirection.y += 1.;
				moving.y = true;
			}
			if (keys.GetKeyD()) {
				forceDirection.y -= 1.;
				moving.y = !moving.y;
			}
			if (keys.GetKeyA()) {
				forceDirection.z += 1.;
				moving.z = true;
			}
			if (keys.GetKeyE()) {
				forceDirection.z -= 1.;
				moving.z = !moving.z;
			}

			forceDirection.Normalize();

			Vec3<double> velocityMvtFrame = Mul(invBase.T(), velocity);

			Vec3<bool> reverse = (forceDirection * velocityMvtFrame).IsNegative();
			Vec3<double> stopDirection = Vec3<double>(Or(Not(moving),reverse));

			double dragCoef = object->GetMass() * fac / (sprintTime * maxSpeed);
			Vec3<double> airDrag = -dragCoef * (Vec3(1.) - stopDirection) *velocity.Norm() * velocity;

			double acc = dragCoef * maxSpeed * maxSpeed;

			object->AddForce(airDrag);

			dragCoef = object->GetMass() / stopTime;
			Vec3<double> stopDrag = -dragCoef * stopDirection * velocityMvtFrame;
			stopDrag = Mul(movementBase, stopDrag);
			object->AddForce(stopDrag);

			Vec3<double> force = Mul(movementBase, forceDirection);

			object->AddForce(acc * force);
		}

	};

}