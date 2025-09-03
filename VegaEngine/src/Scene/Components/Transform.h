#pragma once

#include <concepts>
#include "Math/Vec3.h"

namespace Vega {
	
	class CTransform {
	public:
		void SetPosition(Vec3<double> position) {
			_position = position;
		}
		void SetRotation(Vec3<double> rotation) {
			_rotation = rotation;
		}
		void SetScale(Vec3<double> scale) {
			_scale = scale;
		}

		Vec3<double> GetPosition() const {
			return _position;
		}
		Vec3<double> GetRotation() const {
			return _rotation;
		}
		Vec3<double> GetScale() const {
			return _scale;
		}
 
	private:
		Vec3<double> _position;
		Vec3<double> _rotation;
		Vec3<double> _scale;

	};

}