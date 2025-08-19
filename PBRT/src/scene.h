#pragma once
#include "floats.h"
#include "mathHelper.h"
#include <vector>
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "computeShader.h"
#include "vec3.h"
#include "camera.h"

namespace ObjectType {
	enum {
		sphere = 0,
		cube = 1,
		plane = 2,
		circle = 3,
		cylinder = 4,
		cone = 5,
		pyramid = 6
	};
}

namespace EditMode {
	enum {
		translation = 0,
		scaling = 1,
		rotation = 2,
	};
}

struct ObjectCount {
	int total;
	int sphere;
	int cube;
	int plane;
	int circle;
	int cylinder;
	int cone;
	int pyramid;
};

struct Transform {
	float4 position;
	float4 scale;
	float4 rotation;
};

struct Material {
	float4 color;
};

struct Object {
	Transform transform;
	Material material;
	int type;

	Object() {
		transform = {};
		transform.scale = { 1,1,1,0 };
		material = {};
		material.color = { 1,1,1,0 };
		type = 0;
	}
};

class Scene {
public:
	std::vector<Object> objects;
	Transform transforms[4096]{};
	float4 colors[4096]{};
	int counts[7];
	int totalCount;
	int selectedIndex = -1;
	int selectedType = -1;
	int editMode = 0;
	int editAxis = -1;
	Vec3 startOffset{};
	Vec3 startPos{};
	Vec3 startScale{};
	Vec3 startRot{};
	float startAngle = 0;
	int GIsamples = 0;
	float lightDir[3]{0,0,-1};
	float lightColor[3]{120,120,120};
	float lightRadius{.05};
	Camera* mainCamera = nullptr;
	float GIthreshold = 0;
	bool accumulate = false;
	int nAccumulated = 0;
	float thresh = 0;

	Scene() {};
	Scene(ComputeShader& mainShader);

	void ConnectGPU();

	void RandomScene(int nObjects);
	void AddObject(Object object);
	void RemoveObject(int index);
	void Clear();

	void ParseObjects();

	void SetEditMode(int mode);

	void SaveScene(Renderer& UI);
	
private:
	unsigned int transformsSSBO = 0;
	unsigned int colorsSSBO = 0;
	ComputeShader* rtShader = nullptr;
};