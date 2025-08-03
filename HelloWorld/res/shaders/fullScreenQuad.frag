#version 460 core 

out vec4 FragColor;
in vec2 UVs;

uniform sampler2D screenTexture;
const float startCompression=.6-0.04;
const float desaturation=.15;

// Thanks to https://modelviewer.dev/examples/tone-mapping
vec3 khronosToneMapping(vec3 color) {
    float x = min(color.r, min(color.g, color.b));
    float offset = x < 0.08 ? x - 6.25 * x * x : 0.04;
    color -= offset;

    float peak = max(color.r, max(color.g, color.b));
    if (peak < startCompression) return color;

    float d = 1. - startCompression;
    float newPeak = 1. - d * d / (peak + d - startCompression);
    color *= newPeak / peak;

    float g = 1. - 1. / (desaturation * (peak - newPeak) + 1.);
    return mix(color, newPeak * vec3(1, 1, 1), g);
}

vec3 acesToneMapping(vec3 color) {
	float a = 2.51;
	float b = 0.03;
	float c = 2.43;
	float d = 0.59;
	float e = 0.14;
	return (color * (a * color + b)) / (color * (c * color + d) + e);
}

vec3 ACESFitted(vec3 color)
{
	const mat3x3 ACESInputMat =
	{
		{0.59719, 0.35458, 0.04823},
		{0.07600, 0.90834, 0.01566},
		{0.02840, 0.13383, 0.83777}
	};
    color = color * ACESInputMat;

	vec3 a = color * (color + 0.0245786f) - 0.000090537f;
	vec3 b = color * (0.983729f * color + 0.4329510f) + 0.238081f;
	return a / b;

	const mat3x3 ACESOutputMat =
	{
		{ 1.60475, -0.53108, -0.07367},
		{-0.10208,  1.10813, -0.00605},
		{-0.00327, -0.07276,  1.07602}
	};

    color = color * ACESOutputMat;

    color = clamp(color, 0., 1.);

    return color;
}

vec3 SoftClip(vec3 x) // added, adapted from: https://www.shadertoy.com/view/wdtfRS
{
    return (1.0 + x - sqrt(1.0 - 1.99*x + x*x)) / (1.995);
}

// Based on http://www.oscars.org/science-technology/sci-tech-projects/aces
vec3 aces_tonemap(vec3 color){	
	mat3 m1 = mat3(
        0.59719, 0.07600, 0.02840,
        0.35458, 0.90834, 0.13383,
        0.04823, 0.01566, 0.83777
	);
	mat3 m2 = mat3(
        1.60475, -0.10208, -0.00327,
        -0.53108,  1.10813, -0.07276,
        -0.07367, -0.00605,  1.07602
	);
	vec3 v = m1 * color;    
	vec3 a = v * (v + 0.0245786) - 0.000090537;
	vec3 b = v * (0.983729 * v + 0.4329510) + 0.238081;
        
	return m2 * (a / b); // changed
}

vec3 HDR(vec3 color) {
	float lumInitial = .2126*color.x + .7152*color.y + .0722*color.z;
	float scaling = 1.4;
	float lum = scaling * lumInitial;
	lum = lum / (1 + lum);
	float saturation = .9;
	color = lum * pow((color / lumInitial), vec3(saturation));
	return color;
}

void main() {
	vec3 color = texture2D(screenTexture,UVs).xyz;
	//color = SoftClip(aces_tonemap(color));
//	color = HDR(color);
//	color = pow(color, vec3(1./2.2));
	FragColor = vec4(color,1);

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