#include "NeuralComponents.h"
#include <vector>

// Função para imprimir o tabuleiro de jogo da velha
void printBoard(const Matrix& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            double value = board.getElement(i, j);
            if(value == 1) cout << " X ";
            else if(value == -1) cout << " O ";
            else cout << " . ";
        }
        cout << endl;
    }
}
int checkGameState(Matrix &m) {
    // Checando linhas
    int line = m.haveIqualLine();
    if (line != -1) {
        if (m.data[line][0] == 1) return 1;  // 'X' ganhou
        if (m.data[line][0] == -1) return -1; // 'O' ganhou
    }

    // Checando colunas
    int col = m.haveIqualCols();
    if (col != -1) {
        if (m.data[0][col] == 1) return 1;  // 'X' ganhou
        if (m.data[0][col] == -1) return -1; // 'O' ganhou
    }

    // Checando diagonais
    int diag = m.haveIgualDiag();
    if (diag != -1) {
        if (diag == 0 && m.data[0][0] == 1) return 1;  // 'X' ganhou na diagonal principal
        if (diag == 0 && m.data[0][0] == -1) return -1; // 'O' ganhou na diagonal principal
        if (diag == 1 && m.data[0][2] == 1) return 1;  // 'X' ganhou na diagonal secundária
        if (diag == 1 && m.data[0][2] == -1) return -1; // 'O' ganhou na diagonal secundária
    }

    // Checando se ainda há movimentos possíveis
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            if (m.data[i][j] == 0) return 0;  // Jogo ainda não acabou
        }
    }

    // Se nenhuma das condições acima for satisfeita, o jogo terminou empatado
    return 0;  // Jogo empatado ou continua
}

int main() {
    int input = 9;//matrix 3x3
    int oculta = 6;//teste a princípio
    int output =9; //matrix 3x3
    RedeNeural rn(3, 9, 3, 0.4);
    double entrada[7][9] ={
        /**
         * casos simples, que a decisão de jogada é obvia
         * -1 -> O = bolinha = maquina
         * 1 -> X = outro jogados
         * 0 -> lugar ainda não marcado
         * 
         * */
        {-1,-1,0,1,1,0,-1,1,1},
        {1,0,0,-1,-1,1,1,0,0},
        {0,-1,1,1,1,0,-1,0,0},
        {1,-1,0,-1,-1,1,1,1,0},
        {0,-1,1,0,0,1,0,0,0},
        {0,0,0,0,1,-1,0,0,1},
        {0,0,-1,0,1,0,-1,1,1}
        
    };
    double saida[7][9] ={
        /**
         * saída esperada para entrada i, respectiva
         * 0.1 -> é possível jogar, mas não é uma boa jogada
         * -1 -> não é possível jogar, está preenchido
         * 1 -> boa jogada, é onde ela deve aprender a jogar
         * 
         * */
         
        {-10,-10,1,-10,-10,0.1,-10,-10,-10},
        {-10,1,0.1,-10,-10,-10,01,0.1},
        {0.1,-10,-10,-10,-10,1,-10,0.1,0.1},
        {-10,-10,0.1,-10,-10,-10,-10,-10,1},
        {0.1,-10,-10,0.1,0.1,-10,0.1,0.1,1},
        {1, 0.1, 0.1, 0.1, -10, -10, 0.1, 0.1, -10},
        {0.1,1,-10,0.1, -10, 0.1, -10, -10, -10}
    };
    vector<Matrix> entradas(7);
    vector<Matrix> saidas(7);
    for(int i=0;i<7;i++){
        entradas[i] = Matrix::vectorTomatriz(entrada[i],3);
        saidas[i] = Matrix::vectorTomatriz(saida[i],3);
        rn.train(entradas[i], saidas[i]);
    }
    double input_test [9]=
    {-1,-1,0,1,1,0,-1,1,1};
    Matrix input_t = Matrix::vectorTomatriz(input_test, 3);
    input_t.printJogoDaVelha();
    Matrix outputTest = rn.feedforward(input_t);
    cout << endl << endl;
    outputTest.display();
    
    
    
    double input_test2 [9]=
     {1,0,0,-1,-1,1,1,0,0};
    input_t = Matrix::vectorTomatriz(input_test2, 3);
    input_t.printJogoDaVelha();
    outputTest = rn.feedforward(input_t);
    cout << endl << endl;
    outputTest.display();
    
    
    
}



