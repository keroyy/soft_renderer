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
      接受从renderRoute中发射的front的缓存数据
     **************************************************************/
protected slots: // 槽
    void receiveFrame(unsigned char* data);

private:
    void paintEvent(QPaintEvent *)override;

private:
    Ui::mainwindowClass *ui;
    /*unsigned char* data*/; // 颜色数据
    QImage* canvas;
    RenderRoute* loop;
    QThread* loopThread;
};
