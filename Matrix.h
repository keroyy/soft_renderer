#pragma once
#include "Vec3.h"
#include "Vec4.h"
class Matrix {
public:
	float ele[4][4];
public:
	Matrix():ele{0.0f}{}
	Matrix(float a00, float a01, float a02, float a03,
		float a10, float a11, float a12, float a13,
		float a20, float a21, float a22, float a23,
		float a30, float a31, float a32, float a33)
		:ele{ a00,a01,a02,a03,a10,a11,a12,a13,a20,a21,a22,a23,a30,a31,a32,a33 }{}
	Matrix(const Matrix& mat):ele{ mat.ele[0][0],mat.ele[0][1],mat.ele[0][2],mat.ele[0][3],
		 mat.ele[1][0],mat.ele[1][1],mat.ele[1][2],mat.ele[1][3],
		 mat.ele[2][0],mat.ele[2][1],mat.ele[2][2],mat.ele[2][3],
		 mat.ele[3][0],mat.ele[3][1],mat.ele[3][2],mat.ele[3][3] }{}
	~Matrix(){}


	/***************************************************************
	  *  @brief     修改矩阵中任意位置的元素
	  *  @param     值，行数，列数
	  *  @note      备注
	  *  @Sample usage:     函数的使用方法
	 **************************************************************/
	void set(float e, int x, int y);

	Matrix operator+(const Matrix& mat);
	Matrix operator-(const Matrix& mat);
	Matrix operator*(const float k);
	Matrix operator*(const Matrix& mat);
	Vec4 operator*(const Vec4 vec);
	Matrix operator/(const float k);
	void operator+=(const Matrix& mat);
	void operator-=(const Matrix& mat);
	void operator*=(const float k);
	void operator*=(const Matrix& mat);
	void operator/=(const float k);
	Matrix operator+() const;
	Matrix operator-() const;

	void normalize();
	/***************************************************************
	  *  @brief     行列互换
	 **************************************************************/
	void transposition();
	void translation(const Vec3& trans);
	void scale(const Vec3& sca);
	void rotationX(const double angle);
	void rotationY(const double angle);
	void rotationZ(const double angle);

	// world -> view
	void lookat(Vec3 camPos, Vec3 tarPos, Vec3 up);

	// view -> projection
	void perspective(float fovy, float aspect, float near, float far);

	// ndc -> screen
	//void viewport(int x,int y,int width, int height);
	void viewport(int width, int height);
};