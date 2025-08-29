#pragma once
#include "Object.h"
#include "Core/Application.h"

namespace Vega {

	enum PrimitiveType {
		sphere = 0,
		cube = 1,
		plane = 2,
		circle = 3,
		cylinder = 4,
		cone = 5,
		pyramid = 6
	};

	class RTPrimitive {
	public:
		RTPrimitive() = default;
		RTPrimitive(PrimitiveType type) : _type(type) {}

		void SetColor(Vec3<float> color) {
			_color = color;
		}
		Vec3<float> GetColor() const {
			return _color;
		}

		void SetPrimitiveType(PrimitiveType type) {
			_type = type;
		}
		PrimitiveType GetPrimitiveType() const {
			return _type;
		}


	private:
		Vec3<float> _color{};
		PrimitiveType _type = PrimitiveType::sphere;
	};

	class Entity : public RigidBody, public RTPrimitive
	{

	};

}

