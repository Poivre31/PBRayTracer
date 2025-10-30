#version 460 core

out vec4 color;
layout(location = 0) in vec2 uv;

float pi = 3.14159265358;
uniform ivec2 size;
uniform int height;

uniform float wavelength;
uniform float intensity;
uniform float gamma;

uniform int selectedIndex;
uniform int nPrimitives;
uniform int nSources;
uniform int nPlanes;

uniform vec2 origin = vec2(0);
uniform float scale;
uniform int displayType;

struct Primitive {
	int type;
	vec4 color;
	vec3 position;
	vec3 scale;
	vec3 A;
	vec3 B;
};

struct Source {
	vec3 position;
	vec4 color;
	float phi0;
	int type;
};

layout(std430, binding = 0) readonly restrict buffer SourcesBuffer
{
	Source _sources[];
};

layout(std430, binding = 1) readonly restrict buffer PlanesBuffer
{
	Source _planes[];
};

layout(std430, binding = 7) buffer PrimitivesBuffer
{
	Primitive _primitives[]; // Buffer sent from the cpu to the gpu. Here vec3 and vec4 are equivalent
};

float feathering = 2.;
// 0 = Cercle
// 1 = ligne
// 2 = box
// 3 = donut
// 4 = arrow

mat2x2 rotationMatrix(float theta) {
	return mat2x2(cos(theta),-sin(theta),sin(theta),cos(theta));
}

float sdfCircle(vec2 position, Primitive cercle) {
	return distance(position,cercle.position.xy) - cercle.scale.x;
}

float sdfLine(vec2 position, Primitive line) {
    vec2 pa = position-line.A.xy, ba = (line.B-line.A).xy;
    float h = clamp( dot(pa,ba)/dot(ba,ba), 0.0, 1.0 );
    return length( pa - ba*h ) - line.scale.x/2;
}

float sdfBox(vec2 position, Primitive box) {
    vec2 d = abs(position - box.position.xy)-.5*box.scale.xy;
    return length(max(d,0.0)) + min(max(d.x,d.y),0.0);
}

float sdfDonut(vec2 position, Primitive donut) {
	float r1 = max(donut.scale.x,donut.scale.y);
	float r2 = min(donut.scale.x,donut.scale.y);
	float d1 = distance(position,donut.position.xy) - r1;
	float d2 = -(distance(position,donut.position.xy) - r2);
	if(d2>d1) return d2;
	else return d1;
}

float sdfArrow(vec2 position, Primitive arrow) {
    vec2 pa = position-arrow.A.xy, ba = (arrow.B-arrow.A).xy;
    float h = clamp( dot(pa,ba)/dot(ba,ba), 0.0, 1.0 );
	float dist = length( pa - ba*h ) - arrow.scale.x/2;

	vec2 C = normalize(rotationMatrix(pi/5) * (arrow.A-arrow.B).xy)*arrow.scale.x*4 + arrow.B.xy;
	pa = position-C, ba = (arrow.B.xy-C);
    h = clamp( dot(pa,ba)/dot(ba,ba), 0.0, 1.0 );
	dist = min(dist, length( pa - ba*h ) - arrow.scale.x/2);

	C = normalize(rotationMatrix(-pi/5) * (arrow.A-arrow.B).xy)*arrow.scale.x*4 + arrow.B.xy;
	pa = position-C, ba = (arrow.B.xy-C);
    h = clamp( dot(pa,ba)/dot(ba,ba), 0.0, 1.0 );
	dist = min(dist, length( pa - ba*h ) - arrow.scale.x/2);
    return dist;
}


void main() {
	vec2 position = ((uv-.5) * size * scale + origin);

	color = vec4(0);
	vec3 phi_r = vec3(0);
	vec3 phi_i = vec3(0);
	float k = 2 * pi / wavelength;
	for(int i = 0; i < nSources; i++) {
		Source p = _sources[i];

		float d = distance(_sources[i].position.xy, position.xy) + 0.000001;
		vec3 c = _sources[i].color.xyz;
		vec3 p_r = c / d * cos(k * d);
		vec3 p_i = c / d * sin(k * d);

		phi_r += p_r;
		phi_i += p_i;
	}

	for(int i = 0; i < nPlanes; i++) {
		Source p = _planes[i];

		vec3 c = _planes[i].color.xyz;
		vec3 p_r = c * cos(dot(k * _planes[i].position.xy,position) + _planes[i].phi0)*.01;
		vec3 p_i = c * sin(dot(k * _planes[i].position.xy,position) + _planes[i].phi0)*.01;


		phi_r += p_r;
		phi_i += p_i;
	}

	vec3 I;
	if(displayType == 0)
		I = (phi_r * phi_r + phi_i * phi_i)*100;
	if(displayType == 1)
		I = max(vec3(0),phi_r * 10);
	if(displayType == 2)
		I =max(vec3(0),phi_i * 10);

	I *= intensity;
	I = I / (1+I);
	//I = sqrt(I);
	I = pow(I, vec3(1./gamma));
	color = vec4(I,1);

	float dist = 1000000000;
	vec4 savedColor = vec4(0);
	position = ((uv-.5) * size * scale + origin);
	for(int i = 0; i < nPrimitives; i++) {
		float d = 1000000000;
		Primitive p = _primitives[i];
		p.scale *= scale;
		switch(p.type){
		case(0):
			d = sdfCircle(position,p);
			break;
		case(1):
			d = sdfLine(position,p);
			break;
		case(2):
			d = sdfBox(position,p);
			break;
		case(3):
			d = sdfDonut(position,p);
			break;
		case(4):
			d = sdfArrow(position,p);
			break;
		}
		if(d<dist) {
			dist = d;
			savedColor = p.color;
		}
	}
	Primitive grid;
	grid.position = vec3(50);
	grid.scale = vec3(100);
	float d = -sdfBox(fract(position/100)*100, grid)/2;
	if(d<dist) {
		dist = d;
		savedColor = vec4(.5f);
	}
	float v = smoothstep(feathering/2*scale,-feathering/2*scale,dist);
	color = mix(color, savedColor, v * savedColor.w);
}

