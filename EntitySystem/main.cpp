#include "Entity.h"
#include "Timer.h"
#include "math.h"
#include <omp.h>
#include "thread_pool.h"

//template <typename T>
//static void OnPhysicsUpdate(T& component, double timeStep)
//{
//	component.acceleration = Vec3(0., 0., -9.8);
//	component.velocity += timeStep * component.acceleration;
//	component.position += timeStep * component.velocity;
//}

int main() {
	std::vector<Entity> objects(10000000);
	std::vector<Transform> transforms(10000000);
	//Transform* transforms2 = (Transform*)_aligned_malloc(10000000 * sizeof(Transform), 64);
	//if (!transforms2) {
	//	return -1;
	//}
	//for (int i = 0; i < objects.size(); i++)
	//{
	//	objects[i].transform = &transforms[i];
	//}
	//Transform transforms[10000];
	std::vector<System<>*> systems;
	//systems.push_back(new Gravity());

	auto system = Gravity();
	auto light = FollowLight();

	//for (size_t i = 0; i < 100; i++)
	//{
	//	scene.objects[i].AddSystem(new Gravity());
	//}

	auto LIGHT = Light();

	double deltaTime = 1./10;
	Timer::Init();
	for (int i = 0; i < 10000000; i++)
	{
		system.OnPhysicsUpdate(&transforms[objects[i].ID], (float)deltaTime);
		//std::swap(transforms[3], transforms[10000000 - 1]);
		//std::swap(objects[3], objects[10000000 - 1]);
		//std::swap(objects[3].transform, objects[10000000 - 1].transform);
	}
	transforms[10].position.Print();
	std::cout << "Time: " << Timer::GetTimeSinceInit()*1000;
}