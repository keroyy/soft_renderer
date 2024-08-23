#include "RenderRoute.h"
#include "Mesh.h"
#include "MainCamera.h"
#define PI 3.14159265359

RenderRoute::RenderRoute(int w, int h, QObject* parent) :QObject(parent), width(w), height(h), channel(4)
{
	stopped = false;
	pipeline = new Pipeline(width, height);
}

void RenderRoute::stopIt() {
	stopped = true;
}

void RenderRoute::loop()
{
	pipeline->initialize();
	Vec3 v1(-10, -10, 0), v2(0, 10, 0), v3(10, -10, 0);
	Mesh* msh=new Mesh();
	//msh->triangle(v1, v2, v3);
	msh->cube(10, 10, 10, 1, Vec4(0.f, 0.f, 0.f, 1.0f));
	MainCamera* camera = new MainCamera();
	camera->setPosition(0, 0, -15);
	pipeline->setVertexBuffer(msh->vertices);
	pipeline->setIndexBuffer(msh->index);

	while (!stopped) {
		pipeline->clearBuffer(Vec4(0.9f, 0.9f, 0.9f, 1.0f));
		pipeline->drawIndex(Pipeline::RenderMode::fill, camera);
		pipeline->swapBuffer();
		emit frameOut(pipeline->output()); //将渲染管线中front缓冲区中的颜色数据发射出去。
		camera->rotateY(0.1f * PI / 6);
	}
}