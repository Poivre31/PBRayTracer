#include <Vega.h>
#include <memory>
#include "DebugWindow.h"
#include "ObjectManager.h"

class ShaderLayer : public Vega::Layer {
public:
	void OnAttach() override {
		_shader = new Vega::Shader("res/fullScreenQuad.vert", "res/fullScreenQuad.frag");
		_shader->SetInt("screenTexture", 0);
	}

	void OnUpdate() override {
	}

	Vega::Shader* GetShader() {
		return _shader;
	}
private:
	Vega::Shader* _shader = nullptr;
};

class ComputeLayer : public Vega::Layer {
public:

	void OnAttach() override {
		_shader = new Vega::ComputeShader({
			"res/compTest.comp",
			"res/rayGeneration.comp",
			"res/rotations.comp",
			"res/sphere.comp",
			"res/transform.comp",
			});
		_image.BindImage(0);
		_shader->SetInt("image", _image.imageUnit);
		_image.BindTexture(0);
	}

	void OnUpdate() override {
		_shader->Use();
		UINT _width = Vega::Application::Get()->GetWindow()->GetWidth();
		UINT _height = Vega::Application::Get()->GetWindow()->GetHeight();
		_shader->SetFloat3("objectPosition", (float*)&_object->transform.position);
		_shader->SetFloat3("objectScale", (float*)&_object->transform.scale);
		_shader->SetFloat2("objectRotation", (float*)&_object->transform.rotation);
		_shader->Dispatch2D(_width, _height, 16, 16);
	}

private:
	UINT _width = Vega::Application::Get()->GetWindow()->GetWidth();
	UINT _height = Vega::Application::Get()->GetWindow()->GetHeight();
	Vega::ComputeShader* _shader = nullptr;
	Vega::Texture _image = Vega::Texture(_width, _height, GL_RGBA32F);
	Vega::Object* _object = &Vega::Application::Get()->sphere;
};

class Orion : public Vega::Application {
public:
	Orion() {
		spdlog::info("Orion Ray Tracer launched");

		AttachLayer(new ComputeLayer());
		ShaderLayer* sl = new ShaderLayer();
		AttachLayer(sl);


		Vega::ScreenQuadDisplay* screenQuad = new Vega::ScreenQuadDisplay(sl->GetShader());
		AttachLayer(screenQuad);


		Vega::ImGuiLayer* imgui = new Vega::ImGuiLayer();
		imgui->AttachWindow(new DebugWindow());
		imgui->AttachWindow(new ObjectManagerUI());
		AttachLayer(imgui);
	}

	~Orion() override {
		spdlog::info("Orion Ray Tracer closed");
	}
};

std::unique_ptr <Vega::Application> Vega::CreateApplication() {
	return std::make_unique<Orion>();
}