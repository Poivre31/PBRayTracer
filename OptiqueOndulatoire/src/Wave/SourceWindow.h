#pragma once

import Vega;



struct GpuSource {
	float4 position;
	float4 color;
	float phi0;
	int type;
	int pad0;
	int pad1;
};

struct Source : public Vega::Entity {
public:
	Source(Vec3<float> position, Vec3<float> color, float intensity, float wavelength) :
		position(position), color(color), intensity(intensity), wavelength(wavelength) {
	};

	Vec3<float> position;
	Vec3<float> color;
	float intensity;
	float wavelength;

	GpuSource Parse() {
		return GpuSource{
			{position.x, position.y,position.z},
			{color.x * intensity, color.y * intensity, color.z * intensity},
			{0.f},
			{0},
		};
	}
};

struct PlaneSource : public Vega::Entity {
public:
	PlaneSource(Vec3<float> origin, Vec3<float> direction, Vec3<float> color, float intensity, float wavelength) :
		origin(origin), direction(direction), color(color), intensity(intensity), wavelength(wavelength) {
	};

	Vec3<float> direction;
	Vec3<float> origin;
	Vec3<float> color;
	float intensity;
	float wavelength;

	GpuSource Parse() {
		Vec3 dir = direction;
		dir.Normalize();
		float phi0 = (float)std::fmod(dot(dir, origin), 2. * std::numbers::pi);
		phi0 = 0.;
		return GpuSource{
			{dir.x, dir.y,dir.z},
			{color.x * intensity, color.y * intensity, color.z * intensity},
			{phi0},
			{1}
		};
	}
};
enum EditingStatus {
	None,
	Adding,
	Editing,
	Moving,
	Direction,
	Deleting,
	Clearing,
	Measuring,
};

enum Display {
	Intensity,
	Real,
	Imaginary,
};

struct SourceSettings {
	float size = 1.f;
	float intensity = 1.f;
	float gamma = 1.8f;
	float wavelength = 10.f;
	EditingStatus status = None;
	size_t targetIndex = -1;
	size_t hoveredIndex = -1;
	float measuredDistance = 0.f;
	float scale = 1.;
	Vec3<float> origin;
	int displayType = Intensity;
	int editingType = 0;
	Vec3<float> targetColor{ 1.f,1.f,1.f };
	float targetAlpha = 1.f;
	float gridAlpha = .25f;
};

Source CreateSource(float posX, float posY, Vec3<float> color = { 1.f,1.f,1.f }) {
	return Source{ {posX,posY,0.f},{ 1.f,1.f,1.f }, 1.f, 1.f };
}
PlaneSource CreatePlane(float posX, float posY, float dirX, float dirY, Vec3<float> color = { 1.f,1.f,1.f }) {
	return PlaneSource{ {posX,posY,0.f} , {dirX,dirY,0.f},{ 1.f,1.f,1.f }, 1.f, 1.f };
}

class SourceWindow : public Vega::GuiCanvas {
public:
	SourceWindow(SourceSettings* settings) : _settings(settings) {}

	void Draw() override {
		Vega::Combo("Mode d'affichage", { "Intensite", "Partie reelle", "Partie imaginaire" }, _settings->displayType);
		Vega::Slider("Taille des widgets", _settings->size, .5f, 3.f);
		Vega::Separator("Parametres d'affichage");
		Vega::Slider("Intensite", _settings->intensity, 0, 2);
		Vega::Slider("Gamma", _settings->gamma, .5, 3);
		Vega::Slider("Grid alpha", _settings->gridAlpha, .0f, 1.f);

		Vega::Separator("Parametres des sources");
		if (Vega::Button("Ajouter une source spherique") or Vega::Keys::Pressed(Vega::Key::Space) and _settings->status != Adding) {
			_settings->status = Adding;
			_settings->editingType = 0;
		}
		if (Vega::Button("Ajouter une onde plane")) {
			_settings->status = Adding;
			_settings->editingType = 1;
		}
		if (Vega::Button("Supprimer tout")) {
			_settings->status = Clearing;
		}
		static std::array<float,4> color {1, 1, 1, 1} ;
		Vega::ColorPicker("Source color", _settings->targetColor);
		Vega::Slider("Longueur d'onde", _settings->wavelength, 5.f, 200.f);
		Vega::Text(std::format("Distance mesuree: {:.3f}", _settings->measuredDistance));
	}

private:
	SourceSettings* _settings;
};