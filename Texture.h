#pragma once
#include "Vec2.h"
#include "Vec4.h"
#include <qmainwindow>
#include <qstring>

class Textures
{
private:
    int width, height, channel;
    QImage* pixelBuffer;
public:
    Textures();
    ~Textures();
    void loadImage(const QString path);
    Vec4 sample(const Vec2& texcoord);
};
