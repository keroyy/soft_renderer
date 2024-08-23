#pragma once
#include "Vec3.h"
class Vec4
{
public:
    float x, y, z, w;
public:
    Vec4() :x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    Vec4(float tX, float tY, float tZ, float tW) :x(tX), y(tY), z(tZ), w(tW) {}
    Vec4(const Vec4& vec) :x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}
    Vec4(const Vec3& vec,float tw) :x(vec.x), y(vec.y), z(vec.z), w(tw) {}
    ~Vec4() {}

    void set(float tX, float tY, float tZ, float tW);
    void setX(float tX);
    void setY(float tY);
    void setZ(float tZ);
    void setW(float tW);
    float length();
    Vec4 getNormalize();
    void normalize();

    void operator=(const Vec3& vec);
    Vec4 operator+(const Vec4& vec)const;
    Vec4 operator-(const Vec4& vec)const;
    Vec4 operator*(const float& t)const;
    Vec4 operator/(const Vec4& vec)const;
    Vec4 operator/(const float& t)const;
    void operator+=(const Vec4& vec);
    void operator-=(const Vec4& vec);
    void operator/=(const float& t);
    Vec4 operator+() const;
    Vec4 operator-() const;

    float dot(const Vec4& vec) const;
    Vec4 lerp(const Vec4& vec, float weight)const;
};