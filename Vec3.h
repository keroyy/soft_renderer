#pragma once
class Vec3
{
public:
    float x, y, z;
public:
    Vec3() :x(0.0f), y(0.0f), z(0.0f) {}
    Vec3(float tX, float tY, float tZ) :x(tX), y(tY), z(tZ) {}
    Vec3(const Vec3& vec) :x(vec.x), y(vec.y), z(vec.z) {}
    ~Vec3() {}

    void set(float tX, float tY, float tZ);
    void setX(float tX);
    void setY(float tY);
    void setZ(float tZ);
    float length();
    Vec3 getNormalize();
    void normalize();

    Vec3 operator+(const Vec3& vec);
    Vec3 operator-(const Vec3&  vec);
    Vec3 operator*(const float k);
    Vec3 operator/(const float k);
    void operator+=(const Vec3& vec);
    void operator-=(const Vec3& vec);
    void operator/=(const float k);
    Vec3 operator+() const;
    Vec3 operator-() const;

    float dot(const Vec3& vec) const;
    Vec3 cross(const Vec3& vec) const;
    Vec3 Vec3::lerp(const Vec3& vec, float weight)const;
};
