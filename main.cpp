#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void readInput(ifstream& inputFile, int& n, int& m, vector<vector<int>>& table,
               vector<int>& sequence, int& result) {
    inputFile >> n >> m;
    table.resize(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inputFile >> table[i][j];
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
    vector<vector<int>> table;
    vector<int> sequence;

    readInput(inputFile, n, m, table, sequence, result);
    inputFile.close();  
    return 0;
}

