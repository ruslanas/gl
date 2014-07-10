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
    
    // half width
    
    Vec3 v1 = Vec3(0, 0, 0);
    Vec3 v2 = Vec3(0, width, 0);
    Vec3 v3 = Vec3(length, width, 0);
    Vec3 v4 = Vec3(length, 0, 0);
    Vec3 v5 = Vec3(length, 0, depth);
    Vec3 v6 = Vec3(0, 0, depth);
    Vec3 v7 = Vec3(0, width, depth);
    Vec3 v8 = Vec3(length, width, depth);
    
    addFace(v1, v2, v3);
    addFace(v1, v3, v4);
    addFace(v1, v6, v7);
    addFace(v1, v7, v2);
    addFace(v2, v7, v8);
    addFace(v2, v8, v3);
    
    addFace(v6, v7, v8);
    addFace(v5, v6, v8);
    addFace(v1, v6, v5);
    addFace(v1, v5, v4);
    addFace(v4, v5, v8);
    addFace(v4, v8, v3);

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
