/* 
 * File:   Matrix.h
 * Author: Ruslanas Balciunas <ruslanas.com@gmail.com>
 *
 * Created on 05 July 2014, 20:43
 */

#ifndef MATRIX_H
#define	MATRIX_H

#include <vector>

template <typename T> class Matrix {
private:
    std::vector<std::vector<T> > mat;
    unsigned rows;
    unsigned cols;

public:
    Matrix(unsigned _rows, unsigned _cols, const T& _initial);
    Matrix(const Matrix& orig);
    virtual ~Matrix();

    // operator overloading
    Matrix<T>& operator+=(const Matrix<T>& rhs);
    Matrix<T>& operator=(const Matrix<T>& rhs);
    Matrix<T> operator*(const Matrix<T>& rhs);

    // scalar operations
    std::vector<T> operator*(const std::vector<T>& rhs);

    T& operator()(const unsigned& row, const unsigned& col);
    const T& operator()(const unsigned& row, const unsigned& col) const;

    unsigned get_rows() const;
    unsigned get_cols() const;
};

// implementation

template<typename T>
Matrix<T>::Matrix(unsigned _rows, unsigned _cols, const T& _initial) {

    mat.resize(_rows);

    for (unsigned i = 0; i < mat.size(); i++) {
        mat[i].resize(_cols, _initial);
    }

    rows = _rows;
    cols = _cols;
}

// copy private members from original

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& orig) {
    mat = orig.mat;
    rows = orig.get_rows();
    cols = orig.get_cols();
}

template<typename T>
Matrix<T>::~Matrix() {
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs) {
    unsigned rows = rhs.get_rows();
    unsigned cols = rhs.get_cols();

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            this->mat[i][j] += rhs(i, j);
        }
    }
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs) {
    // check if not assigned to itself
    if (&rhs == this) {
        return *this;
    }

    unsigned new_rows = rhs.get_rows();
    unsigned new_cols = rhs.get_cols();

    mat.resize(new_rows);
    for (unsigned i = 0; i < mat.size(); i++) {
        mat[i].size(new_cols);
    }

    for (unsigned i = 0; i < new_rows; i++) {
        for (unsigned j = 0; j < new_cols; j++) {
            mat[i][j] = rhs(i, j);
        }
    }

    rows = new_rows;
    cols = new_cols;

    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs) {


    Matrix result(this->get_rows(), rhs.get_cols(), 0.0);
    
    for (unsigned i = 0; i < this->get_rows(); i++) {
        for (unsigned j = 0; j < rhs.get_cols(); j++) {
            for (unsigned k = 0; k < rhs.get_rows(); k++) {
                result(i, j) += rhs(k, j) * this->mat[i][k];
            }
        }
    }

    return result;
}

template<typename T>
std::vector<T> Matrix<T>::operator*(const std::vector<T>& rhs) {
    std::vector<T> result(rhs.size(), 0.0);
    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; i++) {
            result[i] = this->mat[i][j] * rhs[j];
        }
    }
    return result;
}

// Access individual elements

template<typename T>
T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) {
    return this->mat[row][col];
}

template<typename T>
const T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) const {
    return this->mat[row][col];
}

template<typename T>
unsigned Matrix<T>::get_rows() const {
    return this->rows;
}

template<typename T>
unsigned Matrix<T>::get_cols() const {
    return this->cols;
}

#endif	/* MATRIX_H */

