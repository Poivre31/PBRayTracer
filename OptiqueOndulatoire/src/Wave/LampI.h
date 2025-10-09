#pragma once
#include "../DebugWindow.h"

import Vega;

using namespace Vega::Math;

struct GpuLamp {
	float4 position; // Always use float4/int4 for vector types, for alignement issues
	float4 velocity;
};

class Lamp : public Vega::Entity {
public:
	void Random() override {
		_rigidBody.SetPosition(Random::Rand3f(0., 1.));
		_rigidBody.SetVelocity(.2f * Random::Rand3fUnitSphere<double>());
	}

	void OnCreate() override {
		Log.debug("Created entity {}", GetID());
	}

	void OnUpdate(double deltaTime) override {
		_rigidBody.Update(deltaTime);

		auto position = _rigidBody.GetPosition();
		auto velocity = _rigidBody.GetVelocity();
		std::function bounce = [](double x, double vx) {
			if (x > 1.) return -abs(vx);
			if (x < 0.) return abs(vx);
			else return vx;
			};
		velocity = ApplyElementWise(position, velocity, bounce);
		_rigidBody.SetVelocity(velocity);
	}

	void OnDestroy() override {
		Log.debug("Destroyed entity {}", GetID());
	}

	GpuLamp Parse() const {
		auto position = (Vec3<float>)_rigidBody.GetPosition();
		auto velocity = (Vec3<float>)_rigidBody.GetVelocity();
		return GpuLamp{
			position.x,position.y,position.z,0.,
			velocity.x,velocity.y,velocity.z,0.
		};
	}

private:
	Vega::CRigidBody _rigidBody;
};

enum : int {
	RenderColorPosition = 0,
	RenderColorCrossSpeed,
};
