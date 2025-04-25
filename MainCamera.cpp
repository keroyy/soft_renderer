#include "MainCamera.h"
#include "Vec4.h"
#include "Matrix.h"
#include "stdio.h"

MainCamera::MainCamera(int w, int h) {
	pos = Vec3(0, 0, 3);
	target = Vec3(0, 0, 0);
	up = Vec3(0, 1, 0);
	fov = 45 * 3.14 / 180.f;
	asp = static_cast<float>(w) / h;
	near = 1.f;
	far = 50.f;
}

MainCamera::MainCamera(Vec3 mpos, Vec3 mtarget, Vec3 mup, float mfov, float masp, float mnear, float mfar) {
	pos = mpos;
	target = mtarget;
	up = mup;
	fov = mfov * 3.14 / 180.f;
	asp = masp;
	near = mnear;
	far = mfar;
}

void MainCamera::rotateY(float angle) {
	Vec4 pos4(pos.x, pos.y, pos.z, 1);
	Matrix rotMat;
	rotMat.normalize();
	rotMat.rotationY(angle);
	pos4 = rotMat * pos4;
	pos.set(pos4.x, pos4.y, pos4.z);
}

void MainCamera::setPosition(Vec3 mpos) {
	pos = mpos;
}

void MainCamera::setPosition(float x, float y, float z) {
	pos.x = x;
	pos.y = y;
	pos.z = z;
}