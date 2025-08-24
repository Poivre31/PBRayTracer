#pragma once
#include "intersectionTest.h"
#include "imgui.h"
#include "camera.h"

namespace Axis {
	enum Axis {
		none = -1,
		x = 0,
		y = 1,
		z = 2,
		invalid = 3,
	};
}

float intersect(Object& object, Ray ray) {
	float hitDist = -1;
	if(object.type == 0) hitDist = intersectSphere(object.transform, ray);
	else if(object.type == 1) hitDist = intersectCube(object.transform, ray);
	else if (object.type == 2) hitDist = intersectPlane(object.transform, ray);
	else if (object.type == 3) hitDist = intersectCircle(object.transform, ray);
	else if (object.type == 4) hitDist = intersectCylinder(object.transform, ray);
	else if (object.type == 5) hitDist = intersectCone(object.transform, ray);
	else if (object.type == 6) hitDist = intersectPyramid(object.transform, ray);

	//switch (object.type) {
	//case(ObjectType::sphere):
	//	hitDist = intersectSphere(object.transform, ray); break;
	//case(ObjectType::cube):
	//	hitDist = intersectCube(object.transform, ray); break;
	//case(ObjectType::plane):
	//	hitDist = intersectPlane(object.transform, ray); break;
	//case(ObjectType::circle):
	//	hitDist = intersectCircle(object.transform, ray); break;
	//case(ObjectType::cylinder):
	//	hitDist = intersectCylinder(object.transform, ray); break;
	//case(ObjectType::cone):
	//	hitDist = intersectCone(object.transform, ray); break;
	//case(ObjectType::pyramid):
	//	hitDist = intersectPyramid(object.transform, ray); break;
	//}
	return hitDist;
}

Vec3 rotateY(Vec3 vec, float alpha) {
	float x = cos(alpha) * vec.x + sin(alpha) * vec.z;
	float z = -sin(alpha) * vec.x + cos(alpha) * vec.z;
	return Vec3(x, vec.y, z);
}

Vec3 rotateZ(Vec3 vec, float alpha) {
	float x = cos(alpha) * vec.x - sin(alpha) * vec.y;
	float y = sin(alpha) * vec.x + cos(alpha) * vec.y;
	return Vec3(x, y, vec.z);
}

Ray getRay(Camera& camera, Renderer& UI) {
	ImVec2 mousePos = ImGui::GetMousePos();

	float screenPosX = 2 * UI.io->MousePos.x / UI.width - 1;
	float screenPosY = 1 - 2 * UI.io->MousePos.y / UI.height;

	float scale = tan(camera.vFov * M_PI / 360);
	float x = -screenPosY * scale;
	float y = -screenPosX * scale * float(UI.width) / UI.height;

	Ray ray;
	ray.origin = camera.position;
	ray.direction = Vec3(x, y, 1.f);
	ray.direction.Normalize();
	ray.direction = rotateY(ray.direction, camera.direction.y);
	ray.direction = rotateZ(ray.direction, camera.direction.z);

	return ray;
}

std::tuple<int, int> findHitObject(Scene& scene, Camera& camera, Renderer& UI) {
	Ray ray = getRay(camera, UI);

	int index = -1;
	int type = -1;
	float depth = 1000;

	int i = 0;
	for (Object object : scene.objects)
	{
		float hitDist = intersect(object, ray);
		if (hitDist > 0 && hitDist < depth) {
			index = i;
			type = object.type;

			depth = hitDist;
		}
		i++;
	}

	return {index, type};
}

int findSelectedAxis(Scene& scene, Renderer& UI, Camera& camera) {
	Transform object{};
	float depth = 1000;
	int axis = Axis::none;
	///CHECK
	Ray ray = getRay(camera, UI);
	object.position = scene.objects[scene.selectedIndex].transform.position;
	Vec3 position = Vec3(object.position.x, object.position.y, object.position.z);
	float objDist = sqrt(dot(position - camera.position, position - camera.position));

	object.scale = { .02f * objDist,.02f * objDist,.02f * objDist };
	object.rotation = { 0, 0 };
	float dist = intersectSphere(object, ray);
	if (dist > 0 && dist < depth) {
		axis = Axis::none;
		return axis;
	}
	object.position.x = position.x;

	object.position.x += 0.08 * objDist;
	object.scale = { .01f * objDist,.01f * objDist,.08f * objDist };
	object.rotation = { M_PI / 2, 0 };
	dist = intersectCylinder(object, ray);
	if (dist > 0 && dist < depth) {
		axis = Axis::x;
		depth = dist;
	}
	object.position.x = position.x;

	object.position.y += 0.08 * objDist;
	object.scale = { .01f * objDist,.01f * objDist,.08f * objDist };
	object.rotation = { M_PI / 2, M_PI/2 };
	dist = intersectCylinder(object, ray);
	if (dist > 0 && dist < depth) {
		axis = Axis::y;
		depth = dist;
	}
	object.position.y = position.y;

	object.position.z += 0.08 * objDist;
	object.scale = { .01f * objDist,.01f * objDist,.08f * objDist };
	object.rotation = { 0, 0 };
	dist = intersectCylinder(object, ray);
	if (dist > 0 && dist < depth) {
		axis = Axis::z;
		depth = dist;
	}
	object.position.z = position.z;

	return axis;
}

int findSelectedPlane(Scene& scene, Renderer& UI, Camera& camera) {
	Transform object{};
	float depth = 1000;
	int axis = Axis::none;
	///CHECK
	Ray ray = getRay(camera, UI);
	object.position = scene.objects[scene.selectedIndex].transform.position;
	Vec3 position = Vec3(object.position.x, object.position.y, object.position.z);
	float objDist = sqrt(dot(position - camera.position, position - camera.position));

	object.scale = { .12f * objDist,.12f * objDist,.12f * objDist };
	object.rotation = { 0, 0 };
	float dist = intersectCircle(object, ray);
	if (dist > 0 && dist < depth) {
		Vec3 inter = ray.origin + dist * ray.direction - position;
		if ((inter.x * inter.x + inter.y * inter.y) > .10 * .10 * objDist * objDist) {
			axis = Axis::z;
			depth = dist;
		}
	}

	object.scale = { .12f * objDist,.12f * objDist,.12f * objDist };
	object.rotation = { M_PI / 2, M_PI / 2 };
	dist = intersectCircle(object, ray);
	if (dist > 0 && dist < depth) {
		Vec3 inter = ray.origin + dist * ray.direction - position;
		if ((inter.x * inter.x + inter.z * inter.z) > .10 * .10 * objDist * objDist) {
			axis = Axis::y;
			depth = dist;
		}
	}

	return axis;
}

std::tuple< float, float> inversePoint(Vec3 point, Renderer& UI, Camera& camera) {
	Vec3 rayDir = point - camera.position;
	rayDir = rotateZ(rayDir, -camera.direction.z);
	rayDir = rotateY(rayDir, -camera.direction.y);
	rayDir /= rayDir.z;

	float scale = tan(camera.vFov * M_PI / 360);
	float screenPosX = -rayDir.y / scale * float(UI.height) / UI.width;
	float screenPosY = -rayDir.x / scale;

	float pixelX = .5 * (1 + screenPosX) * UI.width;
	float pixelY = .5 * (1 + screenPosY) * UI.height;

	return {pixelX,pixelY};
}

Ray findPoint(float pixelX, float pixelY, Renderer& UI, Camera& camera) {
	float screenPosX = pixelX / UI.width * 2.0 - 1.0;
	float screenPosY = pixelY / UI.height * 2.0 - 1.0;

	float scale = tan(camera.vFov * M_PI / 360);
	float x = -screenPosY * scale;
	float y = -screenPosX * scale * float(UI.width) / UI.height;

	Ray ray;
	ray.origin = camera.position;
	ray.direction = Vec3(x, y, 1.f);
	ray.direction.Normalize();
	ray.direction = rotateY(ray.direction, camera.direction.y);
	ray.direction = rotateZ(ray.direction, camera.direction.z);

	return ray;
}

Vec3 computeOffset(Vec3 origin, Renderer& UI, Camera& camera, int axis) {
	ImVec2 mousePos = UI.io->MousePos;
	mousePos.y = UI.height - mousePos.y;
	auto [p0x, p0y] = inversePoint(origin, UI, camera);
	Vec3 axisOffset{};
	switch (axis) {
	case(Axis::x):
		axisOffset = Vec3(1, 0, 0); break;
	case(Axis::y):
		axisOffset = Vec3(0, 1, 0); break;
	case(Axis::z):
		axisOffset = Vec3(0, 0, 1); break;
	}
	auto [p1x, p1y] = inversePoint(origin + axisOffset, UI, camera);

	float dx = p1x - p0x;
	float dy = p1y - p0y;

	float a = dy / dx;
	float b = p0y - p0x * dy / dx;

	float x = (mousePos.x + mousePos.y * a - a * b) / (1 + a * a);
	float y = a * x + b;

	Ray ray = findPoint(x, y, UI, camera);

	float lambda = axis == Axis::z ? (origin.x - ray.origin.x) / ray.direction.x : (origin.z - ray.origin.z) / ray.direction.z;
	return ray.origin + lambda * ray.direction - origin;
}



Vec3 projectAxis(Vec3 origin, Renderer& UI, Camera& camera, int axis) {
	ImVec2 mousePos = UI.io->MousePos;
	mousePos.y = UI.height - mousePos.y;
	auto  [p0x,p0y] = inversePoint(origin, UI, camera);
	Vec3 axisOffset{};
	switch (axis) {
	case(Axis::x):
		axisOffset = Vec3(1, 0, 0); break;
	case(Axis::y):
		axisOffset = Vec3(0, 1, 0); break;
	case(Axis::z):
		axisOffset = Vec3(0, 0, 1); break;
	}
	auto [p1x, p1y] = inversePoint(origin + axisOffset, UI, camera);

	float dx = p1x - p0x;
	float dy = p1y - p0y;

	float a = dy / dx;
	float b = p0y - p0x * dy / dx;

	float x = (mousePos.x + mousePos.y * a - a * b) / (1 + a * a);
	float y = a * x + b;

	Ray ray = findPoint(x, y, UI, camera);

	float lambda = axis == Axis::z ? (origin.x - ray.origin.x) / ray.direction.x : (origin.z - ray.origin.z) / ray.direction.z;
	return ray.origin + lambda * ray.direction;
}

float findAngle(Vec3 origin, Renderer& UI, Camera& camera, int axis) {
	Ray ray = getRay(camera, UI);
	float lambda = 0;
	switch (axis) {
	case(Axis::y):
		lambda = (origin.y - ray.origin.y) / ray.direction.y; break;
	case(Axis::z):
		lambda = (origin.z - ray.origin.z) / ray.direction.z; break;
	}

	Vec3 intersect =  ray.origin + lambda * ray.direction;

	float angle = 0;
	if (axis == Axis::y) {
		angle = M_PI / 2 - atan2(intersect.z, intersect.x);
	}
	else {
		angle = atan2(intersect.y, intersect.x);
	}
	return angle;
}