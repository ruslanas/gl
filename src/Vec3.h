/* 
 * File:   Vec3.h
 * Author: Ruslanas
 *
 * Created on 06 July 2014, 15:04
 */

#ifndef VEC3_H
#define	VEC3_H

#include "Matrix4.h"

#include <math.h>
#include <string>
#include <cstdio>
#include <cstdlib>

class Vec3 {
public:
    double x;
    double y;
    double z;

    Vec3(double _x, double _y, double _z);
    Vec3(const Vec3& orig);
    virtual ~Vec3();

    Vec3 applyMatrix(const Matrix4& mat);
    // typecast operator
    operator const double*();
    
    // cross product
    Vec3 operator^(const Vec3& rhs);
    Vec3 operator-(const Vec3& rhs) const;
    double length();

private:
};

#endif	/* VEC3_H */

