#include "Vec4.h"
#include "math.h"
void Vec4::set(float tX, float tY, float tZ, float tW) {
    x = tX;
    y = tY;
    z = tZ;
    w = tW;
}
void Vec4::setX(float tX) {
    x = tX;
}
void Vec4::setY(float tY) {
    y = tY;
}
void Vec4::setZ(float tZ) {
    z = tZ;
}
void Vec4::setW(float tW) {
    w = tW;
}
float Vec4::length() {
    return static_cast<float>
        (sqrt(static_cast<double>(x * x + y * y + z * z + w * w)));
}
Vec4 Vec4::getNormalize() {
    float tmp = this->length();
    Vec4 res(x / tmp, y / tmp, z / tmp, w / tmp);
    return res;
}
void Vec4::normalize() {
    float tmp = this->length();
    x /= tmp;
    y /= tmp;
    z /= tmp;
    w /= tmp;
}

void Vec4::operator=(const Vec3& vec) {
    x = vec.x;
    y = vec.y;
    z = vec.z;
    w = 1;
}
Vec4 Vec4::operator+(const Vec4& vec)const {
    Vec4 res(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
    return res;
}
Vec4 Vec4::operator-(const Vec4& vec)const {
    Vec4 res(x - vec.x, y + vec.y, z - vec.z, w - vec.w);
    return res;
}
Vec4 Vec4::operator*(const float& t)const {
    Vec4 res(x * t, y * t, z * t, w * t);
    return res;
}
Vec4 Vec4::operator/(const Vec4& vec)const {
    if (vec.x == 0.0f || vec.y == 0.0f || vec.z == 0.0f || vec.w == 0.0f) {
        Vec4 res(0.0f, 0.0f, 0.0f, 0.0f);
        return res;
    }
    Vec4 res(x / vec.x, y / vec.y, z / vec.z, w / vec.w);
    return res;
}
Vec4 Vec4::operator/(const float& t)const {
    if (t == 0.0f) {
        Vec4 res(0.0f, 0.0f, 0.0f, 0.0f);
        return res;
    }
    Vec4 res(x / t, y / t, z / t, w / t);
    return res;
}
void Vec4::operator+=(const Vec4& vec) {
    x += vec.x;
    y += vec.y;
    z += vec.z;
    w += vec.w;
}
void Vec4::operator-=(const Vec4& vec) {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    w -= vec.w;
}
void Vec4::operator/=(const float& t) {
    if (t == 0.0f)return;
    x /= t;
    y /= t;
    z /= t;
    w /= t;
}
Vec4 Vec4::operator+() const {
    return *this;
}
Vec4 Vec4::operator-() const {
    Vec4 res(-x, -y, -z, -w);
    return res;
}
float Vec4::dot(const Vec4& vec) const {
    return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
}
Vec4 Vec4::lerp(const Vec4& vec, float weight)const {
    Vec4 res;
    res.x = (1 - weight) * x + weight * vec.x;
    res.y = (1 - weight) * y + weight * vec.y;
    res.z = (1 - weight) * z + weight * vec.z;
    res.w = (1 - weight) * w + weight * vec.w;
    return res;
}