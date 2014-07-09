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

    // multiply matrices
    for (unsigned i = 0; i < 4; i++) {
        for (unsigned j = 0; j < 4; j++) {
            out[i] += mat(i, j) * vec[j];
        }
    }

    double w = out[3];
    // divide by w. Drop 4th component.
    out[0] /= w;
    out[1] /= w;
    out[2] /= w;

    return Vec3(out[0], out[1], out[2]);
}

double Vec3::length() {
    return sqrt(x * x + y * y + z * z);
}

// cross product

Vec3 Vec3::operator^(const Vec3& rhs) {
    return Vec3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
}

Vec3 Vec3::operator-(const Vec3& rhs) {
    return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vec3::operator const double*() {
    double* a = (double*) malloc(3);
    a[0] = x;
    a[1] = y;
    a[2] = z;
    return a;
}