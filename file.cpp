#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void readInput(ifstream& inputFile, int& n, int& m, vector<vector<int>>& operationTable,
               vector<int>& sequence, int& result) {
    inputFile >> n >> m;
    operationTable.resize(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inputFile >> operationTable[i][j];
        }
    }
    sequence.resize(m);  
    for (int i = 0; i < m; i++) {
        inputFile >> sequence[i];
    }
    inputFile >> result;
    inputFile.close();  
}

void buildExpression(const vector<vector<vector<int>>>& dpTable, int lin,
                     int col, int subResult, string& expression) {
    if (lin == col) {
        // Caso base: célula diagonal principal, retorna o elemento
        expression += to_string(dpTable[lin][col][0]);
        return;
    }
    int parenthesis, leftResult, rightResult;
    for(std::size_t i = 0; i < dpTable[lin][col].size(); i++) {
        if (dpTable[lin][col][i] == subResult) {
            parenthesis = dpTable[col][lin][3 * i]; 
            leftResult = dpTable[col][lin][3 * i + 1];  // Segundo elemento: resultado da esquerda
            rightResult = dpTable[col][lin][3 * i + 2]; // Terceiro elemento: resultado da direita
            // Adiciona parêntese esquerdo
            expression += "(";
            buildExpression(dpTable, lin, parenthesis, leftResult, expression); // Recursão para o lado esquerdo
            expression += " ";
            // Adiciona parêntese direito
            expression += "";
            buildExpression(dpTable, parenthesis + 1, col, rightResult, expression); // Recursão para o lado direito
            expression += ")";
            break;
        }
    }


    
}

int main(int argc, char* argv[]) {
    ifstream inputFile(argv[1]);
    int n, m, result;
    // ???? ver se o recise nao é mais lento
    vector<vector<int>> operationTable;
    vector<int> sequence;

    readInput(inputFile, n, m, operationTable, sequence, result);

    // posso criar isto dentro do readInput para nao correr 2 vezes o mesmo for TODO
    vector<vector<vector<int>>> dpTable(m, vector<vector<int>>(m)); 
    for (int i = 0; i < m; i++) {
        dpTable[i][i].push_back(sequence[i]);
    }

    for (int diagonal = 1; diagonal < m; diagonal++) {
        for (int lin = 0; lin < m - diagonal; lin++) { // para cada celula
            int col = lin + diagonal;
            vector<bool> buffer(n, false); // buffer ocupa espaço mas é mais rapido
            int solutionCounter = 0; // isto podia ser um for loop ou while
            // provavelmente o solution counter ate podia sair se metessemos um vetor das solucoes
            // de tamanho maximo n (ou n*4) e q qnd chegasse ao fim do vetor parava
            for (int i = diagonal - 1; i >= 0; i--) { // para cada numero dentra celula
                for (int leftResult : dpTable[lin][lin + i]) {
                    for (int rightResult : dpTable[lin + i + 1][col]) {
                        if (solutionCounter == n) {
                            break;
                        }
                        int subResult = operationTable[leftResult - 1][rightResult - 1];
                        if (buffer[subResult-1]) {
                            continue;
                        }
                        dpTable[lin][col].push_back(subResult);
                        int closeBracket = lin + i;
                        dpTable[col][lin].push_back(closeBracket);
                        dpTable[col][lin].push_back(leftResult);
                        dpTable[col][lin].push_back(rightResult);
                        buffer[subResult-1] = true;
                        solutionCounter++;
                    }
                    if (solutionCounter == n) {
                        break;
                    }
                }
            }
        }
    }

    bool found = false;
    for (std::size_t final = 0; final < dpTable[0][m - 1].size(); final++) {
        if (dpTable[0][m - 1][final] == result) {
            found = true;
            cout << "1" << endl;
            string expression;
            buildExpression(dpTable, 0, m - 1, result, expression);
            cout << expression << endl;
            break;
        }
    }
    if (!found) {
        cout << "0" << endl;
    }
    return 0; 
}


