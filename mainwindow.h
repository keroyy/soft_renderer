#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include <QPainter>
#include <QWidget>
#include <QThread>
#include "RenderRoute.h"

class mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    mainwindow(QWidget *parent = nullptr);
    ~mainwindow();

    /***************************************************************
      ���ܴ�renderRoute�з����front�Ļ�������
     **************************************************************/
protected slots: // ��
    void receiveFrame(unsigned char* data);

private:
    void paintEvent(QPaintEvent *)override;

private:
    Ui::mainwindowClass *ui;
    /*unsigned char* data*/; // ��ɫ����
    QImage* canvas;
    RenderRoute* loop;
    QThread* loopThread;
};
