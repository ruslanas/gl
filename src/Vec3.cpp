/* 
 * File:   Vec3.cpp
 * Author: Ruslanas
 * 
 * Created on 06 July 2014, 15:04
 */

#include "Vec3.h"

Vec3::Vec3(double _x, double _y, double _z) {
    x = _x;
    y = _y;
    z = _z;
}

Vec3::Vec3(const Vec3& orig) {
    x = orig.x;
    y = orig.y;
    z = orig.z;
}

Vec3::~Vec3() {
}

Vec3 Vec3::applyMatrix(const Matrix4& mat) {

    double vec[] = {x, y, z, 1.0};
    double out[] = {0, 0, 0, 0};

    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            out[i] += mat(i, j) * vec[j];
        }
    }
    
    out[0] /= out[3];
    out[1] /= out[3];
    out[2] /= out[3];
    out[3] /= out[3];
    
    return Vec3(out[0], out[1], out[2]);
}

double Vec3::length() {
    return sqrt(x * x + y * y + z * z);
}

Vec3::operator const double*() {
    double* a = (double*) malloc(3);
    a[0] = x;
    a[1] = y;
    a[2] = z;
    return a;
}