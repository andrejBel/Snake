/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Matrix.h
 * Author: andrej
 *
 * Created on November 3, 2017, 7:50 PM
 */

#ifndef MATRIX_H
#define MATRIX_H
#include <exception>
#include <iostream>

template<typename T>
class Matrix {
private:

    unsigned int rows_;
    unsigned int columns_;
    T** matrix_;

public:

    Matrix(unsigned int rows, unsigned int columns) :
    rows_(rows),
    columns_(columns),
    matrix_(new T*[rows_]) 
    {
        for (int i = 0; i < rows_; i++) {
            matrix_[i] = new T[columns_];
        }
    }

    Matrix(unsigned int rows, unsigned int columns, const T& fill) :
    Matrix(rows, columns) 
    {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < columns_; j++) {
                matrix_[i][j] = fill;
            }
        }
    }


    Matrix(const Matrix& metrix) = delete;
    Matrix& operator=(const Matrix& metrix) = delete;

    ~Matrix() 
    {
        for (int i = 0; i < rows_; i++) {
            delete[] matrix_[i];
        }
        delete[] matrix_;
    }

    const T& operator()(int row, int column) const
    {
        if (row < 0 || row >= rows_ || column < 0 || column >= columns_) {
            throw std::runtime_error("Index out of range");
        }
        return matrix_[row][column];
    };

    T& operator()(int row, int column) 
    {
        if (row < 0 || row >= rows_ || column < 0 || column >= columns_) {
            throw std::runtime_error("Index out of range");
        }
        return matrix_[row][column];
    };

    unsigned int getRows() const
    {
        return rows_;
    }

    unsigned int getColumns() const 
    {
        return columns_;
    }

    void print()
    {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < columns_; j++) {
                if (matrix_[i][j] == '*' || matrix_[i][j] == 'B') 
                {
                std::cout << matrix_[i][j] << " ";
                } else 
                {
                    std::cout << +matrix_[i][j] << " ";
                }
                
            }
            std::cout << std::endl;
        }
    }

};

#endif /* MATRIX_H */

