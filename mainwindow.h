#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include <QPainter>
#include <QWidget>
#include <QThread>
#include "RenderRoute.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /***************************************************************
      ���ܴ�renderRoute�з����front�Ļ�������
     **************************************************************/
protected slots: // ��
    void receiveFrame(unsigned char* data);

private:
    void paintEvent(QPaintEvent *)override;

private:
    void resizeEvent(QResizeEvent* event)override;

private:
    Ui::mainwindowClass *ui;
    /*unsigned char* data*/; // ��ɫ����
    QImage* canvas;
    RenderRoute* loop;
    QThread* loopThread;
};
