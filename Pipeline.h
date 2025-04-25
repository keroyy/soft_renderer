#pragma once
#include "Shader.h"
#include "FrameBuffer.h"
#include "Matrix.h"
#include <vector>
#include "MainCamera.h"

/***************************************************************
	  首先，作为掌控全局的管线，必定承担起分析、计算、产生颜色，并将颜色送向帧缓冲的责任，那么它必须拥有一个缓冲区的指针，且必须知道当前画布的长与宽；
	  此外，渲染管线需要拿到所有的模型数据以及三角形顶点索引，才能进行整体分析；最后渲染管线必须知道自己使用的是哪一套着色器。
　　	  除此之外，我们还有一些设置可以进行选择，例如光照模式ShadingMode、光栅化模式RenderMode（对三角形进行描线还是填充）。
	 **************************************************************/
class Pipeline {
private:
	int width, height;
	Shader* m_shader;
	FrameBuffer* m_frontBuffer; // 暂存、传输
	FrameBuffer* m_backBuffer; // 动态写入
	std::vector<Vertex>m_vertices;
	std::vector<unsigned int>m_indices;
public:
	enum ShadingMode { Simple, Gouraud, Phong };
	enum RenderMode { wire, fill };
public:
	Pipeline(int w, int h) :
		width(w), height(h), m_shader(nullptr), m_frontBuffer(nullptr), m_backBuffer(nullptr) {}
	~Pipeline();

	void initialize(); // 为shader和双缓冲区申请空间
	void clearBuffer(const Vec4 color, bool depth = false); // 清空缓冲区
	void setVertexBuffer(const std::vector<Vertex>vertices) { m_vertices = vertices; }
	void setIndexBuffer(const std::vector<unsigned int>indices) { m_indices = indices; }
	void setShaderMode(ShadingMode mode);
	void drawIndex(RenderMode mode, MainCamera* camera);
	void swapBuffer();
	unsigned char* output() { return m_frontBuffer->getColorBuffer(); } // 返还front缓冲区指针

	/**
	 * @brief 动态调整管线和缓冲区尺寸
	 */
	void resize(int w, int h);

	// 光栅化
	VertexOut lerp(const VertexOut n1, const VertexOut n2, float weight);
	void bresenham(const VertexOut from, const VertexOut to);
	void scanLinePerRow(const VertexOut left, const VertexOut right);
	void rasterTopTriangle(VertexOut v1, VertexOut v2, VertexOut v3);
	void rasterBottomTriangle(VertexOut v1, VertexOut v2, VertexOut v3);
	void edgeWalkingFillRasterization(VertexOut v1, VertexOut v2, VertexOut v3);
};