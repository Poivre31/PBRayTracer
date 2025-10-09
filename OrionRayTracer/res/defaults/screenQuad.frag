#version 460 core 

out vec4 color;
layout(location = 0) in vec2 uv;
uniform sampler2D screenTexture;

void main() {
	vec3 tex = texture2D(screenTexture,uv).xyz;
	color = vec4(tex,1);
}