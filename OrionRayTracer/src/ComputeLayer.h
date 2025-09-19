#pragma once
import Vega;

using namespace Vega::Math;

class ComputeLayer : public Vega::Layer {
public:

	ComputeLayer() {
		_app = Vega::Application::Get();
	}

	void OnAttach() override {
		_width = _app->GetWindow()->GetWidth();
		_height = _app->GetWindow()->GetHeight();

		_image = Vega::Texture(Vega::TextureData{ _width, _height, Vega::Formats::RGBA32F });

		_scene = _app->GetScene();
		_shader = std::make_unique<Vega::ComputeShader>("res/", ".comp");
		Vega::TextureManager::BindTextureSlot(_image, { Vega::TextureReadMode::Image,0 });
		_shader->SetInt("image", 0);
		Vega::TextureManager::BindTextureSlot(_image, { Vega::TextureReadMode::Sampler,0 });
		_shader->SetInt("screenTexture", 0);

		_camera.camera.SetFov(65.f);
		_camera.camera.SetPosition(Vec3(-1., 0., 0.));
		_camera.controller.SetMass(.2);

		Vega::Scene::RandomScene(_scene, 256);
	}

	void OnResize(GLuint width, GLuint height) override {
		_width = width;
		_height = height;
		Vega::TextureManager::UpdateTexture(_image, width, height);
	}

	void OnUpdate() override {
		if (ImGui::IsKeyPressed(ImGuiKey_R)) {
			_shader->Reload();
		}

		_scene->ParseTransforms(_shader.get());
		_scene->BindSSBO(0, 1);

		_shader->SetInt("frameIndex", (int)Vega::Timer::GetFrameCount());

		_shader->SetFloat3("camera.position", Vec3<float>(_camera.camera.GetPosition()).ToArray());
		_shader->SetMat3x3("camera.base", Mat3x3f(_camera.camera.GetTransformationMatrix()));
		_shader->SetFloat("camera.vFov", _camera.camera.GetFov());

		_shader->Dispatch2D(_width, _height, _threadSizeX, _threadSizeY);
	}

	void OnPhysicsUpdate(double timeStep) override {
		Vega::Keys controls = _app->GetIOData().mainControls;

		_camera.Update(timeStep, controls);
	}

private:
	GLuint _width = 0;
	GLuint _height = 0;
	std::unique_ptr<Vega::ComputeShader> _shader;
	Vega::Texture _image;

	GLuint _threadSizeX = 16;
	GLuint _threadSizeY = 16;

	Vega::Camera _camera;
	Vega::Scene* _scene = nullptr;
	Vega::Application* _app = nullptr;
};