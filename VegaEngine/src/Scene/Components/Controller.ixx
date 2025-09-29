module;
#include "imgui.h"
export module Entities:Components.Controller;
import :Components.RigidBody;
import Math;
import Io;
import std;


using namespace Vega::Math;

const double fac = .5 * std::log(2. * std::exp(1.) - 1.);

namespace Vega {

	export class CController : public CRigidBody {
	public:

		/// <summary>
		/// Moves a controller's rigid body with movement interpolation according to the specified direction matrix.
		/// </summary>
		/// <param name="object"> : Rigid body to transform </param>
		/// <param name="keys"> : Keys pressed (uses ZQSDAE for directions) </param>
		/// <param name="movementBase"> : Specifies the world space directions for the acceleration to follow. 
		/// Defaults to identity matrix, so forward is x+, down is z-... </param>
		/// <param name="maxSpeed"> : Maximum speed</param>
		/// <param name="minSpeed"> : Minimum speed before flushing to zero </param>
		/// <param name="sprintTime"> : Caracteristic time of acceleration, corresponds to the time needed to reach 63% of maximum speed </param>
		/// <param name="stopTime"> : Caracteristic time of decceleration, corresponds to the time needed to reach 27% of initial speed </param>
		void Move(Keys keys, const Mat3x3& movementBase = Mat3x3(),
			double maxSpeed = 15., double minSpeed = 0.0001, double sprintTime = 10., double stopTime = 0.05
		) {
			Vec3<double> velocity = GetVelocity();
			if (abs(velocity.x) < minSpeed) velocity.x = 0;
			if (abs(velocity.y) < minSpeed) velocity.y = 0;
			if (abs(velocity.z) < minSpeed) velocity.z = 0;
			SetVelocity(velocity);

			Mat3x3 invBase = movementBase;

			Vec3<double> forceDirection = Vec3(0.);
			Vec3<bool> moving = Vec3(false);
			if (keys.KeyDown(Key::Z)) {
				forceDirection.x += 1.;
				moving.x = true;
			}
			if (keys.KeyDown(Key::S)) {
				forceDirection.x -= 1.;
				moving.x = !moving.x;
			}
			if (keys.KeyDown(Key::Q)) {
				forceDirection.y += 1.;
				moving.y = true;
			}
			if (keys.KeyDown(Key::D)) {
				forceDirection.y -= 1.;
				moving.y = !moving.y;
			}
			if (keys.KeyDown(Key::A)) {
				forceDirection.z += 1.;
				moving.z = true;
			}
			if (keys.KeyDown(Key::E)) {
				forceDirection.z -= 1.;
				moving.z = !moving.z;
			}

			forceDirection.Normalize();

			Vec3<double> velocityMvtFrame = Mul(invBase.T(), velocity);

			Vec3<bool> reverse = (forceDirection * velocityMvtFrame).IsNegative();
			Vec3<double> stopDirection = Vec3<double>(Or(Not(moving), reverse));

			double dragCoef = GetMass() * fac / (sprintTime * maxSpeed);
			Vec3<double> airDrag = -dragCoef * (Vec3(1.) - stopDirection) * velocity.Norm() * velocity;

			double acc = dragCoef * maxSpeed * maxSpeed;

			AddForce(airDrag);

			dragCoef = GetMass() / stopTime;
			Vec3<double> stopDrag = -dragCoef * stopDirection * velocityMvtFrame;
			stopDrag = Mul(movementBase, stopDrag);
			AddForce(stopDrag);

			Vec3<double> force = Mul(movementBase, forceDirection);

			AddForce(acc * force);
		}

		void Rotate(Keys keys, float mouseSpeed = 1.) {
			if (keys.KeyDown(Key::MouseRight) && !keys.KeyPressed(Key::MouseRight)) {
				double speedTheta = mouseSpeed * ImGui::GetIO().MouseDelta.y / 640;
				double speedPhi = -mouseSpeed * ImGui::GetIO().MouseDelta.x / 640;

				Vec3<double> rtp = cart2sphr1(GetRotation());
				rtp.y = std::clamp(rtp.y + speedTheta, 1.0E-5, std::numbers::pi - 1.0E-5);
				rtp.z += speedPhi;
				SetRotation(sph2cartr1(rtp));
			}
		}
	};

}