#include "Matrix.h"
#include "math.h"

void Matrix::set(float e, int x, int y) {
	ele[x][y] = e;
}

Matrix Matrix::operator+(const Matrix& mat) {
	Matrix res(*this);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res.ele[i][j] += mat.ele[i][j];
		}
	}
	return res;
}
Matrix Matrix::operator-(const Matrix& mat) {
	Matrix res(*this);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res.ele[i][j] -= mat.ele[i][j];
		}
	}
	return res;
}
Matrix Matrix::operator*(float k) {
    Matrix res(*this);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res.ele[i][j] *= k;
        }
    }
    return res;
}
Matrix Matrix::operator*(const Matrix& mat) {
    Matrix res(*this);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            float sum = 0;
            for (int k = 0; k < 4; k++)
                sum += res.ele[i][k] * mat.ele[k][j];
            res.ele[i][j] = sum;
        }
    }
    return res;
}
Vec4 Matrix::operator*(const Vec4 vec) {
    Vec4 res;
    res.x = ele[0][0] * vec.x + ele[0][1] * vec.y + ele[0][2] * vec.z + ele[0][3] * vec.w;
    res.y = ele[1][0] * vec.x + ele[1][1] * vec.y + ele[1][2] * vec.z + ele[1][3] * vec.w;
    res.z = ele[2][0] * vec.x + ele[2][1] * vec.y + ele[2][2] * vec.z + ele[2][3] * vec.w;
    res.w = ele[3][0] * vec.x + ele[3][1] * vec.y + ele[3][2] * vec.z + ele[3][3] * vec.w;
    return res;
}
Matrix Matrix::operator/(const float k)
{
    return Matrix();
}
void Matrix::operator+=(const Matrix& mat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->ele[i][j] += mat.ele[i][j];
        }
    }
}
void Matrix::operator-=(const Matrix& mat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->ele[i][j] -= mat.ele[i][j];
        }
    }
}
void Matrix::operator*= (const float k) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->ele[i][j] *= k;
        }
    }
}
void Matrix::operator*= (const Matrix& mat) {
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            float sum = 0;
            for (int k = 0; k < 4; k++)
                sum += ele[i][k]*mat.ele[k][j];
            ele[i][j] = sum;
        }
    }
}
void Matrix::operator/=(const float k) {
    if (k == 0.0f) {
        Matrix res;
        for (int i = 0; i < 4; i++)for (int j = 0; j < 4; j++)this->ele[i][j] = 0;
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->ele[i][j] /= k;
        }
    }
}
Matrix Matrix::operator+() const {
    return *this;
}
Matrix Matrix::operator-() const {
    Matrix res(*this);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res.ele[i][j] = this->ele[i][j] * (-1);
        }
    }
    return res;
}

void Matrix::normalize() {
    for (int i = 0; i < 4; i++)for (int j = 0; j < 4; j++)ele[i][j] = 0;
    for (int i = 0; i < 4; i++)ele[i][i] = 1;
}
void Matrix::transposition() {
    Matrix tmp;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            tmp.ele[i][j] = ele[j][i];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            ele[i][j] = tmp.ele[i][j];
}
void Matrix::translation(const Vec3& trans) {
    normalize();
    ele[0][3] = trans.x;
    ele[1][3] = trans.y;
    ele[2][3] = trans.z;
}
void Matrix::scale(const Vec3& sca) {
    normalize();
    ele[0][0] *= sca.x;
    ele[1][1] *= sca.y;
    ele[2][2] *= sca.z;
}
void Matrix::rotationX(const double angle) {
    normalize();
    float a = static_cast<float>(angle);
    ele[1][1] = cosf(a);
    ele[1][2] = -sinf(a);
    ele[2][1] = sinf(a);
    ele[2][2] = cosf(a);
}
void Matrix::rotationY(const double angle) {
    normalize();
    float a = static_cast<float>(angle);
    ele[0][0] = cosf(a);
    ele[0][2] = sinf(a);
    ele[2][0] = -sinf(a);
    ele[2][2] = cosf(a);
}
void Matrix::rotationZ(const double angle) {
    normalize();
    float a = static_cast<float>(angle);
    ele[0][0] = cosf(a);
    ele[0][1] = -sinf(a);
    ele[1][0] = sinf(a);
    ele[1][1] = cosf(a);
}

void Matrix::lookat(Vec3 camPos, Vec3 tarPos, Vec3 up) {
    Vec3 xAxis, yAxis, zAxis;
    zAxis = -(tarPos - camPos);
    zAxis.normalize();
    xAxis = up.cross(zAxis);
    xAxis.normalize();
    yAxis = zAxis.cross(xAxis);
    yAxis.normalize();
    normalize();
    ele[0][0] = xAxis.x;
    ele[0][1] = xAxis.y;
    ele[0][2] = xAxis.z;
    ele[1][0] = yAxis.x;
    ele[1][1] = yAxis.y;
    ele[1][2] = yAxis.z; 
    ele[2][0] = zAxis.x;
    ele[2][1] = zAxis.y;
    ele[2][2] = zAxis.z;
    ele[0][3] = -(xAxis.dot(camPos));
    ele[1][3] = -(yAxis.dot(camPos));
    ele[2][3] = -(zAxis.dot(camPos));
}

//void Matrix::perspective(float fovy, float aspect, float near, float far) {
//    ele[0][0] = 1 / (aspect * tanf(fovy / 2));
//    ele[1][1] = 1 / (tanf(fovy / 2));
//    ele[2][2] = -((far + near) / (far - near));
//    ele[2][3] = -(2 * far * near) / (far - near);
//    ele[3][2] = -1;
//}

void Matrix::perspective(float fovy, float aspect, float near, float far) {
    float f = 1.0f / tan(fovy / 2.0f);

    ele[0][0] = f / aspect;
    ele[1][1] = f;
    ele[2][2] = (far + near) / (near - far);
    ele[2][3] = -1.0f;
    ele[3][2] = (2.0f * far * near) / (near - far);
}

//void Matrix::viewport(int left, int top, int width, int height) {
//    normalize();
//    ele[0][0] = static_cast<float>(width) / 2.0f;
//    ele[1][1] = -static_cast<float>(height) / 2.0f;
//    ele[0][3] = static_cast<float>(left) + static_cast<float>(width) / 2.0f;
//    ele[1][3] = static_cast<float>(top) + static_cast<float>(height) / 2.0f;
//}

void Matrix::viewport(int width, int height) {
    normalize();
    ele[0][0] = static_cast<float>(width) / 2.0f;
    ele[1][1] = -static_cast<float>(height) / 2.0f;
    ele[2][2] = 0.5f;
    ele[0][3] = (static_cast<float>(width)) / 2.0f;
    ele[1][3] = (static_cast<float>(height)) / 2.0f;
    ele[2][3] = 0.5f;
}

