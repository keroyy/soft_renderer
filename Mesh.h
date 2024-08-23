#pragma once
#include <vector>
#include "Vertex.h"
class Mesh
{
public:
	std::vector<Vertex> vertices; // 模型的顶点动态数组，下标为对应顶点的编号
	std::vector<unsigned int> index; // 索引顺序
	Mesh() {};
	~Mesh() {};

	Mesh(const Mesh& msh):vertices(msh.vertices),index(msh.index){}
	Mesh operator=(const Mesh& msh);
	void setVertices(Vertex* v, int count);
	void setIndex(int* i, int count);

	void triangle(Vec3 v1, Vec3 v2, Vec3 v3);
	void cube(double width, double height, double depth, int id, Vec4 pos);
	void plane(double width, double height, int id, Vec4 pos);
};