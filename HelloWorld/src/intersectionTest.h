#pragma once
#include "scene.h"
#include "vec3.h"

struct Ray{
	Vec3 origin;
	Vec3 direction;
};

float intersectSphere(Transform object, Ray ray);
float intersectCube(Transform object, Ray ray);
float intersectPlane(Transform object, Ray ray);
float intersectCircle(Transform object, Ray ray);
float intersectCylinder(Transform object, Ray ray);
float intersectCone(Transform object, Ray ray);
float intersectPyramid(Transform object, Ray ray);