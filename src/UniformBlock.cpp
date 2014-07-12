/* 
 * File:   UniformBlock.cpp
 * Author: Ruslanas
 * 
 * Created on 08 July 2014, 14:36
 */

#include "UniformBlock.h"
#include "Vec3.h"
#include <GL/glut.h>
#include <cstdio>
#include <iostream>

UniformBlock::UniformBlock() {
    end_ptr = 0;
    bindingPoint = 1;
    blockIdx = 0;
}

UniformBlock::UniformBlock(GLuint _program, char* _name)
: name(_name), program(_program) {
    end_ptr = 0;
    bindingPoint = 1;

    createBuffer();
}

void UniformBlock::createBuffer() {
    blockIdx = glGetUniformBlockIndex(program, name);
    glGetActiveUniformBlockiv(program, blockIdx, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);

    glGenBuffers(1, &buffName);
    glBindBuffer(GL_UNIFORM_BUFFER, buffName);
    glBufferData(GL_UNIFORM_BUFFER, blockSize, NULL, GL_STREAM_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    fprintf(stdout, "Buffer %d created of size %d bytes\n", buffName, blockSize);

}

UniformBlock::UniformBlock(const UniformBlock& orig) {
    end_ptr = 0;
    bindingPoint = orig.bindingPoint;
    blockIdx = orig.blockIdx;
    blockSize = orig.blockSize;
}

UniformBlock::~UniformBlock() {
}

void UniformBlock::writeBuffer(GLfloat* data, size_t size) {
    glBindBuffer(GL_UNIFORM_BUFFER, buffName);
    glBufferSubData(GL_UNIFORM_BUFFER, end_ptr, size, data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    fprintf(stdout, "%d bytes written to buffer %d starting from %d\n", size, buffName, end_ptr);
    
    end_ptr += size;
}

void UniformBlock::append(Vec3& vec) {
    // Warning: Implementations sometimes get the std140​ layout wrong for vec3​ components.
    GLfloat data[4] = {(GLfloat) vec.x, (GLfloat) vec.y, (GLfloat) vec.z, 1};
    writeBuffer(data, sizeof(data));
}

void UniformBlock::append(Matrix4& mat) {
    GLfloat data[16];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i * 4 + j] = (GLfloat) mat(i, j);
        }
    }
    writeBuffer(data, sizeof(data));
}

void UniformBlock::append(Matrix4 mat) {
    GLfloat data[16];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i * 4 + j] = (GLfloat) mat(i, j);
        }
    }
    writeBuffer(data, sizeof(data));
}

void UniformBlock::transfere() {
    glUniformBlockBinding(program, blockIdx, bindingPoint);
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, buffName);
}
