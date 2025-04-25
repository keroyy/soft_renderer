#include "FrameBuffer.h"
#include "iostream"

void FrameBuffer::Fill(Vec4 vec) {
	unsigned char cl[4];
	cl[0] = static_cast<unsigned char>(vec.x * 255);
	cl[1] = static_cast<unsigned char>(vec.y * 255);
	cl[2] = static_cast<unsigned char>(vec.z * 255);
	cl[3] = static_cast<unsigned char>(vec.w * 255);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			for (int k = 0; k < 4; k++) {
				mp[(i * width + j) * 4 + k] = cl[k];
			}
		}
	}
}
void FrameBuffer::Cover(int x, int y, Vec4 vec) {
    // 检查坐标范围
    if (x >= 0 && x < width && y >= 0 && y < height) {
        unsigned char cl[4] = {
            static_cast<unsigned char>(vec.x * 255),
            static_cast<unsigned char>(vec.y * 255),
            static_cast<unsigned char>(vec.z * 255),
            static_cast<unsigned char>(vec.w * 255)
        };

        for (int k = 0; k < 4; k++) {
            mp[(y * width + x) * 4 + k] = cl[k];
        }
    }
    else {
        // 处理越界情况，可以选择忽略或者进行错误处理
        std::cout << "Warning: Coordinates out of bounds." << std::endl;
    }

} 

void FrameBuffer::resize(int w, int h) {
    width = w;
    height = h;

    // 重建深度缓冲向量
    m_depthBuffer.clear();
    m_depthBuffer.reserve(width * height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            m_depthBuffer.push_back(1.0);
        }
    }
}

void FrameBuffer::setDepthBuffer(VertexOut zBuffer) {
    //unsigned int xx = static_cast<unsigned int>(zBuffer.screenPos.x), yy = static_cast<unsigned int>(zBuffer.screenPos.y);
    unsigned int xx = zBuffer.screenPos.x, yy = zBuffer.screenPos.y;
    depthBuffer[xx][yy].setDepth(zBuffer.screenPos.z);
    depthBuffer[xx][yy].setBuffer(zBuffer);
}
DepthBuffer FrameBuffer::getDepthBuffer(int x, int y) {
    return depthBuffer[x][y];
}
unsigned char* FrameBuffer::getColorBuffer() {
	return mp;
}

void FrameBuffer::clearDepthBuffer() {
    for (unsigned int row = 0; row < height; ++row)
    {
        for (unsigned int col = 0; col < width; ++col)
        {
            m_depthBuffer[row * width + col] = 1.0f;
            //depthBuffer[row][col].setDepth(1.0f);
        }
    }
}
double FrameBuffer::getDepth(const unsigned int& x, const unsigned int& y)const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return 0.0f;
    }
    return m_depthBuffer[y * width + x];
}
void FrameBuffer::drawDepth(const unsigned int& x, const unsigned int& y, const double& value) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }
    unsigned int index = y * width + x;
    m_depthBuffer[index] = value;
}
