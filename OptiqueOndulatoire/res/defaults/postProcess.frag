#version 460 core 

out vec4 color;
layout(location = 0) in vec2 uv;

layout(binding = 0) uniform sampler2D colorIn;

void main() {
	color = texture2D(colorIn,uv);
	color = sin(cos(2*color)+color);
}