#pragma once
#include <vector>
#include "Vec3Math.h"

struct Component {
};

struct Transform : public Component {
	Vec3<float> position;
	Vec3<float> velocity;
	Vec3<float> acceleration;
};

struct Light : public Component {
	Vec3<> position;
	Vec3<> direction;
	Vec3<> intensity;
};

template <typename... T>
class System {
public:
	virtual void OnCreate(T*...) = 0;
	virtual void OnUpdate(T*...) = 0;
	virtual void OnPhysicsUpdate(T*..., double timeStep) = 0;
	virtual void OnDestroy(T*...) = 0;
};

class FollowLight : public System<Transform, Light> {
public:
	void OnCreate(Transform*, Light*) final
	{
	}

	void OnUpdate(Transform*, Light*) final
	{
	}

	void OnPhysicsUpdate(Transform* rb, Light* l, double timeStep) final
	{
		l->intensity = Vec3(1., .5, 1.);
	}

	void OnDestroy(Transform*, Light*) final
	{
	}
};

class Gravity {
public:
	void OnCreate(Transform*)
	{
	}

	void OnUpdate(Transform*)
	{
	}

	void OnPhysicsUpdate(Transform* rb, float timeStep) const
	{
		rb->position += timeStep * rb->velocity;
		rb->velocity += timeStep * rb->acceleration;
		rb->acceleration = Vec3<float>(0.f, 0.f, -9.8f);
	}

	void OnDestroy(Transform*)
	{
	}
};

static size_t nObjects = 0;

class Entity {
public:
	size_t ID;
	//Transform* transform = nullptr;
	//char _[16]{};
	Entity() {
		ID = nObjects;
		nObjects++;
	}
	//GameObject(std::vector<System*> systems) : _systems(systems) {
	//	ID = nObjects;
	//	nObjects++;
	//}

	//void AddSystem(System* system) {
	//	_systems.push_back(system);
	//}

	//void AddSystems(std::vector<System*> systems) {
	//	_systems.emplace_back(systems);
	//}

	//void OnCreate() {
	//	for (System* system : _systems)
	//	{
	//		system->OnCreate();
	//	}
	//}	
	//void OnUpdate() {
	//	for (System* system : _systems)
	//	{
	//		system->OnUpdate();
	//	}
	//}
	//void OnPhysicsUpdate(double timeStep) {
	//	for (System* system : _systems)
	//	{
	//		system->OnPhysicsUpdate(ID, timeStep);
	//	}
	//}
	//void OnDestroy() {
	//	for (System* system : _systems)
	//	{
	//		system->OnCreate();
	//	}
	//}

private:
	//std::vector<System*> _systems;
};
