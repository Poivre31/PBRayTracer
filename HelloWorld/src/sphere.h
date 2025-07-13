#pragma once
#include <vector>

struct Sphere {
	float position[3];
	float radius;
	float color[3];
};

struct SphereBuffer {
	float position[256][3];
	float radius[256];
	float color[256][3];
};

SphereBuffer parseSpheres(std::vector<Sphere>& spheres) {
	SphereBuffer buffer{};
	for (size_t i = 0; i < spheres.size(); i++)
	{
		buffer.position[i][0] = spheres[i].position[0];
		buffer.position[i][1] = spheres[i].position[1];
		buffer.position[i][2] = spheres[i].position[2];
		buffer.radius[i] = spheres[i].radius;
		buffer.color[i][0] = spheres[i].color[0];
		buffer.color[i][1] = spheres[i].color[1];
		buffer.color[i][2] = spheres[i].color[2];
	}
	return buffer;
}