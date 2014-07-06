/* 
 * File:   Matrix4.h
 * Author: Ruslanas
 *
 * Created on 06 July 2014, 09:36
 */

#ifndef MATRIX4_H
#define	MATRIX4_H

class Matrix4 {
public:
    Matrix4();
    Matrix4(double _initial);
    Matrix4(const Matrix4& orig);
    virtual ~Matrix4();
    
    void init(double _initial);
    
    Matrix4 operator*(const Matrix4& rhs);
    
    double& operator()(const unsigned row, const unsigned col);
    const double& operator()(const unsigned row, const unsigned col) const;
    
    Matrix4& operator=(const Matrix4& rhs);
    Matrix4& operator+=(const Matrix4& rhs);
private:
    unsigned rows;
    unsigned cols;
    double mat[4][4];
};

#endif	/* MATRIX4_H */
