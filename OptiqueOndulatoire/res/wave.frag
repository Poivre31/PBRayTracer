#version 460 core

out vec4 color;
layout(location = 0) in vec2 uv;
layout(binding = 0) uniform sampler2D colorIn;

float pi = 3.14159265358;

uniform float wavelength = 1.;
uniform float intensity = 1.;
uniform float gamma = 1.;

uniform int nSources;

uniform vec2 origin = vec2(0);
uniform float scale;
uniform int displayType;

struct Source {
	vec3 position;
	vec4 color;
	float phi0;
	int type;
};

layout(std430, binding = 0) readonly restrict buffer SourcesBuffer
{
	Source _sources[];
};

void main() {
	vec2 position = ((uv-.5) * textureSize(colorIn,0) * scale - origin);

	color = vec4(0);
	vec3 phi_r = vec3(0);
	vec3 phi_i = vec3(0);
	float k = 2 * pi / wavelength;
	for(int i = 0; i < nSources; i++) {
		float d = distance(_sources[i].position.xy, position.xy) + 0.000001;
		vec3 c = _sources[i].color.xyz;
		vec3 p_r = c / d * cos(k * d);
		vec3 p_i = c / d * sin(k * d);

		phi_r += p_r;
		phi_i += p_i;
	}

//	for(int i = 0; i < nPlanes; i++) {
//		Source p = _planes[i];
//
//		vec3 c = _planes[i].color.xyz;
//		vec3 p_r = c * cos(dot(k * _planes[i].position.xy,position) + _planes[i].phi0)*.01;
//		vec3 p_i = c * sin(dot(k * _planes[i].position.xy,position) + _planes[i].phi0)*.01;
//
//
//		phi_r += p_r;
//		phi_i += p_i;
//	}

	vec3 I;
	if(displayType == 0)
		I = (phi_r * phi_r + phi_i * phi_i)*100;
	if(displayType == 1)
		I = max(vec3(0),phi_r * 10);
	if(displayType == 2)
		I =max(vec3(0),phi_i * 10);

	I *= intensity;
	I = I / (1+I);
	I = pow(I, vec3(1./gamma));
	color = vec4(I,1);
}

