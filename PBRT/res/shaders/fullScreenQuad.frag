#version 460 core 

out vec4 FragColor;
in vec2 UVs;

uniform sampler2D screenTexture;

vec3 acesToneMapping(vec3 color) {
	float a = 2.51;
	float b = 0.03;
	float c = 2.43;
	float d = 0.59;
	float e = 0.14;
	return (color * (a * color + b)) / (color * (c * color + d) + e);
}

vec3 HDR(vec3 color) {
	float lumInitial = .2126*color.x + .7152*color.y + .0722*color.z;
	float scaling = 1;
	float lum = scaling * lumInitial;
	lum = lum / (1 + lum);
	float saturation = 1.5;
	color = lum * pow((color / lumInitial), vec3(saturation));
	return color;
}

void main() {
	vec3 color = texture2D(screenTexture,UVs).xyz;
	color = HDR(color);
	color = pow(color, vec3(1./2.2));
	FragColor = vec4(color,1);
}