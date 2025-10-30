#pragma once
#include "SourceWindow.h"
#include "../GraphicSettings.h"

import Vega;
import std;

static const auto screenVert = "defaults/default.vert";
static const auto screenFrag = "proceduralPrimitive.frag";
static const auto waveFrag = "wave.frag";

class WaveDisplay : public Vega::Layer {
public:

	void OnAttach() override {
		_viewport = Vega::Systems::Gui()->GetViewport();

		_shader = new Vega::Shader(screenVert, waveFrag);
		_viewport->AddShader(_shader);

		_sourcesBuffer.Reserve(1);
		_sourcesBuffer.Bind(0);

		_sourcePositions.push_back(new Vega::DonutHandle());
		_viewport->AddWidget(_sourcePositions[0]);

		Vega::Systems::Gui()->AttachCanvas<SourceWindow>("Parametres", &_settings);

	}

	void OnUpdate(double deltaTime) override {
		auto* settings = _viewport->GetGridSettings();
		_sources.clear();

		if (_settings.status == EditingStatus::Clearing)
			_sourcePositions.clear();

		size_t n = _sourcePositions.size();

		if (_settings.status == EditingStatus::Adding) {
			auto* handle = new Vega::DonutHandle();
			handle->SetStatus(Vega::Status::Moving);
			_sourcePositions.push_back(handle);
			n++;
			_viewport->AddWidget(_sourcePositions[n - 1]);
			_settings.status = EditingStatus::None;
		}

		for (size_t i = 0; i < n; i++)
		{
			if (_sourcePositions[i]->GetStatus() == Vega::Status::Deleting) {
				n--;
				_sourcePositions.erase(_sourcePositions.begin() + i);
				continue;
			}

			_sources.push_back(Source(_sourcePositions[i]->Position(), {1.f,.5f,1.f}, 1, 1));
		}



		_viewport->GetGridSettings()->alpha = _settings.gridAlpha;

		_sourcesBuffer.SetData(_sources);
		_shader->SetInt("nSources", (int)_sources.size());
		_shader->SetInt("displayType", _settings.displayType);
		_shader->SetFloat("gamma", _settings.gamma);
		// TO FIX: BETTER NON LINEAR INTENSITY HANDLING
		_shader->SetFloat("intensity", std::exp(_settings.intensity*4)-1);
		_shader->SetFloat("wavelength", _settings.wavelength);
		_shader->SetFloat("scale", (float)settings->scale);
		_shader->SetFloat2("origin", { (float)settings->origin.x, (float)settings->origin.y});
	}

private:
	Vega::Shader* _shader;
	Vega::Viewport* _viewport;
	GLuint _height;
	GLuint _width;
	Vec2<GLuint> _size;

	SourceSettings _settings;

	std::vector<Source> _sources;
	std::vector<Vega::DonutHandle*> _sourcePositions;
	Vega::LinkedSSBO<Source, GpuSource> _sourcesBuffer;
};