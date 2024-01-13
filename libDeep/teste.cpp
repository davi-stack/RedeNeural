#include <bits/stdc++.h>
void display(std::ofstream& file, const std::string& text) {
    file << text << std::endl;
}
int main() {
    std::ofstream file("meu_arquivo.txt"); // Abre ou cria o arquivo para escrita
    if (!file.is_open()) {
        std::cerr << "Falha ao abrir o arquivo." << std::endl;
        return 1;
    }

    std::string minhaString = "Olá, Mundo!";
    display(file, minhaString); // Grava a string no arquivo

    file.close(); // Fecha o arquivo
    return 0;
}
