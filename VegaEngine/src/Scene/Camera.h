#pragma once
#include "Object.h"
#include "Math/Vec3Math.h"
#include "Math/Mat3x3.h"
#include "IO/Keys.h"

namespace Vega {

	class Camera : public RigidBody
	{
	public:

		Camera() {
			SetOrientation(Vec3(1., 0., 0.));
		}

		void Print() {
			GetPosition().Print();
			//GetScale().Print();
			//GetVelocity().Print();
		}

		void Rotate(double timeStep, Keys keys, float mouseSpeed = 1.) {
			if (keys.GetMouseRight()) {
				double speedTheta = mouseSpeed * ImGui::GetIO().MouseDelta.y / 640;
				double speedPhi = -mouseSpeed * ImGui::GetIO().MouseDelta.x / 640;

				Vec3<double> forward = _base.C1;
				Vec3<double> up = _base.C3;

				_base.C1 = forward * cos(speedTheta) - up * sin(speedTheta);
				_base.C3 = up * cos(speedTheta) + forward * sin(speedTheta);

				auto rot = Mat3x3::RotationZ(speedPhi);
				_base.C1 = Mul(rot, _base.C1);
				_base.C2 = Mul(rot, _base.C2);
				_base.C3 = Mul(rot, _base.C3);

				SetOrientation(_base.C1);
			}
		}


		Mat3x3& GetTransformationMatrix() {
			return _base;
		}

		void SetFov(float vFov) {
			_vFov = vFov;
		}
		float GetFov() {
			return _vFov;
		}

	private:
		float _vFov = 45.f;
		Mat3x3 _base;
	};

}

