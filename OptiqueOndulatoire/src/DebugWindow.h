#pragma once

import Vega;
import std;

Vega::Logger Log("MyProject", Vega::Color::BlueLight);

void OnButtonClick() {
	Log.info("A button was clicked.");
}

class DebugWindow : public Vega::GuiCanvas {
public:
	void Draw() override {
		float fps = 1.f / (float)std::max(Vega::Timer::DeltaTime(),.0001);
		float avg = 0.f;

		if (Vega::Timer::FrameCount() < 2) {
			avg = fps;
		}
		else {
			fpsTracker[index] = fps;
			avg = std::reduce(fpsTracker.begin(), fpsTracker.end()) / nFramesCounted;

			if (Vega::Timer::FrameCount() != 2)
				index++;
			index = index % nFramesToAverage;
			if (nFramesCounted < nFramesToAverage)
				nFramesCounted++;
		}


		Vega::Text(std::format("FPS: {:.0f}", avg));
		if (Vega::Button("Click me")) {
			OnButtonClick();
		}
	}

private:
	static inline const int nFramesToAverage = 100;
	int nFramesCounted = 1;
	int index = 0;
	std::array<float, nFramesToAverage> fpsTracker{};

};

class DebugLayer : public Vega::Layer {
public:
	DebugLayer(std::string arg) {
		if (arg == "") {
			Log.error("Default argument is empty ):");
			exit(42);
		}
		else
			Log.warn("Loading default layer with argument '{}'",arg);
	}

	void OnAttach() override {
		Log.trace("Attached debug layer");
		Vega::Systems::Gui()->AttachCanvas<DebugWindow>("Debug window :)");
	}

	void OnUpdate(double deltaTime) override {
	}

	void OnDetach() override {

	}

private:

};