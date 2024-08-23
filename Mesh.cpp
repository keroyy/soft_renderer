#include "Mesh.h"

Mesh Mesh::operator=(const Mesh& msh) {
	vertices = msh.vertices;
	index = msh.index;
	return *this;                     
}

void Mesh::setVertices(Vertex* v, int count) {
	vertices.resize(static_cast<unsigned long>(count));
	new(&vertices[0])std::vector<Vertex>(v, v + count);
}

void Mesh::setIndex(int* i, int count) {
	index.resize(static_cast<unsigned long>(count));
	new(&index)std::vector<unsigned int>(i, i + count);
}

void Mesh::triangle(Vec3 v1, Vec3 v2, Vec3 v3) {
	vertices.resize(3);
	index.resize(3);
    vertices[0].position = Vec4(v1, 1.0f);
    vertices[0].normal = Vec3(0.f, 0.f, 1.f);
    vertices[0].color = Vec4(1.f, 0.f, 0.f, 1.f);
    vertices[0].texcoord = Vec2(0.f, 0.f);
    vertices[1].position = Vec4(v2, 1.0f);
    vertices[1].normal = Vec3(0.f, 0.f, 1.f);
    vertices[1].color = Vec4(0.f, 1.f, 0.f, 1.f);
    vertices[1].texcoord = Vec2(1.f, 0.f);
    vertices[2].position = Vec4(v3, 1.0f);
    vertices[2].normal = Vec3(0.f, 0.f, 1.f);
    vertices[2].color = Vec4(0.f, 0.f, 1.f, 1.f);
    vertices[2].texcoord = Vec2(0.5f, 1.f);
    index[0] = 0;
    index[1] = 1;
    index[2] = 2;
}

void Mesh::cube(double width, double height, double depth, int id, Vec4 pos) {
    vertices.resize(4 * 6);
    index.resize(6 * 6);
    float cubeVertices[] = {
        // Positioin                                                     Normal              Color                    Texcoord
        pos.x - width / 2, pos.y - height / 2, pos.z - depth / 2, pos.w, 0.0f, 0.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0, 0.0f, 0.0f,      // 左下
        pos.x + width / 2, pos.y - height / 2, pos.z - depth / 2, pos.w, 0.0f, 0.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0, 1.0f, 0.0f,      // 右下
        pos.x + width / 2, pos.y + height / 2, pos.z - depth / 2, pos.w, 0.0f, 0.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0, 1.0f, 1.0f,      // 右上
        pos.x - width / 2, pos.y + height / 2, pos.z - depth / 2, pos.w, 0.0f, 0.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0, 0.0f, 1.0f,      // 左上
                                                                  
        pos.x - width / 2, pos.y - height / 2, pos.z + depth / 2, pos.w, 0.0f, 0.0f, 1.0f,   1.0f,  0.0f,  0.0f, 1.0, 0.0f, 0.0f,      // 左下
        pos.x + width / 2, pos.y - height / 2, pos.z + depth / 2, pos.w, 0.0f, 0.0f, 1.0f,   1.0f,  0.0f,  0.0f, 1.0, 1.0f, 0.0f,      // 右下
        pos.x + width / 2, pos.y + height / 2, pos.z + depth / 2, pos.w, 0.0f, 0.0f, 1.0f,   1.0f,  0.0f,  0.0f, 1.0, 1.0f, 1.0f,      // 右上
        pos.x - width / 2, pos.y + height / 2, pos.z + depth / 2, pos.w, 0.0f, 0.0f, 1.0f,   1.0f,  0.0f,  0.0f, 1.0, 0.0f, 1.0f,      // 左上
                                                                  
        pos.x - width / 2, pos.y + height / 2, pos.z + depth / 2, pos.w, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0, 1.0f, 0.0f,      // 右上
        pos.x - width / 2, pos.y + height / 2, pos.z - depth / 2, pos.w, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0, 1.0f, 1.0f,      // 右下
        pos.x - width / 2, pos.y - height / 2, pos.z - depth / 2, pos.w, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0, 0.0f, 1.0f,      // 左下
        pos.x - width / 2, pos.y - height / 2, pos.z + depth / 2, pos.w, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0, 0.0f, 0.0f,      // 左上
                                                                  
        pos.x + width / 2, pos.y + height / 2, pos.z + depth / 2, pos.w, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0, 1.0f, 0.0f,      // 右上
        pos.x + width / 2, pos.y + height / 2, pos.z - depth / 2, pos.w, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0, 1.0f, 1.0f,      // 右下
        pos.x + width / 2, pos.y - height / 2, pos.z - depth / 2, pos.w, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0, 0.0f, 1.0f,      // 左下
        pos.x + width / 2, pos.y - height / 2, pos.z + depth / 2, pos.w, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0, 0.0f, 0.0f,      // 左上
                                                                  
        pos.x - width / 2, pos.y - height / 2, pos.z - depth / 2, pos.w, 0.0f,-1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0, 0.0f, 1.0f,      // 左下
        pos.x + width / 2, pos.y - height / 2, pos.z - depth / 2, pos.w, 0.0f,-1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0, 1.0f, 1.0f,      // 右下        
        pos.x + width / 2, pos.y - height / 2, pos.z + depth / 2, pos.w, 0.0f,-1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0, 1.0f, 0.0f,      // 右上
        pos.x - width / 2, pos.y - height / 2, pos.z + depth / 2, pos.w, 0.0f,-1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0, 0.0f, 0.0f,      // 左上
                                                                  
        pos.x - width / 2, pos.y + height / 2, pos.z - depth / 2, pos.w, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0, 0.0f, 1.0f,      // 左下
        pos.x + width / 2, pos.y + height / 2, pos.z - depth / 2, pos.w, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0, 1.0f, 1.0f,      // 右下
        pos.x + width / 2, pos.y + height / 2, pos.z + depth / 2, pos.w, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0, 1.0f, 0.0f,      // 右上
        pos.x - width / 2, pos.y + height / 2, pos.z + depth / 2, pos.w, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0, 0.0f, 0.0f,      // 左上
    };
    for (int i = 0, j = 0, l = 4 * 6; j < l; i += 13 , j++) {
        vertices[j].position = Vec4(cubeVertices[i], cubeVertices[i + 1], cubeVertices[i + 2], cubeVertices[i + 3]);
        vertices[j].normal = Vec3(cubeVertices[i + 4], cubeVertices[i + 5], cubeVertices[i + 6]);
        vertices[j].color = Vec4(cubeVertices[i + 7], cubeVertices[i + 8], cubeVertices[i + 9], cubeVertices[i + 10]);
        vertices[j].texcoord = Vec2(cubeVertices[i + 11], cubeVertices[i + 12]);
    }
    for (int m = 0, n = 0, t = 6 * 6; m < t; m += 6, n += 4) {
        index[m] = n;
        index[m + 1] = n + 1;
        index[m + 2] = n + 2;
        index[m + 3] = n + 2;
        index[m + 4] = n + 3;
        index[m + 5] = n;
    }

}

void Mesh::plane(double width, double height, int id, Vec4 pos) {

}