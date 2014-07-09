/* 
 * File:   Mesh.cpp
 * Author: Ruslanas
 * 
 * Created on 09 July 2014, 22:41
 */

#include "Mesh.h"
#include <iostream>

#define MAX_VERTICES 128

Mesh::Mesh() {
    // allocate heap space for MAX_VERTICES
    count = 0;
    vertices = (Vec3*)malloc(MAX_VERTICES * sizeof(Vec3));
}

Mesh::Mesh(const Mesh& orig) {
    count = orig.count;
    memcpy(vertices, orig.vertices, count * sizeof(Vec3));
}

Mesh::~Mesh() {
}

void Mesh::addVertex(const Vec3& vertex) {
    vertices[count] = vertex;
    count++;
}

void Mesh::addFace(const Vec3& v1, const Vec3& v2, const Vec3& v3) {
    addVertex(v1);
    addVertex(v2);
    addVertex(v3);
}

int Mesh::numVertices() const {
    return count;
}

void Mesh::print() {
    std::cout << "I'm the mesh!" << std::endl;
}