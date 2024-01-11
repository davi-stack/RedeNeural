#pragma once

namespace NEURAL_COMPONENTS {
    class Matrix{
        public:
        static Matrix vectorTomatriz(double * n, int x);
        void printJogoDaVelha();
        void display();

    };
    class RedeNeural{
        public:
    void train(Matrix input, Matrix output);

    };




}