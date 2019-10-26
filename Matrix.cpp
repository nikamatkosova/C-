#include <iostream>
#include <cmath>
#include "Matrix.h"
#include "Vector.h"

using namespace mat_vec;
using namespace std;

Matrix::Matrix(size_t size, double value){
    mArray = new double* [size];
    width = size;
    height = size;

    for(size_t i = 0; i < width; ++i){
        mArray[i] = new double[height];
    }
    for(size_t i = 0; i < width; ++i){
        for(size_t j = 0; j < height; ++j){
            mArray[i][j] = value;
        }
    }
}

Matrix::Matrix(size_t rows, size_t cols, double value){
    width = rows;
    height = cols;
    mArray = new double* [width];

    for(size_t i = 0; i < width; ++i){
        mArray[i] = new double[height];
    }
    for(size_t i = 0; i < width; ++i){
        for(size_t j = 0; j < height; ++j){
            mArray[i][j] = value;
        }
    }
}

Matrix::Matrix(const Matrix &src){
    width = src.width;
    height = src.height;
    mArray = new double* [width];
    for(size_t i = 0; i < width; ++i){
        mArray[i] = new double[height];
    }

    for(size_t i = 0; i < width; ++i){
        for(size_t j = 0; j < height; ++j){
            mArray[i][j] = src.mArray[i][j];
        }
    }

}

Matrix Matrix::eye(size_t size){
    Matrix res = Matrix(size);

    for(size_t i = 0; i < size; ++i){
        for(size_t j = 0; j < size; ++j){
            if(i == j)
                res.mArray[i][j] = 1;
            else
                res.mArray[i][j] = 0;
        }
    }

    return(res);
}

Matrix::~Matrix(){
    for(size_t i = 0; i < width; ++i){
        delete[] mArray[i];
    }
    delete[] mArray;
}

double Matrix::get(size_t row, size_t col) const{
    return(mArray[row][col]);
}

Matrix Matrix::operator+(const Matrix &rhs) const{
    Matrix res = Matrix(rhs.width, rhs.height);

    for(size_t i = 0; i < rhs.width; ++i) {
        for (size_t j = 0; j < rhs.height; ++j) {
            res.mArray[i][j] = this->mArray[i][j] + rhs.mArray[i][j];
        }
    }
     return res;
}

Matrix &Matrix::operator+=(const Matrix &rhs){
    for(size_t i = 0; i < rhs.width; ++i) {
        for (size_t j = 0; j < rhs.height; ++j) {
            this->mArray[i][j] += rhs.mArray[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator-(const Matrix &rhs) const{
    Matrix res = Matrix(rhs.width, rhs.height);

    for(size_t i = 0; i < rhs.width; ++i) {
        for (size_t j = 0; j < rhs.height; ++j) {
            res.mArray[i][j] = this->mArray[i][j] - rhs.mArray[i][j];
        }
    }
    return res;
}

Matrix &Matrix::operator-=(const Matrix &rhs){
    for(size_t i = 0; i < rhs.width; ++i) {
        for (size_t j = 0; j < rhs.height; ++j) {
            this->mArray[i][j] -= rhs.mArray[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix &rhs) const{
    Matrix res = Matrix(this->width, rhs.height);

    for(size_t i = 0; i < this->width; ++i) {
        for (size_t j = 0; j < rhs.height; ++j) {
            for(size_t k = 0; k < rhs.width; ++k) {
                res.mArray[i][j] += this->mArray[i][k] * rhs.mArray[k][j];
            }
        }
    }
    return res;
}

Matrix &Matrix::operator*=(const Matrix &rhs){
    Matrix res = *this * rhs;
    this->width = res.width;
    this->height = res.height;

    for(size_t i = 0; i < res.width; ++i){
        for (size_t j = 0; j < res.height; ++j) {
            this->mArray[i][j] = res.mArray[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator*(double k) const{
    Matrix res = Matrix(this->width, this->height);

    for(size_t i = 0; i < this->width; ++i) {
        for (size_t j = 0; j < this->height; ++j) {
            res.mArray[i][j] = this->mArray[i][j]  * k;
        }
    }

    return res;
}

Matrix &Matrix::operator*=(double k){
    for(size_t i = 0; i < this->width; ++i) {
        for (size_t j = 0; j < this->height; ++j) {
            this->mArray[i][j]  *= k;
        }
    }
    return *this;
}

Matrix Matrix::operator/(double k) const{
    Matrix res = Matrix(this->width, this->height);

    for(size_t i = 0; i < this->width; ++i) {
        for (size_t j = 0; j < this->height; ++j) {
            res.mArray[i][j] = this->mArray[i][j] / k;
        }
    }

    return res;
}

Matrix &Matrix::operator/=(double k){
    for(size_t i = 0; i < this->width; ++i) {
        for (size_t j = 0; j < this->height; ++j) {
            this->mArray[i][j] /= k;
        }
    }

    return *this;
}

Matrix &Matrix::operator=(const Matrix &rhs){
    for(size_t i = 0; i < this->width; ++i) {
        for (size_t j = 0; j < this->height; ++j) {
            this->mArray[i][j] = rhs.mArray[i][j];
        }
    }
    return *this;
}

void Matrix::reshape(size_t rows, size_t cols){
    Matrix res = Matrix(rows, cols);

    size_t k = 0;
    size_t t = 0;

    for(size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            res.mArray[i][j] = this->mArray[k][t];
            t += 1;
            if(t == this->height){
                k += 1;
                t = 0;
            }

        }
    }

    this->width = rows;
    this->height = cols;

    for(size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            this->mArray[i][j] = res.mArray[i][j];
        }
    }


}

std::pair<size_t, size_t> Matrix::shape() const{
    return make_pair(this->width, this->height);
}

Matrix Matrix::transposed() const{
    Matrix res = Matrix(this->width, this->height);

    double count = res.height;
    res.height = res.width;
    res.width = count;

    for(size_t i = 0; i < res.width; ++i) {
        for (size_t j = 0; j < res.height; ++j) {
            res.mArray[i][j] = this->mArray[j][i];
        }
    }
    return res;
}

void Matrix::transpose(){
    double count = this->height;
    this->height = this->width;
    this->width = count;

    for(size_t i = 0; i < this->width; ++i) {
        for (size_t j = 0; j < this->height; ++j) {
            this->mArray[i][j] = this->mArray[j][i];
        }
    }
}

double Matrix::det() const{
    double d = 0;
    if(this->width == 2){
        return this->mArray[0][0] * this->mArray[1][1] - this->mArray[0][1] * this->mArray[1][0];
    }
    else {
        size_t row_y = 0;
        size_t col_x = 0;
        Matrix array(this->width - 1);
        for (size_t i = 0; i < this->width; ++i) {
            for (size_t row = 0; row < this->width; ++row) {
                if (row != 0) {
                    row_y = row;
                    if (row > 0)
                        row_y -= 1;
                    for (size_t col = 0; col < this->width; ++col) {
                        if (col != i) {
                            col_x = col;
                            if (col > i)
                                col_x -= 1;
                            array.mArray[row_y][col_x] = this->mArray[row][col];
                        }
                    }
                }
            }
            d += pow(-1, i) * this->mArray[0][i] * array.det();
        }

        return d;
    }
}

Matrix Matrix::inv() const{
    return this->transposed() * (1 / this->det());
}

bool Matrix::operator==(const Matrix &rhs) const{
    if((rhs.width != this->width) or (rhs.height != this->height)){
        return false;
    }

    for(size_t i = 0; i < rhs.width; ++i) {
        for (size_t j = 0; j < rhs.height; ++j) {
            if(rhs.mArray[i][j] != this->mArray[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &rhs) const{
    if((rhs.width != this->width) or (rhs.height != this->height)){
        return false;
    }

    for(size_t i = 0; i < rhs.width; ++i) {
        for (size_t j = 0; j < rhs.height; ++j) {
            if(rhs.mArray[i][j] != this->mArray[i][j]) {
                return true;
            }
        }
    }
    return false;
}

Vector Matrix::operator*(const Vector &vec) const{
    Vector res = Vector(vec.size());

    for(size_t i = 0; i < this->width; ++i){
        for(size_t j = 0; j < vec.size(); ++j){
            res[i] += this->mArray[i][j] * vec[j];
        }
    }

    return res;
}