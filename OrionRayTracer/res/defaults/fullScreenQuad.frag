#version 460 core 

out vec4 color;
in vec2 uv;

uniform sampler2D screenTexture;

void main() {
	vec3 color = texture2D(screenTexture,uv).xyz;
	color = vec4(sqrt(color),1);
}