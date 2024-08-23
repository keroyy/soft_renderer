#pragma once
class Vec2 {
public:
	float x, y;
public:
	Vec2():x(0.0f),y(0.0f) {}
	Vec2(float tx,float ty):x(tx),y(ty){}
	Vec2(const Vec2& vec):x(vec.x), y(vec.y) {}
	~Vec2(){}

	void set(float tx, float ty);
	void setX(float tx);
	void setY(float ty);
	float length();
	Vec2 getNormalize();
	void normalize();

	Vec2 operator+(const Vec2& vec);
	Vec2 operator-(const Vec2& vec);
	Vec2 operator*(const float k);
	Vec2 operator/(const float k);
	void operator+=(const Vec2& vec);
	void operator-=(const Vec2& vec);
	void operator*=(const float k);
	void operator/=(const float k);
	Vec2 operator+() const;
	Vec2 operator-() const;

	Vec2 Vec2::lerp(const Vec2& vec, float weight)const;
};
