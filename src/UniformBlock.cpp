/* 
 * File:   UniformBlock.cpp
 * Author: Ruslanas
 * 
 * Created on 08 July 2014, 14:36
 */

#include "UniformBlock.h"
#include <GL/glut.h>
#include <cstdio>
#include <iostream>

UniformBlock::UniformBlock(GLuint _program, char* _name) : name(_name), program(_program) {
    bindingPoint = 1;
    blockIdx = glGetUniformBlockIndex(program, name);
}

UniformBlock::UniformBlock(const UniformBlock& orig) {
    
}

UniformBlock::~UniformBlock() {
}

void UniformBlock::append(Matrix4& mat) {
    GLvoid * buff;
    glGetActiveUniformBlockiv(program, blockIdx, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
    
    buff = malloc(blockSize);
    if(buff == NULL) {
        fprintf(stderr, "Unable to allocate buffer");
        exit(EXIT_FAILURE);
    }
    glUniformBlockBinding(program, blockIdx, bindingPoint);
    
    // copy
    GLfloat* model = (GLfloat *) malloc(16 * sizeof (GLfloat));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            model[i * 4 + j] = mat(i, j);
        }
    }
    
    memcpy(buff, model, blockSize);
    glGenBuffers(1, &buffName);
    glBindBuffer(GL_UNIFORM_BUFFER, buffName);
    
    glBufferData(GL_UNIFORM_BUFFER, blockSize, buff, GL_STREAM_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, buffName);
}