#version 460 core 

out vec4 color;
layout(location = 0) in vec2 uv;

void main() {
	color = vec4(uv,1,1);
}