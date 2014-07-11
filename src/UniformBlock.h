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
#include "Vec3.h"

class UniformBlock {
public:
    // default constructor
    UniformBlock();
    UniformBlock(GLuint _program, char* _name);
    UniformBlock(const UniformBlock& orig);
    virtual ~UniformBlock();
    
    void append(Vec3& vec);
    void append(Matrix4& mat);
    void transfere();
    
private:
    char* name;
    GLint blockSize;
    GLuint program, blockIdx, bindingPoint, buffName;
    GLvoid* buff;
    int end_ptr;
};

#endif	/* UNIFORMBLOCK_H */

