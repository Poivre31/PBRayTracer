#pragma once
#include "LampI.h"
#include "LampWindow.h"
#include "../GraphicSettings.h"

import Vega;
import std;

using namespace Vega::Math;

static const auto screenVert = "defaults/default.vert";
static const auto screenFrag = "defaults/screenQuad.frag";
static const auto waveFrag = "wave.frag";
static const auto waveComp = "wave.comp";
static const bool useComputeShader = false;

class WaveDiplay : public Vega::Layer {
public:

	void OnAttach() override {
		_height = Vega::Systems::Window()->Height();
		_width = Vega::Systems::Window()->Width();

		if (useComputeShader) {
			_image = Vega::Texture({ _width ,_height,Vega::Formats::RGBA32F });
			Vega::TextureManager::BindTextureSlot(_image, {Vega::TextureReadMode::Image, 0});
			Vega::TextureManager::BindTextureSlot(_image, { Vega::TextureReadMode::Sampler, 0 });
			Vega::Systems::Application()->AttachLayer<Vega::ScreenQuad>(_screenShader);
		}
		else
			Vega::Systems::Application()->AttachLayer<Vega::ScreenQuad>(_classicShader);

		Vega::Systems::Gui()->AttachCanvas<LampWindow>("Lamps settings", &_settings);

		_collection.Random(_settings.nLamps);
		_lampBuffer.SetData(_collection.Data());
		_lampBuffer.Bind(0);
	}

	void OnResize(GLuint width, GLuint height) override {
		_width = width;
		_height = height;
		if (useComputeShader)
			Vega::TextureManager::UpdateTexture(_image, width, height);
	}

	void OnUpdate(double deltaTime) override {
		if (Vega::Keys::KeyPressed(Vega::Key::R, Vega::KeyMod::ModCtrl)) {
			_classicShader->Reload();
			_screenShader->Reload();
			_computeShader->Reload();
		}

		if (_collection.Size()!=_settings.nLamps) {
			_collection.Random(_settings.nLamps);
		}

		_collection.Update(deltaTime);
		_lampBuffer.SetData(_collection.Data());
		_classicShader->SetInt("nLamps", _settings.nLamps);
		_classicShader->SetInt("renderMode", _settings.renderMode);
		_classicShader->SetFloat ("wavelength", _settings.wavelength);
		_classicShader->SetFloat("intensity", GraphicSystem::Get()->Settings()->luminosity);
		_classicShader->SetFloat("gamma", GraphicSystem::Get()->Settings()->gamma);
		_classicShader->SetFloat("saturation", GraphicSystem::Get()->Settings()->saturation);

		_computeShader->SetInt("nLamps", (int)_collection.Size());

		if(useComputeShader)
			_computeShader->Dispatch2D(_width, _height, 16, 16);
	}

private:
	Vega::Shader* _classicShader = new Vega::Shader(screenVert,waveFrag);
	Vega::Shader* _screenShader = new Vega::Shader(screenVert, screenFrag);
	Vega::ComputeShader* _computeShader = new Vega::ComputeShader(waveComp);

	Vega::Texture _image;
	GLuint _height;
	GLuint _width;

	LampSettings _settings{2};
	Vega::Collection<Lamp> _collection;
	Vega::LinkedSSBO<Lamp, GpuLamp> _lampBuffer;
};