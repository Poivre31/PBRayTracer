#include <Vega.h>
#include <memory>
#include "DebugWindow.h"
#include "ObjectManager.h"
#include<stdlib.h>
#include <numbers>

class ComputeLayer : public Vega::Layer {
public:

	void OnAttach() override {
		_shader = std::make_unique<Vega::ComputeShader>(std::vector<const char*>{
			"res/compTest.comp",
			"res/rayGeneration.comp",
			"res/transform.comp",
			"res/skyShader.comp",
			"res/rotations.comp",
			"res/sphere.comp",
			"res/cylinder.comp",
			"res/cone.comp",
			"res/cube.comp",
			"res/pyramid.comp",
			"res/plane.comp",
			"res/circle.comp",
			"res/intersectPrimitives.comp",
			"res/primitiveNormals.comp",
		});
		Vega::TextureManager::BindTextureSlot(*_image, { Vega::TextureReadMode::Image,0 });
		_shader->SetInt("image", 0);
		Vega::TextureManager::BindTextureSlot(*_image, { Vega::TextureReadMode::Sampler,0 });
		_shader->SetInt("screenTexture", 0);

		_camera.SetFov(65.f);
		_camera.SetPosition(Vec3(-1., 0., 0.));
		_camera.SetMass(.2);

		Vega::Scene::RandomScene(&_scene, 1024);
	}

	void OnUpdate() override {
		if (ImGui::IsKeyPressed(ImGuiKey_R)) {
			_shader->Reload();
		}

		_scene.ParseTransforms(_shader.get());
		_scene.BindSSBO(0);
		_shader->Use();
		_width = Vega::Application::Get()->GetWindow()->GetWidth();
		_height = Vega::Application::Get()->GetWindow()->GetHeight();
		Vega::TextureManager::UpdateTexture(*_image, _width, _height);
		_shader->SetFloat3("objectPosition", std::span<float, 3>(_object->transform.position.GetAdress(), 3));
		_shader->SetFloat3("objectScale", std::span<float, 3>(_object->transform.scale.GetAdress(), 3));
		_shader->SetFloat2("objectRotation", std::span<float, 2>(_object->transform.rotation.GetAdress(), 2));
		Vec3<float> position = _camera.GetPosition();
		Vec3<float> direction = _camera.GetOrientation();
		_shader->SetFloat3("camera.position", position.x, position.y, position.z);
		_shader->SetFloat3("camera.direction", direction.x, direction.y, direction.z);
		auto mat = Mat3x3f(_camera.GetTransformationMatrix());
		_shader->SetMat3x3("camera.base",&mat.a1);
		_shader->SetFloat("camera.vFov", _camera.GetFov());

		_shader->Dispatch2D(_width, _height, _threadSizeX, _threadSizeY);
	}

	const double fac = .5 * log(2. * exp(1.) - 1.);
	void OnPhysicsUpdate(double timeStep) override {
		Vega::Keys keys;
		keys.SetKeysFromInput();

		if(keys.GetMouseRight())
			glfwSetInputMode(Vega::Application::Get()->GetWindow()->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(Vega::Application::Get()->GetWindow()->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		_camera.Rotate(timeStep, keys);

		Vega::Controller::Move(&_camera, keys, _camera.GetTransformationMatrix());

		_camera.Update(timeStep);
	}

private:
	GLuint _width = Vega::Application::Get()->GetWindow()->GetWidth();
	GLuint _height = Vega::Application::Get()->GetWindow()->GetHeight();
	std::unique_ptr<Vega::ComputeShader> _shader;
	std::unique_ptr <Vega::Texture> _image = std::make_unique<Vega::Texture>(Vega::TextureData{ _width, _height, GL_RGBA32F });
	Vega::Object2* _object = &Vega::Application::Get()->sphere;

	GLuint _threadSizeX = 16;
	GLuint _threadSizeY = 16;

	Vega::Camera _camera;
	Vega::Scene _scene;
};

class RunLayer : public Vega::Layer {
	void OnAttach() override {
		_app = Vega::Application::Get();
	}

	void OnUpdate() override {
	}

private:
	Vega::Application* _app = nullptr;
};

class Orion : public Vega::Application {
public:
	Orion() {
		Log::trace("Opened Orion Ray Tracer");

		AttachLayer(new ComputeLayer());
		AttachLayer(new Vega::ScreenQuadDisplay(shader.get()));

		auto imgui = new Vega::ImGuiLayer(Application::Get()->GetWindow());
		imgui->AttachCanvas(new DebugWindow());
		AttachLayer(imgui);
	}

	~Orion() override {
		Log::info("Closed Orion Ray Tracer");
	}

private:
	std::unique_ptr<Vega::Shader> shader = std::make_unique<Vega::Shader>("res/fullScreenQuad.vert", "res/fullScreenQuad.frag");

};

std::unique_ptr<Vega::Application> Vega::CreateApplication() {
	return std::make_unique<Orion>();
}