#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <functional>
#include <string>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iostream>

class Matrix {
private:
    static bool randomGeneratorInitialized;
    std::vector<std::vector<double>> data;
    int rows;
    int cols;

public:
    Matrix();
    Matrix(int i, int j);
    void maxNumI();
    void printJogoDaVelha();
    static Matrix vectorTomatriz(double* arr, int n);
    static Matrix applyFunction(Matrix& mat, std::function<double(double)> func);
    void applyFunction(std::function<double(double)> func);
    static Matrix scalarMultiply(const Matrix& mat, double scalar);
    static Matrix transpose(Matrix& mat);
    std::string toString();
    double getElement(int i, int j) const;
    void setElement(int i, int j, double val);
    static Matrix matrixFromVector(std::vector<double> aux);
    static void initializeRandomGenerator();
    void randomize();
    static Matrix hadamard(Matrix a, Matrix b);
    static Matrix add(const Matrix& a, const Matrix& b);
    static Matrix subtract(const Matrix& a, const Matrix& b);
    Matrix add(Matrix other) const;
    static Matrix multiply(const Matrix& a, const Matrix& b);
    void display();
};

double sigmoide(double a);
double dSigmoide(double a);

#endif // MATRIX_H
