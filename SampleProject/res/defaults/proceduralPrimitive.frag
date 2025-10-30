#version 460 core

out vec4 color;
layout(location = 0) in vec2 uv;

float pi = 3.14159265358;
uniform int width;
uniform int height;
vec2 size = vec2(width,height);

uniform int selectedIndex;
uniform int nPrimitives;

struct Primitive {
	int type;
	vec3 color;
	vec3 position;
	vec3 scale;
	vec3 A;
	vec3 B;
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
	vec2 position = uv * size;
	float dist = 1000000000;
	for(int i = 0; i < nPrimitives; i++) {
		float d = 1000000000;
		Primitive p = _primitives[i];
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
		dist = min(dist,d);
		color = vec4(p.color,1);
	}

	color *= smoothstep(feathering/2,-feathering/2,dist);
}

