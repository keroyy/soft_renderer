#pragma once
#include "Shader.h"
#include "Matrix.h"
#include "Vec3.h"
#include "Texture.h"

class BasicShader :public Shader {
private:
	Matrix worldMatrix;
	Matrix viewMatrix;
	Matrix projectMatrix;
	Textures* texture;
public:
	BasicShader();
	~BasicShader(){}
	virtual void setCamera(Vec3 pos, Vec3 target, Vec3 up, float fov, float asp, float near, float far);
	virtual VertexOut vertexShader(const Vertex in)override;
	virtual Vec4 fragmentShader(const VertexOut in)override;
};