#version 460 core

out vec4 color;
layout(location = 0) in vec2 uv;

struct Lamp {
	vec3 position;
	vec3 velocity;
};

layout(std430, binding = 0) readonly restrict buffer LampBuffer
{
	Lamp _Lamps[]; // Buffer sent from the cpu to the gpu. Here vec3 and vec4 are equivalent
};

uniform int nLamps; // Variable set by the cpu
uniform float wavelength;
uniform int renderMode;

uniform float intensity;
uniform float gamma;
uniform float saturation;

float pi = 3.1459;

void main() {
	vec2 xy = uv;
	vec3 xyz = vec3(xy,.5);
	float k = 2 * pi / wavelength;

	vec3 phi_r = vec3(0);
	vec3 phi_i = vec3(0);
	for(int i = 0; i < nLamps; i++) {
		float dist = length(_Lamps[i].position.xy - xy)  + 0.000001;
		vec3 color;
		if(renderMode == 0)
			color = intensity * _Lamps[i].position;
		else if(renderMode == 1)
			color = intensity * (cross(_Lamps[i].position,abs(_Lamps[i].velocity)/length(_Lamps[i].velocity)));
		vec3 p_r = color / dist * cos(k * dist);
		vec3 p_i = color / dist * sin(k * dist);

		phi_r += p_r;
		phi_i += p_i;
	}
	phi_r /= 2*nLamps;
	phi_i /= 2*nLamps;

	vec3 I = phi_r * phi_r + phi_i * phi_i;

	I = I/(1+I);
	color = pow(vec4(I,1), vec4(1/gamma));
}