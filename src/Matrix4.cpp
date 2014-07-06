/* 
 * File:   Matrix4.cpp
 * Author: Ruslanas
 * 
 * Transformation matrix. Replacement for generic Matrix template class.
 * 
 * Created on 06 July 2014, 09:36
 */

#include "Matrix4.h"
#include <cstring>

Matrix4::Matrix4() {
    init(0.0);
}
Matrix4::Matrix4(double _initial) {
    init(_initial);
}
Matrix4::Matrix4(const Matrix4& orig) {
    size_t size = cols * rows * sizeof (double);
    memcpy(this->mat, orig.mat, size);
}

Matrix4::~Matrix4() {
}

void Matrix4::init(double _initial) {
    rows = 4;
    cols = 4;
    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            this->mat[i][j] = _initial;
        }
    }
}

Matrix4 Matrix4::operator*(const Matrix4& rhs) {
    
    Matrix4 result;

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            for (unsigned k = 0; k < rows; k++) {
                result(i, j) += rhs(k, j) * this->mat[i][k];
            }
        }
    }

    return result;
}

double& Matrix4::operator()(const unsigned row, const unsigned col) {
    return this->mat[row][col];
}
const double& Matrix4::operator()(const unsigned row, const unsigned col) const {
    return this->mat[row][col];
}

Matrix4& Matrix4::operator+=(const Matrix4& rhs) {
    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            this->mat[i][j] += rhs(i, j);
        }
    }
}

Matrix4& Matrix4::operator=(const Matrix4& rhs) {
    size_t size = cols * rows * sizeof (double);
    memcpy(this->mat, rhs.mat, size);
    return *this;
}