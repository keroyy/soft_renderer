#pragma once
#include "QObject"
#include "Pipeline.h"
/***************************************************************
	  ��Ⱦѭ��������������Ҫ��������:
	  ��һ�Ǵ������Ⱦ�Ķ���Ȼ���𲽵�����Ⱦ�������еķ��������Ⱦ��
	  �ڶ�������Ⱦ������ʱ��ѶϢ��ʱ������Ⱦ������mainwindow��
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
	int width, height, channel; // ���ߡ�ͨ����
	Pipeline* pipeline;
};