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
    // Inicializando a rede neural para o jogo da velha
    RedeNeural rn(9, 27, 9); // Ajuste os parâmetros conforme necessário

    // Dados de treinamento (simplificados para demonstração)
    std::vector<Matrix> gameStates; // Representa os estados do jogo
    std::vector<Matrix> nextMoves; // Representa as jogadas ideais
    // Preencha os gameStates e nextMoves com os dados de treinamento
    double entrada[7][9] ={
        {-1,-1,0,1,1,0,-1,1,1},
        {1,0,0,-1,-1,1,1,0,0},
        {0,-1,1,1,1,0,-1,0,0},
        {1,-1,0,-1,-1,1,1,1,0},
        {0,-1,1,0,0,1,0,0,0},
        {0,0,0,0,1,-1,0,0,1},
        {0,0,-1,0,1,0,-1,1,1}
        
    };
    double saida[7][9] ={
        {0,0,1,0,0,0.1,0,0,0},
        {0,1,0.1,0,0,0,01,0.1},
        {0.1,0,0,0,0,1,0,0.1,0.1},
        {0,0,0.1,0,0,0,0,0,1},
        {0.1,0,0,0.1,0.1,0,0.1,0.1,1},
        {1, 0.1, 0.1, 0.1, 0, 0, 0.1, 0.1, 0},
        {0.1,1,0,0.1, 0, 0.1, 0, 0, 0}
    };
    // Treinar a rede neural
    for (int i = 0; i < gameStates.size(); ++i) {
        rn.train(gameStates[i], nextMoves[i]);
    }

    // Loop de jogo
    Matrix currentState(3, 3); // Estado inicial do tabuleiro
    while (true) {
        // Imprimir o estado atual do tabuleiro
        printBoard(currentState);

        // Verificar se o jogo acabou

        // Jogada do humano
        // Obter as coordenadas da jogada do humano e atualizar currentState

        // Jogada da rede neural
        Matrix prediction = rn.predict(currentState);
        // Atualizar currentState com a jogada da rede

        // Imprimir o novo estado do tabuleiro

    return 0;
}
