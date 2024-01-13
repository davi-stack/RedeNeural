#include "Matrix.hpp"
#include "RedeNeural.h"

RedeNeural::RedeNeural(double i, double oc, double ou, double lernin) : input(i), output(ou), oculta(oc), in_oc(i, 1), oc_out(oc, 1),
    peso_in_oc(oc, i), peso_oc_out(ou, oc), bias_in_oc(oc, 1), bias_oc_out(ou, 1) {
    bias_oc_out.randomize();
    bias_in_oc.randomize();
    peso_oc_out.randomize();
    peso_in_oc.randomize();
    
    this->learningRate = lernin;
        
    }

    // void feedforward(vector<int> arr){
    // Matrix input = Matrix::matrixFromVector(arr);  // Corrigido para usar ::    }
    // Matrix hidden = Matrix::multiply(this->peso_in_oc, input);
    // hidden.add(this->bias_in_oc);
    // cout << hidden.toString() << endl;
    // hidden.applyFunction([](int x) -> double { return sigmoide(x); });
    // cout << hidden.toString() << endl;
    // }
    Matrix RedeNeural::feedforward(Matrix input) {
        //INPUT -> HIDDEN
        Matrix hidden = Matrix::multiply(peso_in_oc, input);
        hidden = hidden.add(bias_in_oc);
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
        return output;
        
    }
    
    void RedeNeural::train(Matrix input, Matrix expected) {
        //INPUT -> HIDDEN
        Matrix hidden = Matrix::multiply(peso_in_oc, input);
        hidden = hidden.add(bias_in_oc);
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
        
        
        //BACKPROPAGATION
        
        //OUTPUT -> HIDDEN 
        Matrix output_Error = Matrix::subtract(expected, output);
        Matrix outputD = Matrix::applyFunction(output, dSigmoide);//derivada da saída(sigmóide)
        Matrix hiddenT = Matrix::transpose(hidden);//transposed HIDDEN
        Matrix gradient = Matrix::hadamard(output_Error, outputD);
        gradient = Matrix::scalarMultiply(gradient, learningRate);
        
        //ajust bias
        bias_oc_out = bias_oc_out.add(gradient);
        
        
        Matrix peso_oculta_saida_delta = Matrix::multiply(gradient, hiddenT);
        this->peso_oc_out = peso_oc_out.add(peso_oculta_saida_delta);
        
        
        
        
        
        //HIDDEN -> input
        Matrix peso_oc_outT = Matrix::transpose(peso_oc_out);
        Matrix hiddenError = Matrix::multiply(peso_oc_outT, output_Error);//peso oculta
        Matrix d_hidden = Matrix::applyFunction(hidden, sigmoide);
        Matrix input_T = Matrix::transpose(input);
        Matrix gradient_oc = Matrix::hadamard(hiddenError, d_hidden);
        gradient_oc = Matrix::scalarMultiply(gradient_oc,learningRate );
        
        
        //ajust bias hidden -> input
        bias_in_oc = bias_in_oc.add(gradient_oc);
        Matrix pesos_in_oc_deltas = Matrix::multiply(gradient_oc, input_T);
        peso_in_oc = peso_in_oc.add(pesos_in_oc_deltas);
    }
   
   
   
   
    Matrix RedeNeural::predict(Matrix input){
    Matrix hidden = Matrix::multiply(peso_in_oc, input);
    hidden = hidden.add(bias_in_oc);
    
    Matrix output = Matrix::multiply(peso_oc_out, hidden);
    output = output.add(bias_oc_out);
    output.applyFunction(sigmoide);
    
    return output;
    }
