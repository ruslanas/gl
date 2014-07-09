/* 
 * File:   Box.cpp
 * Author: Ruslanas
 * 
 * Created on 08 July 2014, 17:03
 */

#include "Box.h"
#include "Vec3.h"

#define NUM_VERTICES 18

Box::Box(double _length, double _width, double _depth) {
    width = _width;
    length = _length;
    depth = _depth;
    numVertices = NUM_VERTICES;
    vertices = (Vec3*)malloc(sizeof(Vec3) * numVertices);
    
    double hw = width / 2.0;
    Vec3 vrtc[NUM_VERTICES] = {
        Vec3(-hw, -hw, -hw),
        Vec3(hw, hw, -hw),
        Vec3(-hw, hw, -hw),

        Vec3(-hw, -hw, -hw),
        Vec3(hw, -hw, -hw),
        Vec3(hw, hw, -hw),
                
        Vec3(-hw, -hw, hw),
        Vec3(hw, hw, hw),
        Vec3(-hw, hw, hw),

        Vec3(-hw, -hw, hw),
        Vec3(hw, -hw, hw),
        Vec3(hw, hw, hw),
        
        Vec3(-hw, -hw, -hw),
        Vec3(hw, -hw, -hw),
        Vec3(hw, -hw, hw),

        Vec3(-hw, -hw, -hw),
        Vec3(-hw, -hw, -hw),
        Vec3(-hw, -hw, hw),
    };
    // copy to class member
    for(int i=0;i<numVertices;i++) {
        vertices[i] = vrtc[i];
    }
}

Box::Box(const Box& orig) {
}

Box::~Box() {
}

// this method is a stub
void Box::loadNormals(GLfloat* arr) {
    Vec3* normals = (Vec3*)malloc(sizeof(Vec3) * numVertices);
    
    // calculate cross product (normals)
    for (int i = 0; i < numVertices; i++) {
        normals[i] = (vertices[i] - vertices[i+1]) ^ (vertices[i] - vertices[i+2]);
    }
    
    for(int i=0;i<numVertices;i++) {
        Vec3 normal = normals[i];
        
        arr[i*3] = normal.x;
        arr[i*3 + 1] = normal.y;
        arr[i*3 + 2] = normal.z;
    }
}


void Box::loadVertices(GLfloat* arr) {

    // half width
    for (int i = 0; i < numVertices; i++) {
        arr[i*3] = vertices[i].x;
        arr[i*3 + 1] = vertices[i].y;
        arr[i*3 + 2] = vertices[i].z;
    }
}