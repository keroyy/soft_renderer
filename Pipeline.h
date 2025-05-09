#pragma once
#include "Shader.h"
#include "FrameBuffer.h"
#include "Matrix.h"
#include <vector>
#include "MainCamera.h"

/***************************************************************
	  ���ȣ���Ϊ�ƿ�ȫ�ֵĹ��ߣ��ض��е�����������㡢������ɫ��������ɫ����֡��������Σ���ô������ӵ��һ����������ָ�룬�ұ���֪����ǰ�����ĳ����
	  ���⣬��Ⱦ������Ҫ�õ����е�ģ�������Լ������ζ������������ܽ�����������������Ⱦ���߱���֪���Լ�ʹ�õ�����һ����ɫ����
����	  ����֮�⣬���ǻ���һЩ���ÿ��Խ���ѡ���������ģʽShadingMode����դ��ģʽRenderMode���������ν������߻�����䣩��
	 **************************************************************/
class Pipeline {
private:
	int width, height;
	Shader* m_shader;
	FrameBuffer* m_frontBuffer; // �ݴ桢����
	FrameBuffer* m_backBuffer; // ��̬д��
	std::vector<Vertex>m_vertices;
	std::vector<unsigned int>m_indices;
public:
	enum ShadingMode { Simple, Gouraud, Phong };
	enum RenderMode { wire, fill };
public:
	Pipeline(int w, int h) :
		width(w), height(h), m_shader(nullptr), m_frontBuffer(nullptr), m_backBuffer(nullptr) {}
	~Pipeline();

	void initialize(); // Ϊshader��˫����������ռ�
	void clearBuffer(const Vec4 color, bool depth = false); // ��ջ�����
	void setVertexBuffer(const std::vector<Vertex>vertices) { m_vertices = vertices; }
	void setIndexBuffer(const std::vector<unsigned int>indices) { m_indices = indices; }
	void setShaderMode(ShadingMode mode);
	void drawIndex(RenderMode mode, MainCamera* camera);
	void swapBuffer();
	unsigned char* output() { return m_frontBuffer->getColorBuffer(); } // ����front������ָ��

	/**
	 * @brief ��̬�������ߺͻ������ߴ�
	 */
	void resize(int w, int h);

	// ��դ��
	VertexOut lerp(const VertexOut n1, const VertexOut n2, float weight);
	void bresenham(const VertexOut from, const VertexOut to);
	void scanLinePerRow(const VertexOut left, const VertexOut right);
	void rasterTopTriangle(VertexOut v1, VertexOut v2, VertexOut v3);
	void rasterBottomTriangle(VertexOut v1, VertexOut v2, VertexOut v3);
	void edgeWalkingFillRasterization(VertexOut v1, VertexOut v2, VertexOut v3);
};