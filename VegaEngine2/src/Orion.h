#pragma once
import Vega;
using namespace Vega::Math;

auto OrionLog = Vega::Logger("Orion", Vega::Color::BlueLight);

class Orion : public Vega::Application {
public:

	Orion() {
		OrionLog.trace("Opened Orion Ray Tracer");
		std::exp(.2);
		Vec3<double> a = { 0.1,2.,4. };
		a = a * a;
		a = sin(a);
		a.Print();
		std::cout << std::sin(5.) << std::endl;
		//auto imgui = new Vega::ImGuiLayer(GetWindow());
		//AttachLayer(imgui);
	}

	~Orion() override {
		OrionLog.trace("Closed Orion Ray Tracer");
	}

private:
};

std::unique_ptr<Vega::Application> Vega::CreateApplication() {
	return std::make_unique<Orion>();
}