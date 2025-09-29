#pragma once
import Vega;
import std;

using namespace Vega::Math;

struct GPUBoid {
	float4 position;
};

class Boid : public Vega::Entity {
public:

	GPUBoid Parse() const {
		auto position = (Vec3<float>)GetPosition();
		return GPUBoid{ { position.x, position.y, position.z, 0. } };
	}

	void Random() override {
		_rb.SetPosition(Random::Rand3f(0., 1.));
		_rb.SetVelocity(.01 * Random::Rand3f(-1., 1.));
		_rb.SetMass(Random::Randf(1., .2));
	}

	void OnUpdate(double deltaTime) override {
		Vec3<double> position = _rb.GetPosition();
		Vec3<double> velocity = _rb.GetVelocity();

		std::function bounce = [](double pos, double vel) {
			if (pos > 1.)
				vel = -abs(vel);
			else if (pos < 0.)
				vel = abs(vel);

			return vel;
			};

		velocity = ApplyElementWise(position, velocity, bounce);

		if (position.x > 1.) {
			velocity.x = -abs(velocity.x);
		}
		else if (position.x < 0.) {
			velocity.x = abs(velocity.x);
		}
		if (position.y > 1.) {
			velocity.y = -abs(velocity.y);
		}
		else if (position.y < 0.) {
			velocity.y = abs(velocity.y);
		}
		if (position.z > 1.) {
			velocity.z = -abs(velocity.z);
		}
		else if (position.z < 0.) {
			velocity.z = abs(velocity.z);
		}
		_rb.SetVelocity(velocity);
		_rb.AddForce(-5 * velocity * velocity.Norm());
		_rb.Update(deltaTime);
	}

	Vec3<double> GetPosition() const {
		return _rb.GetPosition();
	}

	Vega::CRigidBody& GetRB() {
		return _rb;
	}

private:
	Vega::CRigidBody _rb;

};


class BoidsLayer : public Vega::Layer {
public:

	BoidsLayer() {};

	void OnAttach() override {
		_boids.Random(1000);

		_boidsBuffer.Reserve(_boids.Size());
		_boidsBuffer.Bind(7);

		_compute = std::make_unique<Vega::ComputeShader>("boids/boids.comp");
		_compute->SetInt("nBoids", (int)_boids.Size());

		_width = Vega::Systems::Window()->Width();
		_height = Vega::Systems::Window()->Height();

		_image = Vega::Texture({ _width, _height, Vega::Formats::RGBA32F });

		Vega::TextureManager::BindTextureSlot(_image, { Vega::TextureReadMode::Image,0 });
		_compute->SetInt("image", 0);
	}

	void OnUpdate(double deltaTime) override {
		_boids.Update(deltaTime);
		double energy = 0;
		for (auto& boid1 : _boids.Data()) {
			for (auto& boid2 : _boids.Data()) {
				if (&boid1 == &boid2) continue;
				double d = (boid2.GetRB().GetPosition() - boid1.GetRB().GetPosition()).Norm();
				Vec3<double> force = (boid2.GetRB().GetPosition() - boid1.GetRB().GetPosition()) / d;
				force *= 0.00001 * boid1.GetRB().GetMass() * boid2.GetRB().GetMass();
				d = std::max(.015, d);
				force /= (d * d);
				boid1.GetRB().AddForce(force);
				energy += 0.00001 * boid1.GetRB().GetMass() * boid2.GetRB().GetMass() / d;
			}
			boid1.GetRB().Update(deltaTime);
			energy += .5 * boid1.GetRB().GetMass() * boid1.GetRB().GetVelocity().Norm2();
		}
		if (Vega::Timer::FrameCount() % 200 == 0) {
			OrionLog.debug("Energy = {}", energy);
		}
		_boidsBuffer.UpdateData(_boids.Data(), _boids.Size(), 0);


		if (ImGui::IsKeyPressed(ImGuiKey_R)) {
			_compute->Reload();
			_compute->SetInt("nBoids", (int)_boids.Size());
		}
		_compute->Dispatch2D(_width, _height, 8, 8);
	}

	void OnResize(GLuint width, GLuint height) override {
		_width = width;
		_height = height;
		Vega::TextureManager::UpdateTexture(_image, width, height);
	}

private:
	GLuint _width = 0;
	GLuint _height = 0;
	Vega::Texture _image;

	std::unique_ptr<Vega::ComputeShader> _compute;
	Vega::Collection<Boid> _boids;
	Vega::LinkedSSBO<Boid, GPUBoid> _boidsBuffer;
};