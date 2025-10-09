#pragma once
#include "SourceWindow.h"
#include "../GraphicSettings.h"

import Vega;
import std;

using namespace Vega::Math;

static const auto screenVert = "defaults/default.vert";
static const auto screenFrag = "proceduralPrimitive.frag";
static const auto waveFrag = "wave.frag";

class WaveDisplay : public Vega::Layer {
public:

	void OnAttach() override {
		_height = Vega::Systems::Window()->Height();
		_width = Vega::Systems::Window()->Width();

		_sourcesBuffer.Reserve(1);
		_sourcesBuffer.Bind(0);
		_planesBuffer.Reserve(1);
		_planesBuffer.Bind(1);

		Vega::Systems::Gui()->AttachCanvas<SourceWindow>("Parametres", &_settings);
	}

	void OnResize(GLuint width, GLuint height) override {
		_width = width;
		_height = height;
	}

	void OnUpdate(double deltaTime) override {
		auto* drawStack = Vega::Systems::DrawStack();
		Vega::Shader* shader = drawStack->GetShader();

		auto [mosX, mosY] = Vega::Keys::MousePos();
		mosY = _height - mosY;

		Vec3 origin = { _width / 2.f, _height / 2.f,0.f };

		static Vec3 offset(0.f);
		static Vec3 editingOrigin(0.f);
		if (_settings.status == Clearing) {
			_sources.clear();
			_planes.clear();
			_settings.status = None;
		}

		else if (_settings.status == Editing) {
			Vec3 position = { (float)mosX,(float)mosY,0.f };
			position = ((position - origin) * _settings.scale + _settings.origin);
			Vec3<float> objectPosition;
			if (_settings.editingType == 0) {
				objectPosition = _sources[_settings.targetIndex].position;
			}
			if (_settings.editingType == 1) {
				objectPosition = _planes[_settings.targetIndex].origin;
			}
			if (Vega::Keys::KeyPressed(Vega::Key::MouseLeft) && !Vega::Keys::HoveringWindow()) {

				float d = (objectPosition - position).Norm();
				if (d > 10.f * _settings.size) {
					_settings.status = None;
					_settings.targetIndex = -1;
				}
			}
		}

		float scrollSpeed = 1.07f;
		if (Vega::Keys::MouseWheel() > 0) {
			_settings.scale /= scrollSpeed;
		}
		else if (Vega::Keys::MouseWheel() < 0) {
			_settings.scale *= scrollSpeed;
		}
		if (Vega::Keys::KeyDown(Vega::Key::Z) > 0) {
			_settings.origin.y += 2 * _settings.scale;
		}
		if (Vega::Keys::KeyDown(Vega::Key::S) > 0) {
			_settings.origin.y -= 2 * _settings.scale;
		}
		if (Vega::Keys::KeyDown(Vega::Key::Q) > 0) {
			_settings.origin.x -= 2 * _settings.scale;
		}
		if (Vega::Keys::KeyDown(Vega::Key::D) > 0) {
			_settings.origin.x += 2 * _settings.scale;
		}
		if (Vega::Keys::KeyPressed(Vega::Key::Space)) {
			_settings.status = Adding;
		}
		if (_settings.status == None && !Vega::Keys::HoveringWindow()) {

			Vec3 position = { (float)mosX,(float)mosY,0.f };
			position = ((position - origin) * _settings.scale + _settings.origin);
			size_t i = 0;
			_settings.hoveredIndex = -1;
			for (auto& o : _sources)
			{
				float d = (o.position - position).Norm();
				if (d < 10.f * _settings.size * _settings.scale) {
					if (Vega::Keys::KeyPressed(Vega::Key::MouseLeft) && !Vega::Keys::MouseDoubleClicked()) {
						_settings.status = Moving;
						_settings.targetIndex = i;
						_settings.targetColor = o.color;
						offset = o.position - position;
						editingOrigin = o.position;
						_settings.editingType = 0;
					}
					else {
						_settings.hoveredIndex = i;
						_settings.editingType = 0;
					}
				}
				i++;
			}

			i = 0;
			for (auto& o : _planes)
			{
				float d = (o.origin - position).Norm();
				if (d < 8.f * _settings.size * _settings.scale) {
					if (Vega::Keys::KeyPressed(Vega::Key::MouseLeft) && !Vega::Keys::MouseDoubleClicked()) {
						_settings.status = Moving;
						_settings.targetIndex = i;
						_settings.targetColor = o.color;
						offset = o.origin - position;
						editingOrigin = o.origin;
						_settings.editingType = 1;
					}
					else {
						_settings.hoveredIndex = i;
						_settings.editingType = 1;
					}
				}
				d = (o.origin + o.direction - position).Norm();
				if (d < 6.f * _settings.size * _settings.scale) {
					if (Vega::Keys::KeyPressed(Vega::Key::MouseLeft) && !Vega::Keys::MouseDoubleClicked()) {
						_settings.status = Direction;
						_settings.targetIndex = i;
						_settings.targetColor = o.color;
						offset = o.origin + o.direction - position;
						editingOrigin = o.origin;
						_settings.editingType = 1;
					}
					else {
						_settings.hoveredIndex = i;
						_settings.editingType = 1;
					}
				}
				i++;
			}


		}
		if (Vega::Keys::MouseDoubleClicked()) {
			Vec3 position = { (float)mosX,(float)mosY,0.f };
			size_t i = 0;
			position = ((position - origin) * _settings.scale + _settings.origin);
			for (auto& o : _sources)
			{
				float d = (o.position - position).Norm();
				if (d < 10.f * _settings.size * _settings.scale) {
					_settings.status = Deleting;
					_settings.targetIndex = i;
				}
				i++;
			}
			i = 0;
			for (auto& o : _planes)
			{
				float d = (o.origin - position).Norm();
				if (d < 8.f * _settings.size * _settings.scale) {
					_settings.status = Deleting;
					_settings.targetIndex = i;
				}
				i++;
			}
		}

		static int mosOriginX = 0, mosOriginY = 0;
		auto [dx, dy] = Vega::Keys::MouseDelta();
		if (_settings.status == None && !Vega::Keys::HoveringWindow()) {
			if (Vega::Keys::KeyDown(Vega::Key::MouseLeft)) {
				_settings.origin.x -= dx * _settings.scale;
				_settings.origin.y += dy * _settings.scale;
			}
			if (Vega::Keys::KeyReleased(Vega::Key::MouseLeft)) {
				dx = 0; dy = 0;
			}
		}
		if (_settings.status == None || _settings.status == Editing  && !Vega::Keys::HoveringWindow()) {
			if (Vega::Keys::KeyPressed(Vega::Key::MouseRight)) {
				if (_settings.status == Editing) {
					_settings.status = None;
					_settings.targetIndex = -1;
				}
				Vec3 position = { (float)mosX,(float)mosY,0.f };

				position = ((position - origin) * _settings.scale + _settings.origin);

				if (Vega::Keys::KeyDown(Vega::Key::Ctrl)) {
					position = (position / 100).Round() * 100;
				}

				if (Vega::Keys::KeyDown(Vega::Key::Shift)) {
					for (auto& o : _sources)
					{
						float d = (o.position - position).Norm();
						if (d < 10.f * _settings.size) {
							position = o.position;
						}
					}
				}
				_ruler.origin = position;
				_settings.status = Measuring;
			}
		}


		if (_settings.status == Measuring) {
			Vec3 position = { (float)mosX,(float)mosY,0.f };
			position = ((position - origin) * _settings.scale + _settings.origin);
			if (Vega::Keys::KeyDown(Vega::Key::Ctrl)) {
				position = (position / 100).Round() * 100;
			}
			static int axis = 0;
			if (Vega::Keys::KeyPressed(Vega::Key::X)) {
				if (axis == 1)
					axis = 0;
				else axis = 1;
			}
			if (Vega::Keys::KeyPressed(Vega::Key::Y)) {
				if (axis == 2)
					axis = 0;
				else axis = 2;
			}
			if (axis == 1)
				position.y = _ruler.origin.y;
			if (axis == 2)
				position.x = _ruler.origin.x;

			if (Vega::Keys::KeyDown(Vega::Key::Shift)) {
				for (auto& o : _sources)
				{
					float d = (o.position - position).Norm();
					if (d < 10.f * _settings.size) {
						position = o.position;
					}
				}
			}
			_ruler.endpoint = position;
			drawStack->Add(_ruler);
			if (Vega::Keys::KeyStatus(Vega::Key::MouseRight, Vega::KeyEvent::Released)) {
				//_settings.status = None;
				//axis = 0;
			}
			_settings.measuredDistance = (_ruler.endpoint - _ruler.origin).Norm();
		}

		if (_settings.status == Adding) {
			Vec3 position = { (float)mosX,(float)(mosY),0.f };
			position = ((position - origin) * _settings.scale + _settings.origin);
			if (Vega::Keys::KeyDown(Vega::Key::Ctrl)) {
				position = (position / 100).Round() * 100;
			}

			if (_settings.editingType == 0) {
				drawStack->Add(Vega::Donut{ position,2.f * _settings.size,4.f * _settings.size }, Vec3{ .1f }, .8f);
				drawStack->Add(Vega::Donut{ position,8.f * _settings.size,10.f * _settings.size }, Vec3{ .1f }, .8f);
				drawStack->Add(Vega::Donut{ position,4.f * _settings.size,8.f * _settings.size }, Vec3{ 1.f }, .8f);
			}

			if (_settings.editingType == 1) {
				drawStack->Add(Vega::Donut{ position,6.f * _settings.size,8.f * _settings.size }, Vec3{ .1f }, .8f);
				drawStack->Add(Vega::Circle{ position,6.f * _settings.size }, Vec3{ 1.f }, .8f);
			}

			if (Vega::Keys::KeyPressed(Vega::Key::MouseLeft)) {
				if (_settings.editingType == 0) {
					_sources.push_back(CreateSource(position.x, position.y));
					_settings.targetIndex = _sources.size() - 1;
				}
				if (_settings.editingType == 1) {
					_planes.push_back(CreatePlane(position.x, position.y, 100, 0));
					_settings.targetIndex = _planes.size() - 1;
				}
				_settings.status = Editing;
			}

			if (Vega::Keys::KeyDown(Vega::Key::Esc)) {
				_settings.status = None;
			}
		}

		else if (_settings.status == Moving) {
			Vec3 position = Vec3{ (float)mosX,(float)(mosY),0.f };
			position = offset + ((position - origin) * _settings.scale + _settings.origin);
			static int axis = 0;
			if (Vega::Keys::KeyPressed(Vega::Key::X)) {
				if (axis == 1)
					axis = 0;
				else axis = 1;
			}
			if (Vega::Keys::KeyPressed(Vega::Key::Y)) {
				if (axis == 2)
					axis = 0;
				else axis = 2;
			}
			if (axis == 1)
				position.y = editingOrigin.y;
			if (axis == 2)
				position.x = editingOrigin.x;
			if (Vega::Keys::KeyDown(Vega::Key::Ctrl)) {
				position = (position / 100.f).Round() * 100.f;
				offset = 0;
			}

			if (_settings.editingType == 0) {
				_sources[_settings.targetIndex].position = position;
			}
			if (_settings.editingType == 1) {
				_planes[_settings.targetIndex].origin = position;
			}
			if (Vega::Keys::KeyStatus(Vega::Key::MouseLeft, Vega::KeyEvent::Released)) {
				_settings.status = Editing;
				axis = 0;
			}
		}

		else if (_settings.status == Editing) {
			Vec3 position = { (float)mosX,(float)mosY,0.f };
			position = ((position - origin) * _settings.scale + _settings.origin);
			Vec3<float> objectPosition;
			if (_settings.editingType == 0) {
				_sources[_settings.targetIndex].color = _settings.targetColor;
				objectPosition = _sources[_settings.targetIndex].position;
			}
			if (_settings.editingType == 1) {
				_planes[_settings.targetIndex].color = _settings.targetColor;
				objectPosition = _planes[_settings.targetIndex].origin;
			}
			if (Vega::Keys::KeyPressed(Vega::Key::MouseLeft) && !Vega::Keys::HoveringWindow()) {

				float d = (objectPosition - position).Norm();
				if (d < 10.f * _settings.size) {
					_settings.status = Moving;
					offset = objectPosition - position;
					editingOrigin = objectPosition;
				}
			}
		}

		else if (_settings.status == Direction) {
			Vec3 position = Vec3{ (float)mosX,(float)(mosY),0.f };
			position = offset + ((position - origin) * _settings.scale + _settings.origin);
			if (Vega::Keys::KeyDown(Vega::Key::Ctrl)) {
				position = (position / 100).Round() * 100;
			}
			static int axis = 0;
			if (Vega::Keys::KeyPressed(Vega::Key::X)) {
				if (axis == 1)
					axis = 0;
				else axis = 1;
			}
			if (Vega::Keys::KeyPressed(Vega::Key::Y)) {
				if (axis == 2)
					axis = 0;
				else axis = 2;
			}
			if (axis == 1)
				position.y = _ruler.origin.y;
			if (axis == 2)
				position.x = _ruler.origin.x;
			_planes[_settings.targetIndex].direction = position- _planes[_settings.targetIndex].origin;
			if (Vega::Keys::KeyStatus(Vega::Key::MouseLeft, Vega::KeyEvent::Released)) {
				_settings.status = Editing;
				axis = 0;
			}
		}

		else if (_settings.status == Deleting) {
			if(_settings.editingType == 0)
				_sources.erase(_sources.begin() + _settings.targetIndex);
			if (_settings.editingType == 1)
				_planes.erase(_planes.begin() + _settings.targetIndex);
			_settings.status = None;
			_settings.targetIndex = -1;
		}

		size_t i = 0;
		for (auto& o : _sources)
		{
			drawStack->Add(Vega::Donut{ {o.position.x,o.position.y,o.position.z },2.f * _settings.size,4.f * _settings.size }, Vec3{ .1f }, .35f);
			drawStack->Add(Vega::Donut{ {o.position.x,o.position.y,o.position.z },8.f * _settings.size,10.f * _settings.size }, Vec3{ .1f }, .35f);
			Vec3 color = Vec3(1.f);
			if (i == _settings.targetIndex && _settings.editingType == 0) {
				color = Vec3(1.f, .35f, .0f);
			}
			if (i == _settings.hoveredIndex && _settings.editingType == 0) {
				//color = Vec3(.8f, .6f, .4f);
			}
			drawStack->Add(Vega::Donut{ {o.position.x,o.position.y,o.position.z },4.f * _settings.size,8.f * _settings.size }, color, .35f);
			i++;
		}
		i = 0;
		for (auto& o : _planes)
		{
			drawStack->Add(Vega::Donut{ {o.origin.x,o.origin.y,o.origin.z },6.f * _settings.size,8.f * _settings.size }, Vec3{ .1f }, .35f);
			drawStack->Add(Vega::Donut{ Vec3{o.origin.x,o.origin.y,o.origin.z } + Vec3{o.direction.x,o.direction.y,o.direction.z },6.f * _settings.size,8.f * _settings.size }, Vec3{ .1f }, .35f);
			Vec3 color = Vec3(1.f);
			if (i == _settings.targetIndex && _settings.editingType == 1) {
				color = Vec3(1.f, .35f, .0f);
			}
			if (i == _settings.hoveredIndex && _settings.editingType == 1) {
				//color = Vec3(.8f, .6f, .4f);
			}
			drawStack->Add(Vega::Circle{ {o.origin.x,o.origin.y,o.origin.z },6.f * _settings.size }, color, .35f);
			drawStack->Add(Vega::Circle{ Vec3{o.origin.x,o.origin.y,o.origin.z } + Vec3{o.direction.x,o.direction.y,o.direction.z },6.f * _settings.size }, color, .35f);
			drawStack->Add(Vega::Arrow{ {o.origin.x,o.origin.y,o.origin.z },Vec3{o.origin.x,o.origin.y,o.origin.z }+Vec3{o.direction.x,o.direction.y,o.direction.z },4.f * _settings.size }, color, .35f);
			i++;
		}
		_sourcesBuffer.SetData(_sources);
		_planesBuffer.SetData(_planes);
		shader->SetInt("nSources", _sources.size());
		shader->SetInt("nPlanes", _planes.size());
		shader->SetInt("displayType", _settings.displayType);
		shader->SetFloat("gamma", _settings.gamma);
		shader->SetFloat("intensity", _settings.intensity);
		shader->SetFloat("wavelength", _settings.wavelength);
		shader->SetFloat("scale", _settings.scale);
		shader->SetFloat2("origin", { _settings.origin.x, _settings.origin.y });
	}

private:
	Vega::Texture _image;
	GLuint _height;
	GLuint _width;

	SourceSettings _settings;

	Vega::Line _ruler{ .width = 2 };
	std::vector<Source> _sources;
	std::vector<PlaneSource> _planes;
	Vega::LinkedSSBO<Source, GpuSource> _sourcesBuffer;
	Vega::LinkedSSBO<PlaneSource, GpuSource> _planesBuffer;
};