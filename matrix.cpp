#include "matrix.h"

Matrix::Matrix(int n, int m) {
    this->n = n;
    this->m = m;

    b_length = n * m;
    buffer = new float[b_length];
}

Matrix::Matrix(const Matrix& matrix) {
    copy(matrix);
}

Matrix::Matrix(
    int n, int m,
    std::initializer_list<float> src
) : Matrix(n, m) {
    int i = 0;

    for (auto &e : src)
		buffer[i++] = e;
}

void Matrix::copy(const Matrix& matrix) {
    n = matrix.n;
    m = matrix.m;

    b_length = n * m;
    delete buffer;
    buffer = new float[b_length];

    float* src = matrix.buffer;
    for (int i = 0; i < this->b_length; i++)
        buffer[i] = src[i];
}

float& Matrix::at(int i, int j) {
    return buffer[i * m + j];
}

bool Matrix::add(const Matrix& matrix) {
    if ((matrix.n ^ n) | (matrix.m ^ m))
        return false;

    for (int i = 0; i < b_length; i++)
        buffer[i] += matrix.buffer[i];
    
    return true;
}

bool Matrix::scalar(float s) {
    for (int i = 0; i < b_length; i++)
        buffer[i] *= s;
        
    return true;
}

Matrix Matrix::mul(const Matrix& matrix) const {
    if (this->m != matrix.n)
        return Matrix(0, 0);
    
    Matrix result(this->n, matrix.m);
    int n = result.n,
        m = result.m;

    float* A = this->buffer;
    float* B = matrix.buffer;
    float* C = result.buffer;
    
    for (int i = 0; i < n; i++) {
        float* c = C + i * m;
        for (int j = 0; j < m; j++)
            c[j] = 0;
        
        for (int r = 0; r < this->m; r++) {
            float* b = B + r * m;
            float a = A[r + i * this->m];

            for (int j = 0; j < m; j++)
                c[j] += a * b[j];
        }
    }

    return result;
}

Matrix Matrix::transpose() const {
    Matrix result(m, n);

    for (int i = 0; i < result.n; i++)
        for (int j = 0; j < result.m; j++)
            result.buffer[i*result.m + j] = buffer[j*m + i];
        
    return result;
}

Matrix& Matrix::operator=(const Matrix& matrix) {
    if (&matrix != this)
        copy(matrix);
    return *this;
}

float* Matrix::operator[](int index) {
    return buffer + index * this->m;
}

Matrix operator+(const Matrix& left, const Matrix& right) {
    Matrix result(left);

    if (result.add(right))
        return result;  

    return Matrix(0, 0);
}

Matrix operator-(const Matrix& left, const Matrix& right) {
    return -right + left;
}

Matrix operator*(const Matrix& left, const Matrix& right) {
    return left.mul(right);
}

Matrix operator*(const Matrix& left, float right) {
    Matrix result(left);
    result.scalar(right);

    return result;
}

Matrix operator*(float left, const Matrix& right) {
    return right * left;
}

Matrix operator-(const Matrix& matrix) {
    return -1 * matrix;
}

Matrix::~Matrix() {
    delete this->buffer;
}