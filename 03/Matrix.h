#ifndef Matrix_H
#define Matrix_H 
#include <iostream>
#include <functional>
#include <sstream>
#include <string.h>
#include <cassert>
using namespace std;
class proxy {
    int *row;
    size_t size;
public:
    proxy(int *a, size_t size) : row(a), size(size) {};
    int &operator[](size_t j) {
        if(j >= size) {
            throw std::out_of_range("Your column number is incorrect");
        }
        return row[j];
    }
};
class Matrix {
    int **a;
    size_t rows, columns;
public:
    Matrix(const size_t rows, const size_t columns): rows(rows), columns(columns) {
        a = new int* [rows];
        for(size_t i = 0; i < rows; ++i) {
            a[i] = new int [columns];
        }
    };
    Matrix(const Matrix &cop): rows(cop.rows), columns(cop.columns) {
        a = new int* [rows];
        for(size_t i = 0; i < rows; ++i) {
            a[i] = new int [columns];
        }
        for(size_t i = 0; i < rows; ++i) {
            for(size_t j = 0; j < columns; ++j) {
                a[i][j] = cop[i][j];
            }
        }
    }
    Matrix &operator=(const Matrix& right) {
        this->~Matrix();
        rows = right.rows;
        columns = right.columns;
        a = new int* [rows];
        for(size_t i = 0; i < rows; ++i) {
            a[i] = new int [columns];
        }
        for(size_t i = 0; i < rows; ++i) {
            for(size_t j = 0; j < columns; ++j) {
                a[i][j] = right[i][j];
            }
        }
        return *this;
    }
    proxy operator[] (const size_t i) const {
        if(i >= rows) {
            throw std::out_of_range("Your row number is incorrect");
        }
        return proxy(a[i], columns);
    }
    size_t getRows() const {
        return rows;
    }
    size_t getColumns() const {
        return columns;
    }
    Matrix &operator+=(const Matrix &right) {
        size_t rows = min(this->rows, right.getRows());
        size_t columns = min(this->columns, right.getColumns());
        for(size_t i = 0; i < rows; ++i) {
            for(size_t j = 0; j < columns; ++j) {
                a[i][j] += right[i][j];
            }
        }
        return *this;
    }
    Matrix &operator*=(const int &right) {
        for(size_t i = 0; i < rows; ++i) {
            for(size_t j = 0; j < columns; ++j) {
                a[i][j] *= right;
            }
        }
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Matrix& obj);
    Matrix operator+(const Matrix &right) {
        size_t rows = min(rows, right.getRows());
        size_t columns = min(columns, right.getColumns());
        Matrix res(rows, columns);
        for(size_t i = 0; i < rows; ++i) {
            for(size_t j = 0; j < columns; ++j) {
                res[i][j] = a[i][j] + right[i][j];
            }
        }
        return res;
    }
    bool operator==(const Matrix &right) {
        if(rows != right.rows || columns != right.columns) {
            return false;
        }
        for(size_t i = 0; i < rows; ++i) {
            for(size_t j = 0; j < right.rows; ++j) {
                if(a[i][j] != right[i][j]) {
                    return false;
                }
            } 
        }
        return true;
    }
    bool operator!=(const Matrix &right) {
        return !(*this == right);
    }
    ~Matrix() {
        for(size_t i = 0; i < rows; ++i) {
            delete [] a[i];
        }
        delete [] a;
    }
};
std::ostream& operator<<(std::ostream& os, const Matrix& a)
{
    for(size_t i = 0; i < a.rows; ++i) {
        for(size_t j = 0; j < a.columns; ++j) {
            os << a[i][j] << " ";        
        }
        cout << std::endl;
    }
    return os;
}

#endif