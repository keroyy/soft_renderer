#pragma once
#include "Shader.h"
class DepthBuffer {
private:
	float depth; // 深度值
	VertexOut* buffer; // 颜色缓冲
public:
	DepthBuffer() :depth(1.0f), buffer(nullptr) {};
	~DepthBuffer() {
		buffer = nullptr;
	}
	void setDepth(float z);
	float getDepth();
	void setBuffer(VertexOut zBuffer);
	VertexOut getBuffer();
};