#pragma once

#include <concepts>
#include "Math/Vec3.h"
#include "Math/Vec3Math.h"
#include "Math/Vec2.h"
#include "Core/Log.h"
#include "Transform.h"

namespace Vega {

	class CRigidBody : public CTransform {
	public:

		void Update(double timeStep) {
			SetPosition(GetPosition() + _velocity * timeStep);
			_velocity += _acceleration * timeStep;
			_acceleration = Vec3<double>(0);

			Vec3<double> rtp = cart2sphr1(GetRotation());
			rtp.y += _angularVelocity.x * timeStep;
			rtp.z += _angularVelocity.y * timeStep;
			SetRotation(sph2cartr1(rtp));
			_angularVelocity += _torque * timeStep;
			_torque = Vec2<double>(0);

		}

		void AddForce(Vec3<double> force) {
			_acceleration += force * _invMass;
		}
		void AddTorque(Vec2<double> torque) {
			_torque += torque * _invMass;
		}
		void ClearForces() {
			_acceleration = Vec3<double>(0);
			_torque = Vec2<double>(0);
		}

		Vec3<double> GetVelocity() const {
			return _velocity;
		}
		Vec2<double> GetAngularVelocity() const {
			return _angularVelocity;
		}
		Vec3<double> GetAcceleration() const {
			return _acceleration;
		}
		Vec2<double> GetTorque() const {
			return _torque;
		}
		double GetMass() const {
			return _mass;
		}

		void SetVelocity(Vec3<double> velocity) {
			_velocity = velocity;
		}
		void SetAcceleration(Vec3<double> acceleration) {
			_acceleration = acceleration;
		}
		void SetMass(double mass) {
			if (mass == 0) {
				Log::warn("Mass set to invalid value: 0");
				return;
			}
			_mass = mass;
			_invMass = 1 / _mass;
		}


	private:
		Vec3<double> _velocity{};
		Vec3<double> _acceleration{};
		Vec2<double> _angularVelocity{};
		Vec2<double> _torque{};
		double _mass = 1.;
		double _invMass = 1.;
	};

}