// NeuralComponents.h
#ifndef NEURAL_COMPONENTS_H
#define NEURAL_COMPONENTS_H

#include <bits/stdc++.h>
class Matrix {
private:
    

public:
std::vector<std::vector<double>> data;
    int rows;
    int cols;
    // Constructor to create a matrix of a given size initialized to 0
    Matrix(int i, int j) : rows(i), cols(j) {
        data.resize(i, std::vector<double>(j, 0.0));
    }

    // Randomize the matrix with values between 0 and 1
    void randomize() {
        // Initialize the random number generator
        std::srand(static_cast<unsigned>(std::time(nullptr)));

        // Assign random values to each element in the matrix
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = static_cast<double>(std::rand()) / RAND_MAX;
            }
        }
    }

    // Apply a function to each element in the matrix
    void applyFunction(std::function<double(double)> func) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = func(data[i][j]);
            }
        }
    }

    // Convert the matrix to a string for display
    string toString() {
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
    double getElement(int i, int j) const {
        return data[i][j];
    }

    // Setter for a specific element
    void setElement(int i, int j, double val) {
        data[i][j] = val;
    }

    // Static function to create a matrix from a vector
    static Matrix matrixFromVector(vector<double> aux) {
        Matrix result(static_cast<int>(aux.size()), 1);
        for(int i = 0; i < aux.size(); i++) {
            result.data[i][0] = aux[i];
        }
        return result;
    }

    // Add two matrices
    Matrix add(Matrix other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrices dimensions must match for addition.");
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.setElement(i, j, this->getElement(i, j) + other.getElement(i, j));
            }
        }
        return result;
    }

    // Multiply two matrices (static method)
    static Matrix multiply(const Matrix& a, const Matrix& b) {
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
    void display() {
        cout << this->toString();
    }
};
double sigmoide(double a) {
    return 1.0 / (1.0 + std::exp(-a));
}
class RedeNeural{
    public:
    int input;
    int output;
    int oculta;
    
    Matrix in_oc;
    Matrix oc_out;
    
    //bias to acelerate the process
    Matrix bias_in_oc;
    Matrix bias_oc_out;
    
    Matrix peso_in_oc;
    Matrix peso_oc_out;
    
    RedeNeural(int i, int oc, int ou) : input(i), output(ou), oculta(oc), in_oc(i, 1), oc_out(oc, 1),
    peso_in_oc(oc, i), peso_oc_out(ou, oc), bias_in_oc(oc, 1), bias_oc_out(ou, 1) {
    bias_oc_out.randomize();
    bias_in_oc.randomize();
    peso_oc_out.randomize();
    peso_in_oc.randomize();
        
    }

    // void feedforward(vector<int> arr){
    // Matrix input = Matrix::matrixFromVector(arr);  // Corrigido para usar ::    }
    // Matrix hidden = Matrix::multiply(this->peso_in_oc, input);
    // hidden.add(this->bias_in_oc);
    // cout << hidden.toString() << endl;
    // hidden.applyFunction([](int x) -> double { return sigmoide(x); });
    // cout << hidden.toString() << endl;
    // }
    void feedforward(vector<double> arr) {
        //INPUT -> HIDDEN
        Matrix input = Matrix::matrixFromVector(arr);
        Matrix hidden = Matrix::multiply(peso_in_oc, input);
        hidden.add(bias_in_oc);
        //std::cout << hidden.toString() << std::endl;

        // Aplicando a função sigmoide a cada elemento da matriz 'hidden'
        hidden.applyFunction(sigmoide);
        //std::cout << hidden.toString() << std::endl;
        
        /*
        HIDDEN -> OUTPUT
        */
        Matrix output = Matrix::multiply(peso_oc_out, hidden);
        output = output.add(bias_oc_out);
        output.applyFunction(sigmoide);
        cout << output.toString() << endl;
        
    }
};

#endif // NEURAL_COMPONENTS_H
