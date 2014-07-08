/* 
 * File:   UniformBlock.h
 * Author: Ruslanas
 *
 * Created on 08 July 2014, 14:36
 */

#ifndef UNIFORMBLOCK_H
#define	UNIFORMBLOCK_H

#include <GL/glew.h>
#include "Matrix4.h"

class UniformBlock {
public:
    UniformBlock(GLuint _program, char* _name);
    UniformBlock(const UniformBlock& orig);
    virtual ~UniformBlock();
    
    void append(Matrix4& mat);
    
    
private:
    char* name;
    GLint blockSize;
    GLuint program, blockIdx, bindingPoint, buffName;
};

#endif	/* UNIFORMBLOCK_H */

