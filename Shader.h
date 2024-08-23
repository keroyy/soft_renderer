#pragma once
#include "Vertex.h"
#include "VertexOut.h"
class Shader {
public:
	Shader() {}
	virtual ~Shader() {}
	virtual void setCamera(Vec3 pos, Vec3 target, Vec3 up, float fov, float asp, float near, float far) = 0;
	virtual VertexOut vertexShader(const Vertex in) = 0;
	virtual Vec4 fragmentShader(const VertexOut in) = 0;
};