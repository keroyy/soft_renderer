#pragma once
#include "Vec4.h"
#include "Shader.h"
#include "DepthBuffer.h"
#include <vector>

class FrameBuffer {
private:
	int width, height;
	unsigned char mp[8294405]; // 1920*1080��ÿ��������Ҫ��4��ͨ����Ϣ�������������Ĵ�С����Ϊ1920*1080*4=8294400
	DepthBuffer depthBuffer[1925][1085]; // 1920 * 1080 ��Ȼ���
	std::vector<double> m_depthBuffer;
public:
	FrameBuffer(int w,int h):width(w),height(h){
		// ��ʼ����Ȼ���
		//for (int i = 0; i < width; ++i) {
		//	for (int j = 0; j < height; ++j) {
		//		depthBuffer[i][j].setDepth(1.0f); // Ĭ��ֵΪ�����ȣ���ʾԶ�����
		//	}
		//}
		for (unsigned int row = 0; row < height; ++row)
		{
			for (unsigned int col = 0; col < width; ++col)
			{
				//m_depthBuffer[row * width + col] = 1.0f;
				m_depthBuffer.push_back(1.0f);
			}
		}
	}
	~FrameBuffer(){}

	/***************************************************************
	  *  @brief     ��ʼ����ɫֵ
	  *  @param     RGBA�ĸ�ͨ��
	  *  @note      �����vec������rgbֵ��Χ��[0,1]����ʾ����һ�����ʣ������д�뵽��������Ҫӳ�䵽[0,255]
	  *  @Sample usage:     ������ʹ�÷���
	 **************************************************************/
	void Fill(Vec4 vec); 

	/***************************************************************
	  *  @brief     ������ɫֵ
	  *  @param     ���꣨x,y������ɫֵ
	  *  @note      
	  *  @Sample usage:     
	 **************************************************************/
	void Cover(int x, int y, Vec4 vec);
	void setDepthBuffer(VertexOut zBuffer);
	DepthBuffer getDepthBuffer(int x, int y);
	unsigned char* getColorBuffer();

	void clearDepthBuffer();
	double getDepth(const unsigned int& x, const unsigned int& y)const;
	void drawDepth(const unsigned int& x, const unsigned int& y, const double& value);

	void resize(int w, int h);
};