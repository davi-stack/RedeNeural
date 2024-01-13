#include <sstream>
#include "Matrix.hpp"
#include <vector>
#include <functional>
#include <string>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iostream>
using namespace std;
bool Matrix::randomGeneratorInitialized = false;

double sigmoide(double a) {
    return 1.0 / (1.0 + std::exp(-a));
}
double dSigmoide(double a){
    return a *(1 - a);
}
Matrix::Matrix(int i, int j) : rows(i), cols(j) {
        data.resize(i, std::vector<double>(j, 0.0));
        initializeRandomGenerator();
    }
// Apply a function to each element in the matrix
    Matrix Matrix::applyFunction(Matrix& mat, std::function<double(double)> func) {
        Matrix result(mat.rows, mat.cols);
        for (int i = 0; i < mat.rows; ++i) {
            for (int j = 0; j < mat.cols; ++j) {
                result.data[i][j] = func(mat.data[i][j]);
            }
        }
        return result;
    }


// Apply a function to each element in the matrix
    void Matrix::applyFunction(std::function<double(double)> func) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = func(data[i][j]);
            }
        }
    }

// Função para multiplicar uma matriz por um escalar e retornar uma nova matriz
   Matrix Matrix::scalarMultiply(const Matrix& mat, double scalar) {
        Matrix result = mat;  // Cria uma cópia de mat

        // Usando uma lambda function para multiplicar cada elemento pelo escalar
        applyFunction(result, [scalar](double value) { return value * scalar; });

        return result;  // Retorna a nova matriz resultante
    }
    //function to transpose matrix a
    Matrix Matrix::transpose(Matrix& mat) {
        Matrix transposed(mat.cols, mat.rows); // Nova matriz com dimensões invertidas

        for (int i = 0; i < mat.rows; ++i) {
            for (int j = 0; j < mat.cols; ++j) {
                transposed.data[j][i] = mat.data[i][j]; // Trocando linhas por colunas
            }
        }

        return transposed;
    }
    // Convert the matrix to a string for display
    string Matrix::toString() {
        std::ostringstream oss;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                oss << data[i][j] << " ";
            }
            oss << "\n";
        }
        return oss.str();
    }
    // Getter for a specific element
    double Matrix::getElement(int i, int j) const {
        return data[i][j];
    }
    // Setter for a specific element
    void Matrix::setElement(int i, int j, double val) {
        data[i][j] = val;
    }
    // Static function to create a matrix from a vector
    Matrix Matrix::matrixFromVector(vector<double> aux) {
        Matrix result(static_cast<int>(aux.size()), 1);
        for(int i = 0; i < aux.size(); i++) {
            result.data[i][0] = aux[i];
        }
        return result;
    }
 
     void Matrix::initializeRandomGenerator() {
        if (!randomGeneratorInitialized) {
            std::srand(static_cast<unsigned>(std::time(nullptr)));
            randomGeneratorInitialized = true;
        }
    }
    
    void Matrix::randomize() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = static_cast<double>(std::rand()) / RAND_MAX;
            }
        }
    }
    
    //product hadamard
     Matrix Matrix::hadamard(Matrix a, Matrix b) {
        if (a.rows != b.rows || a.cols != b.cols) {
            throw std::invalid_argument("Matrices dimensions must match for addition.");
        }

        Matrix result(a.rows, a.cols);
        for (int i = 0; i < a.rows; i++) {
            for (int j = 0; j < a.cols; j++) {
                result.setElement(i, j, a.getElement(i, j) * b.getElement(i, j));
            }
        }
        return result;
    }
    
     Matrix Matrix::add(const Matrix& a, const Matrix& b) {
        if (a.rows != b.rows || a.cols != b.cols) {
            throw std::invalid_argument("Matrices must be of the same dimensions to add.");
        }

        Matrix result(a.rows, a.cols);
        for (int i = 0; i < a.rows; ++i) {
            for (int j = 0; j < a.cols; ++j) {
                result.data[i][j] = a.data[i][j] + b.data[i][j];
            }
        }
        return result;
    }

   
    Matrix Matrix::subtract(const Matrix& a, const Matrix& b) {
        if (a.rows != b.rows || a.cols != b.cols) {
            throw std::invalid_argument("Matrices must be of the same dimensions to subtract.");
        }

        Matrix result(a.rows, a.cols);
        for (int i = 0; i < a.rows; ++i) {
            for (int j = 0; j < a.cols; ++j) {
                result.data[i][j] = a.data[i][j] - b.data[i][j];
            }
        }
        return result;
    }
    // Add two matrices
    Matrix Matrix::add(Matrix other) const {
        
        // if (rows != other.rows || cols != other.cols) {
        //     throw std::invalid_argument("Matrices dimensions must match for addition.");
        // }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.setElement(i, j, this->getElement(i, j) + other.getElement(i, j));
            }
        }
        return result;
    }

    // Multiply two matrices (static method)
     Matrix Matrix::multiply(const Matrix& a, const Matrix& b) {
        
        if (a.cols != b.rows) {
            throw std::invalid_argument("Matrices with incompatible dimensions for multiplication.");
        }
        Matrix result(a.rows, b.cols);
        for (int i = 0; i < result.rows; i++) {
            for (int j = 0; j < result.cols; j++) {
                double sum = 0;
                for (int k = 0; k < a.cols; k++) { // or k < b.rows, since a.cols == b.rows
                    sum += a.data[i][k] * b.data[k][j];
                }
                result.data[i][j] = sum;
            }
        }
        return result;
    }

    // Display the matrix
    void Matrix::display() {
        cout << this->toString();
    }
    

