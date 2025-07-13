#version 330 core 
out vec4 FragColor;
in vec2 UVs;

void main() { 
	FragColor = vec4(UVs,1,1);
}