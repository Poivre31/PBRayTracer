#version 460 core 

out vec4 FragColor;
in vec2 UVs;

uniform sampler2D screenTexture;

void main() {
	vec3 color = texture2D(screenTexture,UVs).xyz;
	FragColor = vec4(color,1);
}