#include "MainWindow.h"
#include "RenderRoute.h"
#include <QPainter>
#include <iostream>
#include <QResizeEvent>
#include <Qdebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::mainwindowClass)
{
    ui->setupUi(this);
    this->resize(width(), height());
    canvas = new QImage(width(), height(), QImage::Format_RGBA8888);
    loop = new RenderRoute(width(), height(), nullptr);
    loopThread = new QThread(this);
    loop->moveToThread(loopThread);
    connect(loopThread, &QThread::finished, loop, &RenderRoute::deleteLater);
    connect(loopThread, &QThread::started, loop, &RenderRoute::loop);
    connect(loop, &RenderRoute::frameOut, this, &MainWindow::receiveFrame);
    loopThread->start();
}

MainWindow::~MainWindow()
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

void MainWindow::receiveFrame(unsigned char* data) {
    if (canvas) delete canvas;
    canvas = new QImage(data, width(), height(), QImage::Format_RGBA8888);
    update();
}

void MainWindow::paintEvent(QPaintEvent* event) {
    if (canvas) {
        QPainter painter(this);
        painter.drawImage(0, 0, *canvas);
    }
    QWidget::paintEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);

    const int newW = event->size().width();
    const int newH = event->size().height();

    // 1. ���·��仭��
    delete canvas;
    canvas = new QImage(newW, newH, QImage::Format_RGBA8888);
    // 2. ֪ͨ��Ⱦ�̸߳��³ߴ�
    if (loop && loopThread->isRunning()) { // loop �� RenderRoute ʵ��
        QMetaObject::invokeMethod(
            loop,
            "setSize",
            Qt::QueuedConnection,
            Q_ARG(int, newW),
            Q_ARG(int, newH)
        );
    }

    // 3. ǿ�ƴ��������ػ棬�� paintEvent ��ʹ���� canvas
    update();
}

