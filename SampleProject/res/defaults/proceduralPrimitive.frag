#version 460 core

out vec4 color;
layout(location = 0) in vec2 uv;

struct Primitive {
	int type;
	vec3 position;
	vec3 scale;
};

layout(std430, binding = 0) buffer PrimitivesBuffer
{
	Primitive _primitives[]; // Buffer sent from the cpu to the gpu. Here vec3 and vec4 are equivalent
};

// 0 = Cercle
// 1 = ligne
// 2 = box

void main() {
	Primitive cercle;
	cercle.type = 0;
	cercle.position = vec3(.5,.5,0);
	cercle.scale = vec3(.1);

	float dist = distance(uv, cercle.position.xy);
	if(dist < cercle.scale.x)
		color = vec4(1);
	else 
		color = vec4(0);
}
