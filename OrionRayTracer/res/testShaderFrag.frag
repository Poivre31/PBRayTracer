#version 460 core 

out vec4 pixelColor;
layout(location = 1) in vec2 UVs;

uniform float t;

void main() {
	pixelColor = vec4(UVs,(1 + sin(t))/2,1);
}