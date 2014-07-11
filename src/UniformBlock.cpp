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
    blockIdx = glGetUniformBlockIndex(program, name);
    glGetActiveUniformBlockiv(program, blockIdx, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);

    fprintf(stdout, "Block size: %d\n", blockSize);
    
    buff = malloc(blockSize);
    if (buff == NULL) {
        fprintf(stderr, "Unable to allocate buffer");
        exit(EXIT_FAILURE);
    }
}

UniformBlock::UniformBlock(const UniformBlock& orig) {
    end_ptr = 0;
    bindingPoint = orig.bindingPoint;
    blockIdx = orig.blockIdx;
    blockSize = orig.blockSize;

    buff = malloc(blockSize);
    if (buff == NULL) {
        fprintf(stderr, "Unable to allocate buffer");
        exit(EXIT_FAILURE);
    }
}

UniformBlock::~UniformBlock() {
}

void UniformBlock::append(Vec3& vec) {
    GLfloat data[3] = {(GLfloat)vec.x, (GLfloat)vec.y, (GLfloat)vec.z};
    size_t size = sizeof(data);
    memcpy((char*)buff + end_ptr, data, size);
    end_ptr += size;
    fprintf(stdout, "End pointer: %d\n", end_ptr);
}

void UniformBlock::append(Matrix4& mat) {
    GLfloat data[16];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i * 4 + j] = (GLfloat)mat(i, j);
        }
    }
    memcpy((char*)buff + end_ptr, data, sizeof(data));
    end_ptr += sizeof(data);
    fprintf(stdout, "End pointer: %d\n", end_ptr);
}

void UniformBlock::append(Matrix4 mat) {
    GLfloat data[16];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i * 4 + j] = (GLfloat)mat(i, j);
        }
    }
    memcpy((char*)buff + end_ptr, data, sizeof(data));
    end_ptr += sizeof(data);
    fprintf(stdout, "End pointer: %d\n", end_ptr);
}

void UniformBlock::transfere() {
    glUniformBlockBinding(program, blockIdx, bindingPoint);

    glGenBuffers(1, &buffName);
    glBindBuffer(GL_UNIFORM_BUFFER, buffName);

    glBufferData(GL_UNIFORM_BUFFER, blockSize, buff, GL_STREAM_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, buffName);
}
