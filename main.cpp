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
        for (int lin = 0; lin < m - diagonal; lin++) {
            int col = lin + diagonal;
            for (int i = diagonal - 1; i >= 0; i--) {
                vector<bool> buffer(m, false); // buffer ocupa espaço mas é mais rapido
                int solution_counter = 0;
                for (int leftResult : dpTable[lin][lin + i]) {

                    for (int rightResult : dpTable[lin + i + 1][col]) {
                        int result = operationTable[leftResult - 1][rightResult - 1];
                        if (solution_counter == m) {
                            break;
                        }
                        if (buffer[result-1]) {
                            continue;
                        }
                        dpTable[lin][col].push_back(result);
                        int close_bracket = 0;
                        dpTable[col][lin].push_back(close_bracket);
                        dpTable[col][lin].push_back(leftResult);
                        dpTable[col][lin].push_back(rightResult);
                        buffer[result-1] = true;
                        solution_counter++;
                    }
                    
                    if (solution_counter == m) {
                        break;
                    }
                }
            }
        }
    }

    inputFile.close();  
    return 0;
}

