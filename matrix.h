/*
Есть недоработки:
Нет класса обертки для каждой сроки матрицы для отслеживания выхода за пределы массива
Нет исключений
Нет семантики перемещения
*/

#pragma once

#include <initializer_list>

class Matrix {
    public:
        int n, m;

    protected:
        int     b_length;
        float*  buffer;

    public:
        Matrix(const Matrix& matrix);
        Matrix(int n, int m);
        Matrix(int n, int m, std::initializer_list<float> src);

        void    copy(const Matrix& matrix);
        float&  at(int i, int j);

        bool    add(const Matrix& matrix);
        bool    scalar(float s);
        Matrix  mul(const Matrix& matrix) const;
        Matrix  transpose() const;
        
        Matrix& operator=(const Matrix& matrix);
        float*  operator[](int index);

        friend Matrix operator+(const Matrix& left, const Matrix& right);
        friend Matrix operator-(const Matrix& left, const Matrix& right);
        friend Matrix operator*(const Matrix& left, const Matrix& right);
        friend Matrix operator*(const Matrix& left, float right);
        friend Matrix operator*(float left, const Matrix& right);

        friend Matrix operator-(const Matrix& matrix);
        
        ~Matrix();
};
