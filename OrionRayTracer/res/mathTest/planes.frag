#version 460 core 

out vec4 color;
in vec2 uv;

uniform vec2 range;
uniform float a;
uniform float time;
uniform float wavelength;
uniform float L;
uniform float intensity;
uniform float gamma;
uniform int n;


float v = .2;
float pi = 3.1415929;

vec2 psi_r(vec3 r, vec3 n, float phi0) {
	float phase = dot(r,n) * 2 * pi / wavelength - time * 2 * pi * v / wavelength;
	return intensity * vec2(cos(phase + phi0),sin(phase + phi0));
}


float randFloat(uint seed, float a, float b) {
	uint state = seed*747796405u + 2891336453u;
	uint word = ((state >> ((state>>28u)+4u))^state)*277803737;
	word = (word>>22u)^word;
	return a+(b-a)*float(word)/(-1u);
}

void main() {
	vec2 map = (2 * uv - 1) * range * 10;
	vec3 xyz = vec3(map.x, map.y, L);

	vec2 psi = vec2(0);
	psi += psi_r(xyz, normalize(vec3(1,.5,0)) , randFloat(0, 0, 2*pi)*0);
	psi += psi_r(xyz, normalize(vec3(1,-.5,0)) , randFloat(0, 0, 2*pi)*0);

	float I = dot(psi,psi);

	I = I/(1 + I);
	I = pow(I,1./gamma);
	color = vec4(I);
}