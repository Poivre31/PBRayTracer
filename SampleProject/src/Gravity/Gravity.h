#pragma once
#include "../GraphicSettings.h"
#include "../DebugWindow.h"
#include "GravityWindow.h"

import Vega;
import std;



//static const auto screenVert = "defaults/default.vert";
//static const auto screenFrag = "defaults/screenQuad.frag";
//static const auto waveFrag = "wave.frag";
//static const auto waveComp = "wave.comp";
//static const bool useComputeShader = false;

struct GpuParticle {
	float4 position;
	float4 velocity;
};

class Particle : public Vega::Entity {
public:
	void Random() override {
		_rigidBody.SetPosition(Random::Rand3f(-1., 1.));
		_rigidBody.SetVelocity(.2f * Random::Rand3fUnitSphere<double>());
	}

	void OnCreate() override {
		Log.debug("Created entity {}", GetID());
	}

	void OnUpdate(double deltaTime) override {
		//_rigidBody.Update(deltaTime);

		//auto position = _rigidBody.GetPosition();
		//auto velocity = _rigidBody.GetVelocity();
		//std::function bounce = [](double x, double vx) {
		//	if (x > 1.) return -abs(vx);
		//	if (x < 0.) return abs(vx);
		//	else return vx;
		//	};
		//velocity = ApplyElementWise(position, velocity, bounce);
		//_rigidBody.SetVelocity(velocity);
	}

	void OnDestroy() override {
		Log.debug("Destroyed entity {}", GetID());
	}

	GpuParticle Parse() const {
		auto position = (Vec3<float>)_rigidBody.GetPosition();
		auto velocity = (Vec3<float>)_rigidBody.GetVelocity();
		return GpuParticle{
			position.x,position.y,position.z,0.,
			velocity.x,velocity.y,velocity.z,0.
		};
	}

private:
	Vega::CRigidBody _rigidBody;
};

class GravityDisplay : public Vega::Layer {
public:

	void OnAttach() override {
		_height = Vega::Systems::Window()->Height();
		_width = Vega::Systems::Window()->Width();

		_image = Vega::Texture({ _width ,_height,Vega::Formats::RGBA32F });
		Vega::TextureManager::BindTextureSlot(_image, { Vega::TextureReadMode::Image, 0 });
		Vega::TextureManager::BindTextureSlot(_image, { Vega::TextureReadMode::Sampler, 0 });
		Vega::Systems::Application()->AttachLayer<Vega::ScreenQuad>(_screenShader);

		Vega::Systems::Gui()->AttachCanvas<GravityWindow>("Gravity settings",&_settings);

		_collection.Random(_settings.nParticles);
		_pBuffer.SetData(_collection.Data());
		_pBuffer.Bind(0);
	}

	void OnResize(GLuint width, GLuint height) override {
		_width = width;
		_height = height;
		Vega::TextureManager::UpdateTexture(_image, width, height);
	}

	void OnUpdate(double deltaTime) override {
		if (Vega::Keys::Pressed(Vega::Key::R, Vega::KeyMod::ModCtrl)) {
			_screenShader->Reload();
			_computeShader->Reload();
			_gravityShader->Reload();
		}

		if (_collection.Size() != _settings.nParticles) {
			_collection.Random(_settings.nParticles);
			_pBuffer.SetData(_collection.Data());
		}

		_gravityShader->SetInt("nBody", (int)_settings.nParticles);
		_gravityShader->SetFloat("deltaTime", (float)deltaTime);
		if(_settings.nParticles)
			_gravityShader->Dispatch1D(_settings.nParticles, 256);

		_computeShader->SetInt("nBody", (int)_settings.nDisplay);
		_computeShader->SetFloat("L", _settings.zPos);
		_computeShader->Dispatch2D(_width, _height, 16, 16);
	}

private:
	Vega::Shader* _screenShader = new Vega::Shader(screenVert, screenFrag);
	Vega::ComputeShader* _computeShader = new Vega::ComputeShader("gravityDisplay.comp");
	Vega::ComputeShader* _gravityShader = new Vega::ComputeShader("gravity.comp");

	Vega::Texture _image;
	GLuint _height;
	GLuint _width;

	GravitySettings _settings{40000};
	Vega::Collection<Particle> _collection;
	Vega::LinkedSSBO<Particle, GpuParticle> _pBuffer;
};