export module Core:Components.Camera;
import Math;
import :Components.Transform;

using namespace Vega::Math;

namespace Vega {

	export class CCamera
	{
	public:

		void ConstructCameraView(const CTransform& transform) {
			Vec3<double> forward = transform.GetRotation();
			Vec3<double> left = Vec3(forward.y, -forward.x, 0.);
			left.Normalize();
			Vec3<double> up = cross(forward, left);
			if (dot(up, Vec3<double>::Z()) < 0) {
				up = -up;
				left = -left;
			}

			_base.C1 = forward;
			_base.C2 = left;
			_base.C3 = up;
			_position = transform.GetPosition();
		}

		//void Rotate(double timeStep, Keys keys, float mouseSpeed = 1.) {
		//	if (keys.GetMouseRight()) {
		//		double speedTheta = mouseSpeed * ImGui::GetIO().MouseDelta.y / 640;
		//		double speedPhi = -mouseSpeed * ImGui::GetIO().MouseDelta.x / 640;

		//		Vec3<double> forward = _base.C1;
		//		Vec3<double> up = _base.C3;

		//		_base.C1 = forward * cos(speedTheta) - up * sin(speedTheta);
		//		_base.C3 = up * cos(speedTheta) + forward * sin(speedTheta);

		//		auto rot = Mat3x3::RotationZ(speedPhi);
		//		_base.C1 = Mul(rot, _base.C1);
		//		_base.C2 = Mul(rot, _base.C2);
		//		_base.C3 = Mul(rot, _base.C3);
		//	}
		//}


		void SetFov(float vFov) {
			_vFov = vFov;
		}
		void SetPosition(const Vec3<double>& position) {
			_position = position;
		}
		void SetTransformationMatrix(const Mat3x3& base) {
			_base = base;
		}

		float GetFov() const {
			return _vFov;
		}
		Vec3<double> GetPosition() const {
			return _position;
		}
		Mat3x3 GetTransformationMatrix() const {
			return _base;
		}

	private:
		float _vFov = 45.f;
		Vec3<double> _position = Vec3(0.);
		Mat3x3 _base = Mat3x3();
	};

}

