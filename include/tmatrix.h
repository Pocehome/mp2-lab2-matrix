// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector {
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector() noexcept {
        sz = 1;
        pMem = new T[sz](); // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(size_t size) {
        sz = size;
        if (this->sz > MAX_VECTOR_SIZE) {
            throw out_of_range("Vector size should be less than 100000000");
        }
        if (sz == 0) {
            throw out_of_range("Vector size should be greater than zero");
        }
        pMem = new T[sz](); // У типа T д.б. констуктор по умолчанию
        /*for (size_t i = 0; i < size; i++) {
            pMem[i] = 0;
        }*/
    }
    TDynamicVector(T* arr, size_t s) : sz(s) {
        if (arr == nullptr) {
            throw("TDynamicVector ctor requires non-nullptr arg");
        }
        if (this->sz > MAX_VECTOR_SIZE) {
            throw out_of_range("Vector size should be less than 100000000");
        }
        this->pMem = new T[sz];
        for (size_t i = 0; i < this->sz; i++) {
            this->pMem[i] = arr[i];
        }
        //std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v) {
        this->sz = v.sz;
        this->pMem = new T[v.sz];
        for (size_t i = 0; i < v.sz; i++) {
            this->pMem[i] = v.pMem[i];
        }
    }
    //TDynamicVector(TDynamicVector&& v) noexcept {}
    ~TDynamicVector() {
        delete[] this->pMem;
    }

    TDynamicVector& operator=(const TDynamicVector& v) {
        if (this->pMem != v.pMem) {
            if (this->sz != v.sz) {
                delete[] this->pMem;
                this->sz = v.sz;
                this->pMem = new T[v.sz];
            }
            for (size_t i = 0; i < v.sz; i++) {
                this->pMem[i] = v.pMem[i];
            }
        }

        return *this;
    }
    //TDynamicVector& operator=(TDynamicVector&& v) noexcept {}

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind) {
        return this->pMem[ind];
    }
    const T& operator[](size_t ind) const {
        return this->pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind) {
        if (ind >= this->sz) {
            throw out_of_range("Too much index");
        }
        return this->pMem[ind];
    }

    const T& at(size_t ind) const {
        if (ind >= this->sz) {
            throw out_of_range("Too much index");
        }
        return this->pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept {
        if (this->sz != v.sz) {
            return false;
        }
        for (size_t i = 0; i < this->sz; i++) {
            if (this->pMem[i] != v.pMem[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept {
        if (this->sz != v.sz) {
            return true;
        }
        for (size_t i = 0; i < this->sz; i++) {
            if (this->pMem[i] != v.pMem[i]) {
                return true;
            }
        }
        return false;
    }

    // скалярные операции
    TDynamicVector operator+(T val) {
        TDynamicVector res(*this);
        for (size_t i = 0; i < this->sz; i++) {
            res.pMem[i] += val;
        }
        return res;
    }
    TDynamicVector operator-(T val) {
        TDynamicVector res(*this);
        for (size_t i = 0; i < this->sz; i++) {
            res.pMem[i] -= val;
        }
        return res;
    }
    TDynamicVector operator*(T val) {
        TDynamicVector res(*this);
        for (size_t i = 0; i < this->sz; i++) {
            res.pMem[i] *= val;
        }
        return res;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v) {
        if (this->sz != v.size()) {
            throw("Two vectors should have equal dimensions");
        }
        TDynamicVector res(*this);
        for (size_t i = 0; i < this->sz; i++) {
            res.pMem[i] += v.pMem[i];
        }
        return res;
    }
    TDynamicVector operator-(const TDynamicVector& v) {
        if (this->sz != v.size()) {
            throw("Two vectors should have equal dimensions");
        }
        TDynamicVector res(*this);
        for (size_t i = 0; i < this->sz; i++) {
            res.pMem[i] -= v.pMem[i];
        }
        return res;
    }
    T operator*(const TDynamicVector& v) {
        if (this->sz != v.sz) {
            throw std::length_error("Two vectors should have equal dimensions");
        }
        T res = 0;
        for (size_t i = 0; i < this->sz; i++) {
            res += this->pMem[i] * v.pMem[i];
        }
        return res;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v) {
        for (size_t i = 0; i < v.sz; i++) {
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        }
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v) {
        for (size_t i = 0; i < v.sz; i++) {
            ostr << v.pMem[i] << "\t"; // требуется оператор<< для типа T
        }
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>> {
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) {
        this->sz = s;
        if (this->sz > MAX_MATRIX_SIZE) {
            throw out_of_range("Matrix size should be less than 10000");
        }
        if (sz == 0) {
            throw out_of_range("Matrix size should be greater than zero");
        }
        this->pMem = new TDynamicVector<T>[this->sz];
        for (size_t i = 0; i < sz; i++) {
            pMem[i] = TDynamicVector<T>(this->sz);
        }
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    /*TDynamicMatrix& operator=(const TDynamicMatrix& v) {
        if (this->pMem != v.pMem) {
            if (this->sz != v.sz) {
                delete[] this->pMem;
                this->sz = v.sz;
                this->pMem = new TDynamicVector<T>[this->sz];
            }
            for (size_t i = 0; i < sz; i++) {
                this->pMem[i] = v.pMem[i];
            }
        }

        return *this;
    }*/

    size_t size() const noexcept { return this->sz; }

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept {
        if (this->sz != m.sz) {
            return false;
        }
        for (size_t i = 0; i < this->sz; i++) {
            if ((*this)[i] != m[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator!= (const TDynamicMatrix& m) const noexcept {
        if (this->sz != m.sz) {
            return true;
        }
        for (size_t i = 0; i < this->sz; i++) {
            if ((*this)[i] != m[i]) {
                return true;
            }
        }
        return false;
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val) {
        TDynamicMatrix res(this->sz);
        for (size_t i = 0; i < this->sz; i++) {
            res[i] = this->pMem[i] * val;
        }
        return res;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v) {
        if (this->sz != v.size()) {
            throw("Matrix and vector should have equal dimensions");
        }
        TDynamicVector<T> res(this->sz);
        for (size_t i = 0; i < this->sz; i++) {
            res[i] = 0;
            for (size_t j = 0; j < this->sz; j++) {
                res[i] += (*this)[i][j] * v[j];
            }
        }
        return res;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m) {
        if (this->sz != m.size()) {
            throw("Two matrixs should have equal dimensions");
        }
        TDynamicMatrix res(this->sz);
        for (size_t i = 0; i < this->sz; i++) {
            res[i] = pMem[i] + m[i];
        }
        return res;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m) {
        if (this->sz != m.size()) {
            throw("Two matrixs should have equal dimensions");
        }
        TDynamicMatrix res(*this);
        for (size_t i = 0; i < this->sz; i++) {
            res[i] = this->pMem[i] - m[i];
        }
        return res;
    }

    TDynamicMatrix operator*(const TDynamicMatrix& m) {
        if (this->sz != m.size()) {
            throw("Two matrixs should have equal dimensions");
        }
        TDynamicMatrix res(this->sz);
        for (size_t i = 0; i < this->sz; i++) {
            for (size_t j = 0; j < this->sz; j++) {
                res[i][j] = 0;
                for (size_t k = 0; k < this->sz; k++) {
                    res[i][j] += this->pMem[i][k] * m[k][j];
                }
            }
        }
        return res;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& m) {
        for (size_t i = 0; i < m.sz; i++) {
            istr >> m[i]
        }
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m) {
        for (size_t i = 0; i < m.sz; i++) {
            ostr << m[i] << std::endl;
        }
        return ostr;
    }
};

#endif;
