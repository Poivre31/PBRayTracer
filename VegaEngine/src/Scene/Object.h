#pragma once
#include "Math/Vec3.h"
#include "Core/Log.h"
#include "Core/Timer.h"

namespace Vega {

	class Object {
	public:

		Vec3<double> GetPosition() {
			return _position;
		}
		Vec3<double> GetScale() {
			return _scale;
		}
		Vec3<double> GetOrientation() {
			return _orientation;
		}

		void SetPosition(Vec3<double> position) {
			_position = position;
		}
		void SetScale(Vec3<double> scale) {
			_scale = scale;
		}
		void SetOrientation(Vec3<double> orientation) {
			_orientation = orientation;
		}

	private:
		Vec3<double> _position = Vec3(0.);
		Vec3<double> _scale = Vec3(1.);
		Vec3<double> _orientation = Vec3(0., 0., 1.);
	};

	class RigidBody : public Object {

	public:

		void Update(double timeStep) {
			_acceleration = _totalForce / _mass;
			_velocity += _acceleration * timeStep;
			SetPosition(GetPosition() + _velocity * timeStep);
			_totalForce = Vec3(0.);
		}

		template<typename T>
		void AddForce(Vec3<T> force) {
			_totalForce += Vec3<double>(force);
		}

		Vec3<double> GetVelocity() {
			return _velocity;
		}
		Vec3<double> GetAcceleration() {
			return _acceleration;
		}
		double GetMass() {
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
		}
		void ClearForces() {
			_totalForce = Vec3(0.);
		}

	private:
		Vec3<double> _velocity = Vec3(0.);
		Vec3<double> _acceleration = Vec3(0.);
		Vec3<double> _totalForce = Vec3(0.);
		double _mass = 1.;
	};

}

