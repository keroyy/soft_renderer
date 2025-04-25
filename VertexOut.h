#pragma once
#include "Vec4.h"
#include "Vec2.h"
/***************************************************************
	  *  @brief     Vertex to Fragment
	 **************************************************************/
class VertexOut {
public:
	Vec4 worldPos;
	Vec4 projPos;
	Vec4 ndcPos;
	Vec4 screenPos;
	Vec2 texcoord;
	Vec3 normal;
	Vec4 color;
	double oneDivZ;// 深度测试指标 w分量的倒数，用于透视矫正
	VertexOut() :worldPos(), projPos(), texcoord(), normal(), color(), oneDivZ(1.0){}
	VertexOut(Vec4 wpos, Vec4 ppos, Vec2 tex, Vec3 nor, Vec4 col, double oZ) :
		worldPos(wpos), projPos(ppos), texcoord(tex), normal(nor), color(col), oneDivZ(oZ) {}
	VertexOut(const VertexOut& ver):
		worldPos(ver.worldPos),
		projPos(ver.projPos),
		ndcPos(ver.ndcPos),
		screenPos(ver.screenPos),
		texcoord(ver.texcoord),
		normal(ver.normal),
		color(ver.color),
		oneDivZ(ver.oneDivZ) {}
};