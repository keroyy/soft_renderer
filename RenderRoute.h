#pragma once
#include "QObject"
#include "Pipeline.h"
/***************************************************************
	  渲染循环，它的作用主要有两部分:
	  第一是储存待渲染的对象，然后逐步调用渲染管线类中的方法完成渲染；
	  第二是在渲染结束的时候将讯息及时送往渲染器窗口mainwindow。
	 **************************************************************/
class RenderRoute :public QObject
{
	Q_OBJECT
public:
	explicit RenderRoute(int w, int h, QObject* parent = nullptr);
	~RenderRoute() {}
	void stopIt();
signals:
	void frameOut(unsigned char* image);
public slots:
	void loop();
private:
	bool stopped;
	int width, height, channel; // 宽、高、通道数
	Pipeline* pipeline;
};