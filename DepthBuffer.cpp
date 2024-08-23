#include "DepthBuffer.h"

void DepthBuffer::setDepth(float z) {
	depth = z;
}

float DepthBuffer::getDepth() {
	return depth;
}

void DepthBuffer::setBuffer(VertexOut zBuffer) {
	buffer = &zBuffer;
}

VertexOut DepthBuffer::getBuffer() {
	return *buffer;
}