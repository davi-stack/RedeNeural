#include <bits/stdc++.h>
#include "Matrix.hpp"
#include "RedeNeural.h"
using namespace std;


int main() {
    int input = 3;//matrix 3x3
    int oculta = 9;//teste a princípio
    int output =3; //matrix 3x3
    double lernin = 0.2;
    Matrix aux;
    Matrix outputTest;
    RedeNeural rn(input,oculta, output, lernin);
    
    double input_test[4] [9]={
        {0, 0, 1, 0, 2, 1, 0, 0, 0},
        {0, 0, 1, 0, 2, 1, 0, 1, 2},
        {2, 1, 1, 0, 2, 1, 0, 0, 0},
        {2, 0, 1, 2, 1, 1, 0, 0, 0}
    };
    //  for(int i=0;i<4;i++){
    // aux = Matrix::vectorTomatriz(input_test[i], 3);
    // aux.printJogoDaVelha();
    // outputTest = rn.predict(aux);
    // cout << endl << endl;
    // outputTest.display();
    // }
    
     
    
    double entrada[18][9] ={
        /**
         * casos simhttps://www.onlinegdb.com/edit/WMKrNX29Y#tab-stdinples, que a decisão de jogada é obvia
         * 2 -> O = bolinha = maquina
         * 1 -> X = outro jogados
         * 0 -> lugar ainda não marcado
         * 
         * */
        
        {1, 2, 0,
        0, 1, 0,
        0, 0,0},
        /*
        x O -       0  0 1
        - x -  ->   1  0 1
        - - -      1  1 10
        */
        {0,0,0, 
        2, 1, 0,
        1, 0, 0},
        /*
        - - -       1  1 10
        o x -  ->   0  0 1
        x - -      0  1 1
        */
        {2, 2, 0,
        1, 0, 0,
        1, 1, 0},
        /*
        O O -       0  0 10
        X 0 -  ->   0  0 1
        x X -      0  0 1
        */
        
        
        {1, 0, 0,
        1, 2, 0,
        2, 1, 0},
        /*
        X - -       0  1 10
        X 0 -  ->   0 0 1
        O X -      0  0 1
        */
        
        {1, 2, 0, 1, 0, 0, 0, 0, 0},//5º
        /*
        x O -       0  0 1
        X - -  ->   0  1 1
        - - -      10  1 1
        */
        {1, 1, 0, 2, 0, 0, 0, 0, 0},//6º
        /*
        x X -       0  0 10
        O - -  ->   0  1 1
        - - -       1   1 1
        */
        {2,2,0,1,1,0,2,1,1},//7º
        
        /*
        O O -       0  0 10
        X X -  ->   0  0 1
        O X X       0  0 0
        */
        
        {1,0,0,2,2,1,1,0,0},//8º
        /*
        X - -       0  5 1
        O O X  ->   0  0 0
        X - -       0   5 1
        */

        {0,2,1,1,1,0,2,0,0},//9º
        /*
        - O X       1  0 0
        X X -  ->   0  0 10
        O - -       0  1 1
        */
        {1,2,0,2,2,1,1,1,0},//10º
        /*
        X O -       0  0 1
        O O X  ->   0  0 0
        X X -       0   0 10
        */
        {0,2,1,0,0,1,0,0,0},//11º
        /*
        - O X       1   0  0
        - - X  ->   1  1    0
        - - -       1   1   10
        */
        {0,0,0,0,1,2,0,0,1},//12º
        /*
        - - -       10     1     1
        - X O  ->   1    0    0
        - - X       1   1   0
        */
        
        
        {0,0,0,0,1,0,2,0,1},//13º
        /*
        - - -       10     1     1
        - X -  ->   1    0    1
        O - X       0   1   0
        */
        
        
        {2,0,0,
        0,1,0,
        0,1,1},//14º
        /*
        O - -       0     10     1
        - X 0  ->   1    0    0
        - X X       1  0   0
        */
        
        
        
        {0,0,0,
        0,1,2,
        0,0,1},//15º
        /*
        - - -       10     1     1
        - X 0  ->   1    0    0
        - - X       1   1   0
        */
        
        
        {0,0,0,
        0,1,0,
        1,0,2},//16º
        /*
        - - -       1     1     10
        - X -  ->   1    0    1
        X - O      0   1   0
        */
        
        
        {0,0,0,
        1,2,0,
        0,0,0},//17º
        /*
        - - -       1     1     10
        x O -  ->   0    0    1
        O x X       0   0   0
        */
        
        
        {0,0,0,
        2,1,1,
        2,0,1}//18º
        /*
        - - -       10     1     1
        0 X x  ->   0    0    0
        O - X       0   1   0
        */
        
        
    };
    double saida[18][9] ={
        /**
         * saída esperada para entrada i, respectiva
         * 1 -> é possível jogar, mas não é uma boa jogada
         * 0 -> não é possível jogar, está preenchido
         * 10 -> boa jogada, é onde ela deve aprender a jogar
         * 6 -> jogada boa, porém existe mais de uma
         * */
        {-80, -80, 1,
        1, -80, 1,
        1, 1, 10},//1º
        /*
        x O -       0  0 1
        - x -  ->   1  0 1
        - - -      1  1 10
        */
        
        {1, 1, 10,
        -80, -80, 1,
        -80,  1, 1},//2º
        /*
        - - -       1  1 10
        o x -  ->   0  0 1
        x - -      0  1 1
        */
        
        
        {-80, -80, 10,
        -80, -80, 1,
        -80, -80, 1},//3º
        /*
        O O -       0  0 10
        X 0 -  ->   0  0 1
        x X -      0  0 1
        */
        
        
        {-80, 1, 10,
        -80, -80, 1,
        -80, -80, 1},//4º
        /*
        X - -       0  1 10
        X 0 -  ->   0 0 1
        O X -      0  0 1
        */
        
        
        
        {-80, -80, 1,
        -80, 1, 1,
        10, 1, 1},//º5
        /*
        x O -       0  0 1
        X - -  ->   0  1 1
        - - -      10  1 1
        */
        
        
        
        {-80, -80,10,
        -80, 1, 1,
        1, 1,1 },//6º
        /*
        x X -       0  0 10
        O - -  ->   0  1 1
        - - -       1   1 1
        */
        
        
        
        
        
        {-80, -80, 10,
        -80,-80,1,
        -80,-80,-80},//7º
         /*
        O O -       0  0 10
        X X -  ->   0  0 1
        O X X       0  0 0
        */
        
        {-80, 5, 1,
        -80, -80, -80,
        -80, 5, 1},//8º saída
        /*
        X - -       0  5 1
        O O X  ->   0  0 0
        X - -       0   5 1
        */
        
        {1, -80, -80,
        -80, -80, 10,
        -80, 1, 1},//9º
        /*
        - O X       1  0 0
        X X -  ->   0  0 10
        O - -       0  1 1
        */
        
        {-80, -80,1,
        -80, -80, -80,
        -80, -90,10},//10º
        /*
        X O -       0  0 1
        O O X  ->   0  0 0
        X X -       0   0 10
        */
        
        {1, -80, -80,
        1,1, -80,
        1,1,10},//11º
        
        /*
        - O X       1   0  0
        - - X  ->   1  1    0
        - - -       1   1   10
        */
        
        {10, 1, 1,
        1, -80, -80, 
        1, 1, -80},//12º
        /*
        - - -       10     1     1
        - X O  ->   1    0    0
        - - X       1   1   0
        */
        
        {10, 1, 1,
        1, -80, 1,
        -80, 1, -80},//13º
        /*
        - - -       10     1     1
        - X -  ->   1    0    1
        O - X       0   1   0
        */
        
        {-80,10,1,
        1,-80,-80,
        1,-80, -80},//14º
        /*
        O - -       0     10     1
        - X 0  ->   1    0    0
        - X X       1  0   0
        */
        
        
        
        {10,1,1,
        1, -80, -80,
        1,1, -80},//15º
        /*
        - - -       10     1     1
        - X 0  ->   1    0    0
        - - X       1   1   0
        */
        
        
        {1,1,10,
        1, -80,1,
        -80,1, -80},//16º
        /*
        - - -       1     1     10
        - X -  ->   1    0    1
        X - O      0   1   0
        */
        
        
        {1,1,10,
        -80,-80,1,
        -80,-80,-80},//17º
        /*
        - - -       1     1     10
        x O -  ->   0    0    1
        O x X       0   0   0
        */
        
        
        {10,1,1,
        -80,-80,-80,
        -80,1,-80}//18º
        /*
        - - -       10     1     1
        0 X x  ->   0    0    0
        O - X       0   1   0
        */
    };
    
    
    
    
    
    
    
    
    
    
    
    
    vector<Matrix> entradas(18);
    vector<Matrix> saidas(18);
    for(int i=0;i<18;i++){
        
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
     outputTest.maxNumI();
    
    }
     
    
}
