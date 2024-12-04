#include <iostream>
#include <vector>

using namespace std;

void readInput(int n, int m, vector<vector<int>>& operationTable,
               vector<vector<vector<int>>>& dpTable, int& result) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> operationTable[i][j];
        }
    }
    int value;
    for (int i = 0; i < m; i++) {
        cin >> value;
        dpTable[i][i].push_back(value);
    }
    cin >> result;
}

void backtrack(const vector<vector<vector<int>>>& dpTable, int lin,
                     int col, int subResult, string& expression) {
    // Caso base: célula diagonal principal, retorna o elemento
    if (lin == col) {
        expression += to_string(dpTable[lin][col][0]);
        return;
    }

    int parenthesis, leftResult, rightResult;
    for(size_t i = 0; i < dpTable[lin][col].size(); i++) {
        if (dpTable[lin][col][i] == subResult) {
            parenthesis = dpTable[col][lin][3 * i]; 
            leftResult = dpTable[col][lin][3 * i + 1];
            rightResult = dpTable[col][lin][3 * i + 2];
            
            expression += "(";
            backtrack(dpTable, lin, parenthesis, leftResult, expression); 
            expression += " ";
            backtrack(dpTable, parenthesis + 1, col, rightResult, expression);
            expression += ")";
            break;
        }
    } 
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n, m, result;
    cin >> n >> m;

    vector<vector<int>> operationTable(n, vector<int>(n));
    vector<vector<vector<int>>> dpTable(m, vector<vector<int>>(m)); 

    readInput(n, m, operationTable, dpTable, result);

    for (int diagonal = 1; diagonal < m; diagonal++) {
        for (int lin = 0; lin < m - diagonal; lin++) { // para cada celula
            int col = lin + diagonal;
            vector<bool> buffer(n, false); // buffer ocupa espaço mas é mais rapido

            // provavelmente o solution counter ate podia sair se metessemos um vetor das solucoes
            // de tamanho maximo n (ou n*4) e q qnd chegasse ao fim do vetor parava
            int solutionCounter = 0; // isto podia ser um for loop ou while

            for (int i = diagonal - 1; i >= 0; i--) { // para cada numero dentra celula
                for (int leftResult : dpTable[lin][lin + i]) {
                    for (int rightResult : dpTable[lin + i + 1][col]) {
                        if (solutionCounter == n) {
                            break;
                        }
                        int subResult = operationTable[leftResult - 1][rightResult - 1];
                        if (buffer[subResult - 1]) {
                            continue;
                        }
                        dpTable[lin][col].push_back(subResult);

                        // infos necessarias para backtrack
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
    for (size_t final = 0; final < dpTable[0][m - 1].size(); final++) {
        if (dpTable[0][m - 1][final] == result) {
            found = true;
            cout << "1" << endl;
            string expression;
            backtrack(dpTable, 0, m - 1, result, expression);
            cout << expression << endl;
            break;
        }
    }

    if (!found) {
        cout << "0" << endl;
    }
    
    return 0; 
}


