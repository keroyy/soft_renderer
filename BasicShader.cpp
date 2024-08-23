#include "BasicShader.h"/
#include "Vec3.h"

BasicShader::BasicShader()
{
	worldMatrix.normalize();
	viewMatrix.normalize();
	projectMatrix.normalize();
	texture = new Textures();
	texture->loadImage("D:/Resources/textures/container.jpg");
}

void BasicShader::setCamera(Vec3 pos, Vec3 target, Vec3 up, float fov, float asp, float near, float far)
{
	viewMatrix.lookat(pos, target, up);
	projectMatrix.perspective(fov, asp, near, far);
}

VertexOut BasicShader::vertexShader(const Vertex in) {
	VertexOut ret;
	ret.worldPos = worldMatrix * in.position;
	Vec4 temp = viewMatrix * ret.worldPos; // viewSpace
	ret.projPos = projectMatrix * temp;
	ret.color = in.color;
	ret.normal = in.normal;
	ret.oneDivZ = 1.0;
	ret.texcoord = in.texcoord;
	//ret.textureName = in.textureName;
	return ret;
}

Vec4 BasicShader::fragmentShader(const VertexOut in) {
	Vec4 retColor;
	//retColor = in.color;
	retColor = texture->sample(in.texcoord);
	return retColor;
}