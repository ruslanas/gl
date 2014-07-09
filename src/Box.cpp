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
    
    double hw = width / 2.0;
    
    addFace(Vec3(-hw, -hw, -hw), Vec3(hw, hw, -hw), Vec3(-hw, hw, -hw));
    addFace(Vec3(-hw, -hw, -hw), Vec3(hw, -hw, -hw), Vec3(hw, hw, -hw));
    addFace(Vec3(-hw, -hw, hw), Vec3(hw, hw, hw), Vec3(-hw, hw, hw));
    addFace(Vec3(-hw, -hw, hw), Vec3(hw, -hw, hw), Vec3(hw, hw, hw));
    addFace(Vec3(-hw, -hw, -hw), Vec3(hw, -hw, -hw), Vec3(hw, -hw, hw));
    addFace(Vec3(-hw, -hw, -hw), Vec3(-hw, -hw, -hw), Vec3(-hw, -hw, hw));
}

Box::Box(const Box& orig) : Mesh() {
    width = orig.width;
    length = orig.length;
    depth = orig.depth;
    count = orig.count;
    memcpy(vertices, orig.vertices, count * sizeof(Vec3));
}

Box::~Box() {
}

// this method is a stub
void Box::loadNormals(GLfloat* arr) {
    
    for(int i=0;i<numVertices();i++) {
        // calculate cross product
        Vec3 normal = (vertices[i] - vertices[i+1]) ^ (vertices[i] - vertices[i+2]);
        
        arr[i*3] = normal.x;
        arr[i*3 + 1] = normal.y;
        arr[i*3 + 2] = normal.z;
    }
}


void Box::loadVertices(GLfloat* arr) {

    // half width
    for (int i = 0; i < numVertices(); i++) {
        arr[i*3] = vertices[i].x;
        arr[i*3 + 1] = vertices[i].y;
        arr[i*3 + 2] = vertices[i].z;
    }
}