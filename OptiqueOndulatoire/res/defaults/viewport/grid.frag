#version 460 core 

out vec4 color;
layout(location = 0) in vec2 uv;

layout(binding = 0) uniform sampler2D colorIn;

struct Primitive {
	int type;
	vec4 color;
	vec3 position;
	vec3 scale;
	vec3 A;
	vec3 B;
};

float sdfBox(vec2 position, Primitive box) {
    vec2 d = abs(position - box.position.xy)-.5*box.scale.xy;
    return length(max(d,0.0)) + min(max(d.x,d.y),0.0);
}

float feathering = 1;

uniform float visibility = .5;
uniform float scale = 1.;
uniform float gridSize = 100.;
uniform vec2 origin = vec2(0.);
uniform float thickness = 2;
uniform float axThickFactor = 2;

//Thanks Inigo Quilez
float smoothMin( float a, float b, float k )
{
    float h = max( k-abs(a-b), 0.0 )/k;
    return min(a,b) - k*0.5*(1.0+h-sqrt(1.0-h*(h-2.0)));
}

float smoothMax( float a, float b, float k )
{
    float h = max( k-abs(b-a), 0.0 )/k;
    return max(a,b) + k*0.5*(1.0+h-sqrt(1.0-h*(h-2.0)));
}

float sdfGrid(vec2 position) {
	Primitive grid;
	grid.position = vec3(gridSize/2);
	grid.scale = vec3(gridSize);
	float distGrid = -sdfBox(fract(position/gridSize)*gridSize, grid)-thickness*.5;
	float distAxes = smoothMin(abs(position.x),abs(position.y),.4*thickness)-thickness*.5*axThickFactor;
	return scale*smoothMin(distGrid,distAxes,0.000001); 
}

float sdfCircle(vec2 position, Primitive cercle) {
	return distance(position,cercle.position.xy) - cercle.scale.x;
}

void main() {
	vec2 position = ((uv-.5) * textureSize(colorIn,0) - origin/scale);

	float v = smoothstep(feathering*scale,-feathering*scale,sdfGrid(position));
	color = vec4(v);
	float alpha = v;

	Primitive circle;
	circle.scale = vec3(7.);
	v = smoothstep(feathering,-feathering,sdfCircle(position,circle));
	color = mix(color,vec4(.5),v);
	alpha = max(alpha,v);

	circle.scale = vec3(5.);
	v = smoothstep(feathering,-feathering,sdfCircle(position,circle));
	color = mix(color,vec4(.9),v);
	alpha = max(alpha,v);

	color = mix(texture2D(colorIn,vec2(uv.x,1-uv.y)),color,visibility*alpha);
}