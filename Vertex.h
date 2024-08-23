#pragma once
#include "Vec4.h"
#include "Vec2.h"

class Vertex {
public:
	Vec4 position;
	Vec4 color;
	Vec2 texcoord;
	Vec3 normal;
	//unsigned char textureName;
	Vertex() {}
	~Vertex() {}
	Vertex(Vec4 pos, Vec4 col, Vec2 tex, Vec3 nor) :
		position(pos), color(col), texcoord(tex), normal(nor){}
	Vertex(const Vertex& ver):
		position(ver.position),
		color(ver.color),
		texcoord(ver.texcoord),
		normal(ver.normal){}
};