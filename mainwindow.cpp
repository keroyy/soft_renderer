#include "mainwindow.h"
#include "RenderRoute.h"
#include <QPainter>
#include <iostream>

mainwindow::mainwindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::mainwindowClass)
{
    ui->setupUi(this);
    this->resize(1280, 768);
    canvas = new QImage(width(), height(), QImage::Format_RGBA8888);
    loop = new RenderRoute(width(), height(), nullptr);
    loopThread = new QThread(this);
    loop->moveToThread(loopThread);
    connect(loopThread, &QThread::finished, loop, &RenderRoute::deleteLater);
    connect(loopThread, &QThread::started, loop, &RenderRoute::loop);
    connect(loop, &RenderRoute::frameOut, this, &mainwindow::receiveFrame);
    loopThread->start();
}

mainwindow::~mainwindow()
{
    delete ui;
    loop->stopIt();
    loopThread->quit();
    loopThread->wait();
    if (canvas)delete canvas;
    if (loopThread)delete loopThread;
    loop = nullptr;
    canvas = nullptr;
    loopThread = nullptr;
}

void mainwindow::receiveFrame(unsigned char* data) {
    if (canvas) delete canvas;
    canvas = new QImage(data, width(), height(), QImage::Format_RGBA8888);
    update();
}

void mainwindow::paintEvent(QPaintEvent* event) {
    if (canvas) {
        QPainter painter(this);
        painter.drawImage(0, 0, *canvas);
    }
    QWidget::paintEvent(event);
}
