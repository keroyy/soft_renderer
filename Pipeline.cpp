#include "Pipeline.h"
#include "BasicShader.h"
#include "algorithm"
#include "MainCamera.h"

Pipeline::~Pipeline() {
	if (m_shader)delete m_shader;
	if (m_frontBuffer)delete m_frontBuffer;
	if (m_backBuffer)delete m_backBuffer;
	m_shader = nullptr;
	m_frontBuffer = nullptr;
	m_backBuffer = nullptr;
}

void Pipeline::initialize() {
	if (m_frontBuffer != nullptr)delete m_frontBuffer;
	if (m_backBuffer)delete m_backBuffer;
	if (m_shader)delete m_shader;
	m_frontBuffer = new FrameBuffer(width, height);
	m_backBuffer = new FrameBuffer(width, height);
	m_shader = new BasicShader();
}

void Pipeline::drawIndex(RenderMode mode, MainCamera *camera) {
	if (m_indices.empty())return;
	m_shader->setCamera(camera->pos, camera->target, camera->up, camera->fov, camera->asp, camera->near, camera->far);
	for (unsigned int i = 0; i < m_indices.size(); i += 3) {
		/*VertexOut v1 = m_vertices[m_indices[i]];
		VertexOut v2 = m_vertices[m_indices[i+1]];
		VertexOut v3 = m_vertices[m_indices[i+2]];
		m_backBuffer->Cover(static_cast<int>(v1.projPos.x), static_cast<int>(v1.projPos.y), v1.color);
		m_backBuffer->Cover(static_cast<int>(v2.projPos.x), static_cast<int>(v2.projPos.y), v2.color);
		m_backBuffer->Cover(static_cast<int>(v3.projPos.x), static_cast<int>(v3.projPos.y), v3.color);*/
		//! vertices assembly to triangle primitive
		Vertex p1, p2, p3;
		{
			/*p1 = m_vertices[3 * i + 0];
			p2 = m_vertices[3 * i + 1];
			p3 = m_vertices[3 * i + 2];*/
			p1 = m_vertices[m_indices[i + 0]];
			p2 = m_vertices[m_indices[i + 1]];
			p3 = m_vertices[m_indices[i + 2]];
		}

		//! vertex shader stage.
		VertexOut v1, v2, v3;
		{
			v1 = m_shader->vertexShader(p1);
			v2 = m_shader->vertexShader(p2);
			v3 = m_shader->vertexShader(p3);
		}

		//! rasterization and fragment shader stage.
		{
			// clip -> ndc
			v1.ndcPos = v1.projPos / v1.projPos.w;
			v2.ndcPos = v2.projPos / v2.projPos.w;
			v3.ndcPos = v3.projPos / v3.projPos.w;

			// 因为深度值很大一部分是由很小的z值所决定的，这给了近处的物体很大的深度精度。z的取值为[-1, 1]，我们将z的取值简单映射到[0, 1]
			/*v1.ndcPos.z = (v1.ndcPos.z + 1.0f) * 0.5f;
			v2.ndcPos.z = (v2.ndcPos.z + 1.0f) * 0.5f;
			v3.ndcPos.z = (v3.ndcPos.z + 1.0f) * 0.5f;*/

			// ndc -> screen
			Matrix viewPortMatrix;
			//viewPortMatrix.viewport(0, 0, width, height);
			viewPortMatrix.viewport(width, height);
			v1.screenPos = viewPortMatrix * v1.ndcPos;
			v2.screenPos = viewPortMatrix * v2.ndcPos;
			v3.screenPos = viewPortMatrix * v3.ndcPos;

			/*光栅化*/
			if (mode == RenderMode::wire)
			{
				// bresenham rasterization
				bresenham(v1, v2);
				bresenham(v1, v3);
				bresenham(v2, v3);
			}
			else if (mode == RenderMode::fill)
			{
				// edge walking rasterization
				edgeWalkingFillRasterization(v1, v2, v3);
			}
		}
	}
}

void Pipeline::clearBuffer(const Vec4 color, bool depth) {
	(void)depth;
	m_backBuffer->Fill(color);
	m_backBuffer->clearDepthBuffer();
}

void Pipeline::setShaderMode(ShadingMode mode) {
	if (m_shader)delete m_shader;
	if (mode == Simple)
		m_shader = new BasicShader();
	/*else if(mode == Phong)*/

}

void Pipeline::swapBuffer() {
	FrameBuffer* tmp = m_frontBuffer;
	m_frontBuffer = m_backBuffer;
	m_backBuffer = tmp;
}

VertexOut Pipeline::lerp(const VertexOut n1, const VertexOut n2, float weight) {
	VertexOut result;
	result.worldPos = n1.worldPos.lerp(n2.worldPos, weight);
	result.projPos = n1.projPos.lerp(n2.projPos, weight);
	result.ndcPos = n1.ndcPos.lerp(n2.ndcPos, weight);
	result.screenPos = n1.screenPos.lerp(n2.screenPos, weight);
	result.color= n1.color.lerp(n2.color, weight);
	result.normal= n1.normal.lerp(n2.normal, weight);
	result.texcoord = n1.texcoord.lerp(n2.texcoord, weight);
	//result.oneDivZ = (1.0 - weight) * n1.oneDivZ + weight * n2.oneDivZ;
	return result;
}

void Pipeline::bresenham(const VertexOut from, const VertexOut to) {
	int dx = to.screenPos.x - from.screenPos.x;
	int dy = to.screenPos.y - from.screenPos.y;
	int stepX = 1, stepY = 1;

	// judge the sign
	if (dx < 0) {
		stepX = -1;
		dx = -dx;
	}
	if (dy < 0) {
		stepY = -1;
		dy = -dy;
	}

	int d2x = 2 * dx, d2y = 2 * dy;
	int d2y_minus_d2x = d2y - d2x;
	int sx = from.screenPos.x;
	int sy = from.screenPos.y;

	VertexOut tmp;
	// slope < 1.
	if (dy <= dx) {
		int flag = d2y - dx;
		for (int i = 0; i <= dx; i++) {
			//linear interpolation
			tmp = lerp(from, to, static_cast<float>(i) / dx);
			// fragment shader
			m_backBuffer->Cover(sx, sy, m_shader->fragmentShader(tmp));
			sx += stepX;
			if (flag <= 0) {
				flag += d2y;
			}
			else {
				sy += stepY;
				flag += d2y_minus_d2x;
			}
		}
	}
	// slope > 1
	else {
		int flag = d2x - dy;
		for (int i = 0; i <= dy; ++i)
		{
			// linear interpolation
			tmp = lerp(from, to, static_cast<double>(i) / dy);
			// fragment shader
			m_backBuffer->Cover(sx, sy, m_shader->fragmentShader(tmp));
			sy += stepY;
			if (flag <= 0)
				flag += d2x;
			else
			{
				sx += stepX;
				flag -= d2y_minus_d2x;
			}
		}
	}
}

void Pipeline::scanLinePerRow(const VertexOut left, const VertexOut right) {
	VertexOut current;
	int length = right.screenPos.x - left.screenPos.x + 1;
	for (int i = 0; i <= length; i++) {
		// linear interpolation
		double weight = static_cast<double>(i) / length;
		current = lerp(left, right, weight);
		current.screenPos.x = left.screenPos.x + i;
		current.screenPos.y = left.screenPos.y;
		//// depth test oled
		//DepthBuffer zBuffer = m_frontBuffer->getDepthBuffer(current.screenPos.x, current.screenPos.y);
		//if (current.screenPos.z < zBuffer.getDepth()) {
		//	// fragment shader
		//	m_backBuffer->Cover(current.screenPos.x, current.screenPos.y, m_shader->fragmentShader(current));
		//	m_backBuffer->setDepthBuffer(current);
		//}
		/*
		else {
			m_backBuffer->Cover(current.screenPos.x, current.screenPos.y, m_shader->fragmentShader(zBuffer.getBuffer()));
		}*/

		// depth testing
		double depth = m_backBuffer->getDepth(current.screenPos.x, current.screenPos.y);
		if (current.screenPos.z > depth) {
			continue; // fail to pass the depth testing.
		}
		m_backBuffer->drawDepth(current.screenPos.x, current.screenPos.y, current.screenPos.z);

		// fragment shader
		m_backBuffer->Cover(current.screenPos.x, current.screenPos.y, m_shader->fragmentShader(current));

	}
}

void Pipeline::rasterTopTriangle(VertexOut v1, VertexOut v2, VertexOut v3) {
	VertexOut left = v2;
	VertexOut right = v3;
	VertexOut dest = v1;
	VertexOut tmp, newleft, newright;
	if (left.screenPos.x > right.screenPos.x)
	{
		tmp = left;
		left = right;
		right = tmp;
	}
	int dy = left.screenPos.y - dest.screenPos.y + 1;

	for (int i = 0; i < dy; ++i)
	{
		double weight = 0;
		if (dy != 0)
			weight = static_cast<double>(i) / dy;
		newleft = lerp(left, dest, weight);
		newright = lerp(right, dest, weight);
		newleft.screenPos.y = newright.screenPos.y = left.screenPos.y - i;
		scanLinePerRow(newleft, newright);
	}
}

void Pipeline::rasterBottomTriangle(VertexOut v1, VertexOut v2, VertexOut v3) {
	VertexOut left = v1;
	VertexOut right = v2;
	VertexOut dest = v3;
	VertexOut tmp, newleft, newright;
	if (left.screenPos.x > right.screenPos.x)
	{
		tmp = left;
		left = right;
		right = tmp;
	}
	int dy = dest.screenPos.y - left.screenPos.y + 1;


	for (int i = 0; i < dy; ++i)
	{
		double weight = 0;
		if (dy != 0)
			weight = static_cast<double>(i) / dy;
		newleft = lerp(left, dest, weight);
		newright = lerp(right, dest, weight);
		newleft.screenPos.y = newright.screenPos.y = left.screenPos.y + i;
		scanLinePerRow(newleft, newright);
	}
}

void Pipeline::edgeWalkingFillRasterization(VertexOut v1, VertexOut v2, VertexOut v3) {
	// split the triangle into two part
	VertexOut tmp;
	VertexOut target[3] = { v1, v2, v3 };
	if (target[0].screenPos.y > target[1].screenPos.y)
	{
		tmp = target[0];
		target[0] = target[1];
		target[1] = tmp;
	}
	if (target[0].screenPos.y > target[2].screenPos.y)
	{
		tmp = target[0];
		target[0] = target[2];
		target[2] = tmp;
	}
	if (target[1].screenPos.y > target[2].screenPos.y)
	{
		tmp = target[1];
		target[1] = target[2];
		target[2] = tmp;
	}

	// bottom triangle
	if (target[0].screenPos.y == target[1].screenPos.y)
	{
		rasterBottomTriangle(target[0], target[1], target[2]);
	}
	// top triangle
	else if (target[1].screenPos.y == target[2].screenPos.y)
	{
		rasterTopTriangle(target[0], target[1], target[2]);
	}
	// split it.
	else
	{
		double weight = static_cast<double>(target[1].screenPos.y - target[0].screenPos.y) / (target[2].screenPos.y - target[0].screenPos.y);
		VertexOut newPoint = lerp(target[0], target[2], weight);
		newPoint.screenPos.y = target[1].screenPos.y;
		rasterTopTriangle(target[0], newPoint, target[1]);
		rasterBottomTriangle(newPoint, target[1], target[2]);
	}
}