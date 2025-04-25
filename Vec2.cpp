#include "Vec2.h"
#include "math.h"

void Vec2::set(float tx, float ty) {
	x = tx;
	y = ty;
}
void Vec2::setX(float tx) {
	x = tx;
}
void Vec2::setY(float ty) {
	y = ty;
}
float Vec2::length() {
	return static_cast<float>(static_cast<double>(x * x + y * y));
}
Vec2 Vec2::getNormalize() {
	float tmp = this->length();
	Vec2 res(x / tmp, y / tmp);
	return res;
}
void Vec2::normalize() {
	float tmp = this->length();
	x /= tmp;
	y /= tmp;
}
Vec2 Vec2::operator+(const Vec2& vec) {
	Vec2 res(x + vec.x, y + vec.y);
	return res;
}
Vec2 Vec2::operator-(const Vec2& vec) {
	Vec2 res(x - vec.x, y - vec.y);
	return res;
}
Vec2 Vec2::operator*(const float k) {
	Vec2 res(x * k, y * k);
	return res;
}
Vec2 Vec2::operator/(const float k) {
	if (k == 0.0f) {
		Vec2 res(0.0f, 0.0f);
		return res;
	}
	Vec2 res(x / k, y / k);
	return res;
}
void Vec2::operator+=(const Vec2& vec) {
	x += vec.x;
	y += vec.y;
}
void Vec2::operator-=(const Vec2& vec) {
	x -= vec.x;
	y -= vec.y;
}
void Vec2::operator*=(const float k) {
	x *= k;
	y *= k;
}
void Vec2::operator/=(const float k) {
	if (k != 0.0f)x /= k;
	else x = 0.0f;
	if (k != 0.0f)y /= k;
	else y = 0.0f;
}
Vec2 Vec2::operator+() const {
	return *this;
}
Vec2 Vec2::operator-() const {
	Vec2 res(-x, -y);
	return res;
}
Vec2 operator*(float k, const Vec2& vec) {
	return Vec2(vec.x * k, vec.y * k);
}
Vec2 Vec2::lerp(const Vec2& vec, float weight)const {
	Vec2 res;
	res.x = (1 - weight) * x + weight * vec.x;
	res.y = (1 - weight) * y + weight * vec.y;
	return res;
}

