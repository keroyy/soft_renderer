#include "Vec3.h"
#include "math.h"

void Vec3::set(float tX, float tY, float tZ) {
    x = tX;
    y = tY;
    z = tZ;
}
void Vec3::setX(float tX) {
    x = tX;
}
void Vec3::setY(float tY) {
    y = tY;
}
void Vec3::setZ(float tZ) {
    z = tZ;
}
float Vec3::length() {
    return static_cast<float>
        (sqrt(static_cast<double>(x * x + y * y + z * z)));
}
Vec3 Vec3::getNormalize() {
    float tmp = this->length();
    Vec3 res(x / tmp, y / tmp, z / tmp);
    return res;
}
void Vec3::normalize() {
    float tmp = this->length();
    x /= tmp;
    y /= tmp;
    z /= tmp;
}

Vec3 Vec3::operator+(const Vec3& vec) {
    Vec3 res(x + vec.x, y + vec.y, z + vec.z);
    return res;
}
Vec3 Vec3::operator-(const Vec3& vec) {
    Vec3 res(x - vec.x, y - vec.y, z - vec.z);
    return res;
}
Vec3 Vec3::operator*(const float k) {
    Vec3 res(x * k, y * k, z * k);
    return res;
}
Vec3 Vec3::operator/(const float k) {
    if (k == 0.0f) {
        Vec3 res(0.0f, 0.0f, 0.0f);
        return res;
    }
    Vec3 res(x / k, y / k, z / k);
    return res;
}
void Vec3::operator+=(const Vec3& vec) {
    x += vec.x;
    y += vec.y;
    z += vec.z;
}
void Vec3::operator-=(const Vec3& vec) {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
}
void Vec3::operator/=(const float k) {
    if (k != 0.0f)x /= k;
    else x = 0.0f;
    if (k != 0.0f)y /= k;
    else y = 0.0f;
    if (k != 0.0f)z /= k;
    else z = 0.0f;
}
Vec3 Vec3::operator+() const {
    return *this;
}
Vec3 Vec3::operator-() const {
    Vec3 res(-x, -y, -z);
    return res;
}
float Vec3::dot(const Vec3& vec) const {
    return x * vec.x + y * vec.y + z * vec.z;
}
Vec3 Vec3::cross(const Vec3& vec) const {
    Vec3 res(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
    return res;
}
Vec3 Vec3::lerp(const Vec3& vec, float weight)const {
    Vec3 res;
    res.x = (1 - weight) * x + weight * vec.x;
    res.y = (1 - weight) * y + weight * vec.y;
    res.z = (1 - weight) * z + weight * vec.z;
    return res;
}