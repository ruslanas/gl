/* 
 * File:   Mesh.cpp
 * Author: Ruslanas
 * 
 * Created on 09 July 2014, 22:41
 */

#include "Mesh.h"
#include <iostream>

Mesh::Mesh() {
    count = 0; // number of vertices
    
}

// copy constructor
Mesh::Mesh(const Mesh& orig) {
    count = orig.count;
    size_t size = count * sizeof(GLfloat) * 3;
    // copy vertex data
    memcpy(vertexArray, orig.vertexArray, size);
    memcpy(normalArray, orig.normalArray, size);
}

Mesh::~Mesh() {
}

void Mesh::applyMatrix(const Matrix4& mat) {
    for(int i=0;i<count;i++) {
        vertexArray[i] = vertexArray[i].applyMatrix(mat);
    }
}

// load normals into GPU vertex array
void Mesh::loadNormals() const {

    size_t size = sizeof(GLfloat) * count * 4;
    GLfloat* normals = (GLfloat*)malloc(size);
    for(int i=0;i<count;i++) {
        normals[i * 4] = normalArray[i].x;
        normals[i * 4 + 1] = normalArray[i].y;
        normals[i * 4 + 2] = normalArray[i].z;
        normals[i * 4 + 3] = 1;
    }
    
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    
    glBufferData(GL_ARRAY_BUFFER, size, normals, GL_STATIC_DRAW);
    
    fprintf(stdout, "%d bytes uploaded to buffer %d\n", size, buffer);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    
}

// load vertex data into GPU vertex array
void Mesh::loadVertices() const {
    
    size_t size = sizeof(GLfloat) * count * 4;
    GLfloat* vertices = (GLfloat*)malloc(size);
    
    for(int i=0;i<count;i++) {
        vertices[i * 4] = vertexArray[i].x;
        vertices[i * 4 + 1] = vertexArray[i].y;
        vertices[i * 4 + 2] = vertexArray[i].z;
        vertices[i * 4 + 3] = 1;
    }
    
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    
    // allocate OpenGL server memory for storing data
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    
    fprintf(stdout, "%d bytes uploaded to buffer %d\n", size, buffer);
    
    // tell how to interpret data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

}

void Mesh::addVertex(const Vec3 vertex) {
    
    vertexArray[count] = vertex;
    count++;
}

void Mesh::addVertex(const Vec3 vertex, const Vec3 normal) {
    normalArray[count] = normal;
    addVertex(vertex);
}

void Mesh::addFace(const Vec3& v1, const Vec3& v2, const Vec3& v3) {
    // cross product
    Vec3 normal = (v1 - v2) ^ (v2 - v3);
    
    addVertex(v1, normal);
    addVertex(v2, normal);
    addVertex(v3, normal);
}

int Mesh::numVertices() const {
    return count;
}
