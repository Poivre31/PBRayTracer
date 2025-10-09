export module Core:DrawingLayer;
import Entities;
import Render;
import Io;
import std;
import Math;
import :Window;
import :Layer;

using namespace Vega::Math;

static const auto screenVert = "defaults/default.vert";
//static const auto screenFrag = "defaults/proceduralPrimitive.frag";
static const auto screenFrag = "proceduralPrimitive.frag";

export namespace Vega {
	class DrawingLayer : public Layer {
	public:

		DrawingLayer(Window* window) : _window(window) {
			primitivesBuffer.Reserve(1);
			primitivesBuffer.Bind(7);
		}

		Shader* GetShader() {
			return _shader;
		}

		void Add(Circle o, Vec3<float> color = {1.f,1.f,1.f}, float alpha = 1.f) {
			Primitive p;
			p.SetCircle(o,color, alpha);
			primitives.push_back(p);
		}

		void Add(Line o, Vec3<float> color = { 1.f,1.f,1.f }, float alpha = 1.f) {
			Primitive p;
			p.SetLine(o, color, alpha);
			primitives.push_back(p);
		}

		void Add(Box o, Vec3<float> color = { 1.f,1.f,1.f }, float alpha = 1.f) {
			Primitive p;
			p.SetBox(o, color, alpha);
			primitives.push_back(p);
		}

		void Add(Donut o, Vec3<float> color = { 1.f,1.f,1.f }, float alpha = 1.f) {
			Primitive p;
			p.SetDonut(o, color, alpha);
			primitives.push_back(p);
		}

		void Add(Arrow o, Vec3<float> color = { 1.f,1.f,1.f }, float alpha = 1.f) {
			Primitive p;
			p.SetArrow(o,color, alpha);
			primitives.push_back(p);
		}

		void OnUpdate(double) {
			if (Vega::Keys::KeyPressed(Vega::Key::R, Vega::KeyMod::ModCtrl)) {
				_shader->Reload();
			}

			GLuint width = _window->Width();
			GLuint height = _window->Height();
			_shader->SetInt("width", width);
			_shader->SetInt("height", height);
			_shader->SetInt("nPrimitives", primitives.size());

			primitivesBuffer.SetData(primitives);
			primitives.clear();
		}

	private:
		std::vector<Primitive> primitives;
		Vega::LinkedSSBO<Primitive, GpuPrimitive> primitivesBuffer;
		Vega::Shader* _shader = new Vega::Shader(screenVert, screenFrag);
		Vega::Window* _window;
	};
}