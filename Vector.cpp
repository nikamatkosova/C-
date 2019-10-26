#include "Vector.h"
#include "Matrix.h"
#include<cmath>

using namespace mat_vec;
using namespace std;

Vector::Vector(size_t size, double value) {
    vSize = size;
    vArray = new double[vSize];

    for(size_t i = 0; i < vSize; ++i){
        vArray[i] = value;
    }
}

Vector::Vector(const Vector &src){
    vSize = src.vSize;
    vArray = new double[vSize];

    for(size_t i = 0; i < vSize; ++i){
        vArray[i] = src.vArray[i];
    }
}

Vector::~Vector(){
    delete[] vArray;
}

Vector &Vector::operator=(const Vector &rhs){
    for(size_t i = 0; i < this->vSize; ++i){
        this->vArray[i] = rhs.vArray[i];
    }

    return *this;
}

size_t Vector::size() const{
    return this->vSize;
}

double Vector::norm() const{
    double l2 = 0;
    for(size_t i = 0; i < this->vSize; ++i){
        l2 += pow(this->vArray[i], 2);
    }

    return sqrt(l2);
}

Vector Vector::operator+(const Vector &rhs) const{
    Vector res = Vector(this->vSize);

    for(size_t i = 0; i < this->vSize; ++i){
        res.vArray[i] = this->vArray[i] + rhs.vArray[i];
    }

    return res;
}

Vector &Vector::operator+=(const Vector &rhs){
    for(size_t i = 0; i < this->vSize; ++i){
        this->vArray[i] += rhs.vArray[i];
    }

    return *this;
}


Vector Vector::operator-(const Vector &rhs) const{
    Vector res = Vector(this->vSize);

    for(size_t i = 0; i < this->vSize; ++i){
        res.vArray[i] = this->vArray[i] - rhs.vArray[i];
    }

    return res;
}

Vector &Vector::operator-=(const Vector &rhs){
    for(size_t i = 0; i < this->vSize; ++i){
        this->vArray[i] -= rhs.vArray[i];
    }

    return *this;
}

Vector Vector::operator^(const Vector &rhs) const{
    Vector res = Vector(this->vSize);

    for(size_t i = 0; i < this->vSize; ++i){
        res.vArray[i] = this->vArray[i] * rhs.vArray[i];
    }

    return res;
}

Vector &Vector::operator^=(const Vector &rhs){
    for(size_t i = 0; i < this->vSize; ++i){
        this->vArray[i] *= rhs.vArray[i];
    }

    return *this;
}

double Vector::operator*(const Vector &rhs) const{
    double count = 0;

    for(size_t i = 0; i < this->vSize; ++i){
        count += this->vArray[i] * rhs.vArray[i];
    }
    return count;
}

Vector Vector::operator*(double k) const{
    Vector res = Vector(this->vSize);

    for(size_t i = 0; i < this->vSize; ++i){
        res.vArray[i] = this->vArray[i] * k;
    }

    return res;
}

Vector mat_vec::operator*(double k, const Vector &v){
    return v * k;
}

Vector &Vector::operator*=(double k){
    for(size_t i = 0; i < this->vSize; ++i){
        this->vArray[i] *= k;
    }

    return *this;
}

Vector Vector::operator/(double k) const{
    Vector res = Vector(this->vSize);

    for(size_t i = 0; i < this->vSize; ++i){
        res.vArray[i] = this->vArray[i] / k;
    }

    return res;
}

Vector &Vector::operator/=(double k){
    for(size_t i = 0; i < this->vSize; ++i){
        this->vArray[i] /= k;
    }

    return *this;
}

bool Vector::operator==(const Vector &rhs) const{
    if(rhs.vSize != this->vSize){
        return false;
    }

    for(size_t i = 0; i < this->vSize; ++i){
        if(this->vArray[i] != rhs.vArray[i]){
            return false;
        }
    }

    return true;

}

bool Vector::operator!=(const Vector &rhs) const{
    if(rhs.vSize != this->vSize){
        return false;
    }

    for(size_t i = 0; i < this->vSize; ++i){
        if(this->vArray[i] != rhs.vArray[i]){
            return true;
        }
    }

    return false;
}

Vector Vector::normalized() const{
    Vector res = Vector(this->vSize);
    double L2 = norm();

    for(size_t i = 0; i < this->vSize; ++i) {
        res.vArray[i] = this->vArray[i] / L2;
    }

    return res;
}

void Vector::normalize(){
    double L2 = norm();

    for(size_t i = 0; i < this->vSize; ++i) {
        this->vArray[i] /= L2;
    }
}

double Vector::operator[](size_t n) const{
    return this->vArray[n];
}

double &Vector::operator[](size_t n){
    return this->vArray[n];
}

Vector Vector::operator*(const Matrix &mat) const{
    Vector res = Vector(this->vSize);

    std::pair<size_t, size_t> mPair = mat.shape();

    for(size_t i = 0; i < mPair.first; ++i){
        for(size_t j = 0; j < this->vSize; ++j){
            res.vArray[i] += mat.get(i, j) * this->vArray[j];
        }
    }

    return res;
}

Vector &Vector::operator*=(const Matrix &mat) {
    Vector res = Vector(this->vSize);
    res = *this * mat;

    for(size_t i = 0; i < res.vSize; ++i){
       this->vArray[i] = res.vArray[i];
    }

    return *this;
}