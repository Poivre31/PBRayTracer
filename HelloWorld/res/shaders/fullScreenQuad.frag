#version 460 core 

out vec4 FragColor;
in vec2 UVs;

uniform sampler2D screenTexture;
//uniform int kernelRadius;
//uniform bool useLerp;
//uniform bool downsample;

void main() {
	FragColor = texture2D(screenTexture,UVs);

//	int kernelSize = 2 * kernelRadius +1;
//	vec2 dxdy = 1.f/textureSize(screenTexture,0);
//
//	vec3 color = vec3(0,0,0);
//
//
//
//	float sum = 0;
//	if(useLerp) {
//		for(int i = 0; i <= kernelRadius;i+=2) {
//			for(int j =0; j <= kernelRadius;j+=2) {
//				color+=mix(texture2D(screenTexture,UVs+ivec2(i,j)*dxdy).xyz,texture2D(screenTexture,UVs+ivec2(i+1,j+1)*dxdy).xyz,.5);
//				color+=mix(texture2D(screenTexture,UVs-ivec2(i,j)*dxdy).xyz,texture2D(screenTexture,UVs-ivec2(i+1,j+1)*dxdy).xyz,.5);
//				color+=mix(texture2D(screenTexture,UVs+ivec2(-i,j)*dxdy).xyz,texture2D(screenTexture,UVs+ivec2(-i-1,j+1)*dxdy).xyz,.5);
//				color+=mix(texture2D(screenTexture,UVs-ivec2(-i,j)*dxdy).xyz,texture2D(screenTexture,UVs-ivec2(-i-1,j+1)*dxdy).xyz,.5);
//				sum+=4;
//			}
//		}
//	}
//
//	else {
//		for(int i = 0; i <= kernelRadius;i++) {
//			for(int j =0; j <= kernelRadius;j++) {
//				color+=texture2D(screenTexture,UVs+ivec2(i,j)*dxdy).xyz;
//				color+=texture2D(screenTexture,UVs-ivec2(i,j)*dxdy).xyz;
//				color+=texture2D(screenTexture,UVs+ivec2(-i,j)*dxdy).xyz;
//				color+=texture2D(screenTexture,UVs-ivec2(-i,j)*dxdy).xyz;
//				sum+=4;
//			}
//		}
//	}
//
//	color/=sum;
//
//	FragColor = vec4(color,1);
}