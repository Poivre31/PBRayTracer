export module Gui:Grid;
import Entities;
import :Primitives;
import Io;
import Math;
import Render;
import std;

double scrollSpeed = 1.05;
double spanSpeed = 2.;
double minScale = 0.01;
double maxScale = 100;

struct GridSettings {
	int defaultSize = 100;
	double gridSize = (double)defaultSize;
	Vec2<int> screenSize;
	Vec2<double> origin;
	double scale = 1.;
	bool interactible = true;
	bool moving = false;
	float alpha = .25;
};

export namespace Vega {

	class Grid {
	public:
		GridSettings* Settings() {
			return &_settings;
		}

		Vec2<float> ToWorld(Vec2<float> pos) {
			pos *= _settings.scale;
			pos -= _settings.origin;
			return pos;
		}

		Vec2<float> ToScreen(Vec2<float> pos) {
			pos += _settings.origin;
			pos /= _settings.scale;
			return pos;
		}

		void Update(Vec2<int> _size, Shader* shader) {
			_settings.screenSize = _size;
			if (!_settings.interactible)
				return;

			if (Keys::Pressed(Key::P)) {
				_settings.scale = 1.;
				_settings.origin = { 0.,0. };
			}

			float scrollSpeed = 1.07f;
			if ((Keys::MouseWheel() > 0 or Keys::Pressed(Key::Plus)) and Keys::HoveringViewport()) {
				_settings.scale /= scrollSpeed;
			}
			else if (Keys::MouseWheel() < 0 && Keys::HoveringViewport()) {
				_settings.scale *= scrollSpeed;
			}
			_settings.scale = std::min(std::max(_settings.scale, minScale), maxScale);

			auto [dx, dy] = Keys::MouseDelta();
			if (Keys::Pressed(Key::MouseLeft) && Keys::HoveringViewport()) {
				_settings.moving = true;
			}
			if (Keys::Released(Key::MouseLeft)) {
				_settings.moving = false;
			}
			if (_settings.moving && _settings.interactible) {
				_settings.origin.x += dx * _settings.scale;
				_settings.origin.y -= dy * _settings.scale;
			}
			if (Keys::Down(Key::D) xor Keys::Down(Key::Q)) {
				if (Keys::Down(Key::D))
					_settings.origin.x -= spanSpeed;
				else
					_settings.origin.x += spanSpeed;
			}
			if (Keys::Down(Key::Z) xor Keys::Down(Key::S)) {
				if (Keys::Down(Key::Z))
					_settings.origin.y -= spanSpeed;
				else
					_settings.origin.y += spanSpeed;
			}

			int k = 4;
			int power = int(std::round(std::log(_settings.scale) / std::log(k)));
			_settings.gridSize = _settings.defaultSize * pow(k, power) / _settings.scale;

			shader->SetFloat2("origin", Vec2<float>(_settings.origin).ToArray());
			shader->SetFloat("scale", (float)_settings.scale);
			shader->SetFloat("gridSize", (float)_settings.gridSize);
			shader->SetFloat("visibility", _settings.alpha);
		}

	private:
		GridSettings _settings;
	};

}