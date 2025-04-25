#pragma once
#include "Vec4.h"
#include "Shader.h"
#include "DepthBuffer.h"
#include <vector>

class FrameBuffer {
private:
	int width, height;
	unsigned char mp[8294405]; // 1920*1080，每个像素需要有4个通道信息，因此数据数组的大小至少为1920*1080*4=8294400
	DepthBuffer depthBuffer[1925][1085]; // 1920 * 1080 深度缓冲
	std::vector<double> m_depthBuffer;
public:
	FrameBuffer(int w,int h):width(w),height(h){
		// 初始化深度缓冲
		//for (int i = 0; i < width; ++i) {
		//	for (int j = 0; j < height; ++j) {
		//		depthBuffer[i][j].setDepth(1.0f); // 默认值为最大深度，表示远离相机
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
	  *  @brief     初始化颜色值
	  *  @param     RGBA四个通道
	  *  @note      传入的vec向量的rgb值范围是[0,1]，表示的是一个比率，而最后写入到数据里需要映射到[0,255]
	  *  @Sample usage:     函数的使用方法
	 **************************************************************/
	void Fill(Vec4 vec); 

	/***************************************************************
	  *  @brief     更新颜色值
	  *  @param     坐标（x,y）和颜色值
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