export module Entities:Components.RTPrimitive;
import Math;



export namespace Vega {

	enum PrimitiveType {
		sphere = 0,
		cube = 1,
		plane = 2,
		circle = 3,
		cylinder = 4,
		cone = 5,
		pyramid = 6
	};

	class CRTPrimitive {
	public:
		CRTPrimitive() = default;
		CRTPrimitive(PrimitiveType type) : _type(type) {}

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

}

