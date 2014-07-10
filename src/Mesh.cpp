/* 
 * File:   Mesh.cpp
 * Author: Ruslanas
 * 
 * Created on 09 July 2014, 22:41
 */

#include <GL/glew.h>
#include "Mesh.h"
#include <iostream>

#define MAX_VERTICES 64
#define BUFFER_OFFSET(offset) ((void *)(offset))

Mesh::Mesh() {
    
    count = 0; // number of vertices
    
    // allocate memory for vertex and normal coordinates
    // arrays better idea for this matter
    vertices = (GLfloat*)malloc(MAX_VERTICES * sizeof(GLfloat) * 3);
    normals = (GLfloat*)malloc(MAX_VERTICES * sizeof(GLfloat) * 3);
}

// copy constructor
Mesh::Mesh(const Mesh& orig) {
    count = orig.count;
    // copy vertex data
    memcpy(vertices, orig.vertices, count * sizeof(GLfloat) * 3);
    memcpy(normals, orig.normals, count * sizeof(GLfloat) * 3);
}

Mesh::~Mesh() {
}

// load normals into GPU vertex array
void Mesh::loadNormals() const {

    std::cout << "Loading normals..." << std::endl;
    
    size_t size = sizeof(GLfloat) * numVertices() * 3;

    GLuint normalBuffer;
    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    
    glBufferData(GL_ARRAY_BUFFER, size, normals, GL_STATIC_DRAW);
    
    fprintf(stdout, "%d bytes uploaded to GPU memory\n", size);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    
}

// load vertex data into GPU vertex array
void Mesh::loadVertices() const {
    
    std::cout << "Loading vertices..." << std::endl;
    
    size_t size = sizeof(GLfloat) * count * 3;
    
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    
    fprintf(stdout, "Buffer bound: %d\n", buffer);

    // allocate OpenGL server memory for storing data
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    
    fprintf(stdout, "%d bytes uploaded to GPU memory\n", size);
    
    // tell how to interpret data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

}

void Mesh::addVertex(const Vec3& vertex) {
    vertices[count * 3] = vertex.x;
    vertices[count * 3 + 1] = vertex.y;
    vertices[count * 3 + 2] = vertex.z;
    
    count++;
}

void Mesh::addVertex(const Vec3& vertex, const Vec3& normal) {
    normals[count * 3] = normal.x;
    normals[count * 3 + 1] = normal.y;
    normals[count * 3 + 2] = normal.z;
    
    addVertex(vertex);
}

void Mesh::addFace(const Vec3& v1, const Vec3& v2, const Vec3& v3) {
    // cross product
    Vec3 normal = (v1 - v2) ^ (v1 - v3);
    
    addVertex(v1, normal);
    addVertex(v2, normal);
    addVertex(v3, normal);
}

int Mesh::numVertices() const {
    return count;
}
