export module Entities:Primitives;
import :Entity;
import Math;
import Render;
import std;
import Io;

using namespace Vega::Math;


export namespace Vega {

	struct GpuPrimitive {
		int type = 0;
		int pad1;
		int pad2;
		int pad3;
		float4 color = { 1,1,1,0 };
		float4 position = { 0,0,0,0 };
		float4 scale = { 1,1,1,0 };
		float4 A = { 0,0,0,0 };
		float4 B = { 1,1,1,0 };
	};


	struct Circle {
		Vec3<float> position;
		float radius;
	};

	struct Line {
		Vec3<float> origin;
		Vec3<float> endpoint;
		float width;
	};

	struct Box {
		Vec3<float> position;
		Vec3<float> dimensions;
	};

	struct Donut {
		Vec3<float> position;
		float inRadius;
		float outRadius;
	};

	struct Arrow {
		Vec3<float> origin;
		Vec3<float> endpoint;
		float width;
	};

	class Primitive : public Vega::Entity {
	public:
		GpuPrimitive Parse() {
			return p;
		};

		void SetCircle(Circle o, Vec3<float> color, float alpha){
			p.type = 0;
			p.color = { color.x,color.y,color.z,alpha };
			p.position = { o.position.x,o.position.y,o.position.z };
			p.scale = { o.radius };
		}

		void SetLine(Line o, Vec3<float> color, float alpha) {
			p.type = 1;
			p.color = { color.x,color.y,color.z,alpha };
			p.A = { o.origin.x,o.origin.y,o.origin.z };
			p.B = { o.endpoint.x,o.endpoint.y,o.endpoint.z };
			p.scale = { o.width };
		}

		void SetBox(Box o, Vec3<float> color, float alpha) {
			p.type = 2;
			p.color = { color.x,color.y,color.z,alpha };
			p.position = { o.position.x,o.position.y,o.position.z };
			p.scale = { o.dimensions.x,o.dimensions.y,o.dimensions.z };
		}

		void SetDonut(Donut o, Vec3<float> color, float alpha) {
			p.type = 3;
			p.color = { color.x,color.y,color.z,alpha };
			p.position = { o.position.x,o.position.y,o.position.z };
			p.scale = { o.inRadius,o.outRadius };
		}

		void SetArrow(Arrow o, Vec3<float> color, float alpha) {
			p.type = 4;
			p.color = { color.x,color.y,color.z,alpha };
			p.A = { o.origin.x,o.origin.y,o.origin.z };
			p.B = { o.endpoint.x,o.endpoint.y,o.endpoint.z };
			p.scale = { o.width };
		}

	private:
		GpuPrimitive p{};
	};

}