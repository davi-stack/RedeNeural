#ifndef REDENEURAL_H
#define REDENEURAL_H

#include "Matrix.hpp"

class RedeNeural {
    // ... Declarações da classe RedeNeural
public:
    double learningRate;
    double input;
    double output;
    double oculta;
    void printPeso_in_oc(){
        peso_in_oc.display();
    }
    void printPeso_oc_out(){
        peso_oc_out.display();
    }
    
    Matrix in_oc;
    Matrix oc_out;
    
    //bias to acelerate the process
    Matrix bias_in_oc;
    Matrix bias_oc_out;
    
    Matrix peso_in_oc;
    Matrix peso_oc_out;
    RedeNeural(double i, double oc, double ou, double lernin);
Matrix feedforward(Matrix input);
void train(Matrix input, Matrix expected);
Matrix predict(Matrix input);


};

#endif // REDENEURAL_H
