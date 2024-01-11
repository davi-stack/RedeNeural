#include "NEURAL_COMPONENTS.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
    int input = 9;//matrix 3x3
    int oculta = 6;//teste a princípio
    int output =9; //matrix 3x3
    Matrix aux;
    Matrix outputTest;
    RedeNeural rn(3, 9, 3, 0.2);
    
    double input_test[4] [9]={
        {0, 0, 1, 0, 2, 1, 0, 0, 0},
        {0, 0, 1, 0, 2, 1, 0, 1, 2},
        {2, 1, 1, 0, 2, 1, 0, 0, 0},
        {2, 0, 1, 2, 1, 1, 0, 0, 0}
    };
    
    for(int i=0;i<4;i++){
    aux = Matrix::vectorTomatriz(input_test[i], 3);
    aux.printJogoDaVelha();
    outputTest = rn.feedforward(aux);
    cout << endl << endl;
    outputTest.display();
    }
     
    
    double entrada[14][9] ={
        /**
         * casos simples, que a decisão de jogada é obvia
         * 2 -> O = bolinha = maquina
         * 1 -> X = outro jogados
         * 0 -> lugar ainda não marcado
         * 
         * */
         
        {1, 2, 0, 0, 1, 0, 0, 0,0},
        {0,0,0, 2, 1, 0, 1, 0, 0},
        {2, 2, 0, 1, 0, 0, 1, 1, 0},
        {1, 0, 0, 1, 2, 0, 2, 1, 0},
        
        
        {1, 2, 0, 1, 0, 0, 0, 0, 0},
        /*
        x O -       0  0 1
        X - -  ->   0  1 1
        - - -      10  1 1
        */
        {1, 1, 0, 2, 0, 0, 0, 0, 0},
        {2,2,0,1,1,0,2,1,1},
        
        {1,0,0,2,2,1,1,0,0},
        
        {0,2,1,1,1,0,2,0,0},
        {1,2,0,2,2,1,1,1,0},
        {0,2,1,0,0,1,0,0,0},
        {0,0,0,0,1,2,0,0,1},
        {0,0,2,0,1,0,2,1,1}
        
    };
    double saida[14][9] ={
        /**
         * saída esperada para entrada i, respectiva
         * 0.1 -> é possível jogar, mas não é uma boa jogada
         * -10 -> não é possível jogar, está preenchido
         * 1 -> boa jogada, é onde ela deve aprender a jogar
         * 
         * */
        {0, 0, 0.1,
        0.1, 0, 0.1,
        0.1, 0.1, 1},
        
        {0.1, 0.1, 1,
        0, 0, 0.1,
        0,  0.1, 0.1},
        
        {0, 0, 1, 0, 0.1, 0.1, 0, 0, 0.1},//3º
        {0, 0.1, 1, 0, 0, 0.1, 0, 0, 0.1},
        
        {0, 0, 0.1, 0, 0.1, 0.1, 1, 0.1, 0.1},//º5
        {0,0,1,0, 0.1, 0.1,0.1, 0.1,0.1 },
        {0,0,1,0,0,0.1,0,0,0},
        
        {0, 0.1, 0.6, 0, 0, 0, 0, 0.1, 0.6},//8º saída
        
        {0.1, 0, 0, 0, 0, 1, 0, 0.1, 0.1},
        {0, 0,0.1, 0, 0, 0, 0, 0,1},
        {0.1, 0, 0,0.1,0.1, 0,0.1,0.1,1},
        {1, 0.1, 0.1, 0.1, 0, 0, 0.1, 0.1, 0},
        {0.1, 1, 0,0.1, 0, 0.1, 0, 0, 0}
    };
    vector<Matrix> entradas(14);
    vector<Matrix> saidas(14);
    for(int i=0;i<14;i++){
        entradas[i] = Matrix::vectorTomatriz(entrada[i],3);
        saidas[i] = Matrix::vectorTomatriz(saida[i],3);
        rn.train(entradas[i], saidas[i]);
    }
    
    cout << "Depois do Teste:" << endl << "-----------------------------------------------" << endl;
     for(int i=0;i<4;i++){
    aux = Matrix::vectorTomatriz(input_test[i], 3);
    aux.printJogoDaVelha();
    outputTest = rn.feedforward(aux);
    cout << endl << endl;
    outputTest.display();
    }
     
    
    
    
    
}


