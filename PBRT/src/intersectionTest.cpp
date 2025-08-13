#include "intersectionTest.h"

static Vec3 sign(Vec3 v) {
	v.x = v.x >= 0;
	v.y = v.y >= 0;
	v.z = v.z >= 0;
	return v * 2 - 1;
}

static Vec3 rotateSphericalInv(Vec3 vec, float theta, float phi) {
	Vec3 u;
	u.x = cos(phi) * vec.x + sin(phi) * vec.y;
	u.y = -sin(phi) * vec.x + cos(phi) * vec.y;
	u.z = vec.z;

	vec.x = cos(theta) * u.x - sin(theta) * u.z;
	vec.y = u.y;
	vec.z = sin(theta) * u.x + cos(theta) * u.z;
	return vec;
}

static Ray transformRay(Ray& ray, Transform& transform) {
	Vec3 position = Vec3(transform.position.x, transform.position.y, transform.position.z);
	Vec3 scale = Vec3(transform.scale.x, transform.scale.y, transform.scale.z);
	ray.origin -= position;
	ray.origin = rotateSphericalInv(ray.origin, transform.rotation.x, transform.rotation.y);
	ray.direction = rotateSphericalInv(ray.direction, transform.rotation.x, transform.rotation.y);
	ray.direction /= scale;
	ray.origin /= scale;

	return ray;
}

float intersectSphere(Transform object, Ray ray) {
	ray = transformRay(ray, object);
	float a = dot(ray.direction, ray.direction);
	float b = dot(ray.origin, ray.direction);
	float c = dot(ray.origin, ray.origin) - 1.;

	float delta = b * b - a * c;
	return delta >= 0 ? (-b - sqrt(delta)) / a : -1;
}

float intersectCube(Transform object, Ray ray) {
	ray = transformRay(ray, object);
	Vec3 t2 = (sign(ray.direction) - ray.origin) / ray.direction;
	Vec3 t1 = -(sign(ray.direction) + ray.origin) / ray.direction;

	float tmin = max(t1.x, max(t1.y, t1.z));
	float tmax = min(t2.x, min(t2.y, t2.z));

	return tmin < tmax ? tmin : -1;
}

float intersectPlane(Transform object, Ray ray) {
	ray = transformRay(ray, object);
	float dist = -ray.origin.z / ray.direction.z;
	Vec3 intersect = ray.origin + dist * ray.direction;
	if (abs(intersect.x) < 1. && abs(intersect.y) < 1.) return dist;
	return -1;
}

float intersectCircle(Transform object, Ray ray) {
	ray = transformRay(ray, object);
	float dist = -ray.origin.z / ray.direction.z;
	Vec3 intersect = ray.origin + dist * ray.direction;
	intersect.z = 0;
	if (dot(intersect, intersect) < 1.) return dist;
	return -1;
}

float intersectCylinder(Transform object, Ray ray) {
	ray = transformRay(ray, object);
	float orZ = ray.origin.z;
	float dirZ = ray.direction.z;
	ray.origin.z = 0;
	ray.direction.z = 0;
	float a = dot(ray.direction, ray.direction);
	float b = dot(ray.origin, ray.direction);
	float c = dot(ray.origin, ray.origin) - 1.;

	float delta = b * b - a * c;
	if (delta < 0.) return -1.;
	float dist = (-b - sqrt(delta)) / a;
	float zIntersect = orZ + dist * dirZ;
	if (abs(zIntersect) < 1.) return dist;

	dist = -dist - 2. * b / a;
	zIntersect = orZ + dist * dirZ;
	if (abs(zIntersect) < 1.) return dist;

	return -1;
}

float intersectCone(Transform object, Ray ray) {
	ray = transformRay(ray, object);
	Vec3 fac = Vec3(4, 4, -1);
	float a = dot(fac * ray.direction, ray.direction);
	float b = dot(fac * ray.origin, ray.direction) + ray.direction.z;
	float c = dot(fac * ray.origin, ray.origin) - 1 + 2 * ray.origin.z;

	float delta = b * b - a * c;
	if (delta < 0) return -1;
	float dist = (-b - sqrt(delta)) / a;
	float intersectZ = ray.origin.z + dist * ray.direction.z;
	if (abs(intersectZ) <= 1.) return dist;

	dist = -dist - 2. * b / a;
	intersectZ = ray.origin.z + dist * ray.direction.z;
	if (abs(intersectZ) <= 1.) return dist;

	return -1;
}

float intersectPyramid(Transform object, Ray ray) {
	ray = transformRay(ray, object);

	// ### MAX DEPTH ###
	float dist = 1000;
	Vec3 intersect;
	float t1 = (1 - ray.origin.z - 2 * ray.origin.x) / (ray.direction.z + 2 * ray.direction.x);
	float t2 = (ray.origin.z - 1 - 2 * ray.origin.x) / (-ray.direction.z + 2 * ray.direction.x);
	intersect = ray.origin + t1 * ray.direction;
	if (abs(intersect.z) <= 1 && abs(intersect.y) <= abs(intersect.x)) dist = min(dist, t1);
	intersect = ray.origin + t2 * ray.direction;
	if (abs(intersect.z) <= 1 && abs(intersect.y) <= abs(intersect.x)) dist = min(dist, t2);

	t1 = (1 - ray.origin.z - 2 * ray.origin.y) / (ray.direction.z + 2 * ray.direction.y);
	t2 = (ray.origin.z - 1 - 2 * ray.origin.y) / (-ray.direction.z + 2 * ray.direction.y);
	intersect = ray.origin + t1 * ray.direction;
	if (abs(intersect.z) <= 1 && abs(intersect.x) <= abs(intersect.y)) dist = min(dist, t1);
	intersect = ray.origin + t2 * ray.direction;
	if (abs(intersect.z) <= 1 && abs(intersect.x) <= abs(intersect.y)) dist = min(dist, t2);

	if (dist > 999) dist = -1;
	return dist;
}
