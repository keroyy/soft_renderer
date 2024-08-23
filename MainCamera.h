#pragma once
#include "Vec3.h"

class MainCamera
{
public:
	Vec3 pos, target, up; // target:相机看向的目标点  up:相机自身z轴方向
	float fov, asp, near, far;
public:
	MainCamera();
	/***************************************************************
	* @param pos, target, up, fov, asp, near, far
	 **************************************************************/
	MainCamera(Vec3 mpos, Vec3 mtarget, Vec3 mup, float mfov, float masp, float mnear, float mfar);
	void setPosition(Vec3 mpos);
	void setPosition(float x, float y, float z);
	void rotateY(float angle);
};