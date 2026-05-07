#include "../lib_algorithms/algorithms.h"

int findLocalMin(int matrix[][MAX_N], int n) {
    int i = rand() % n;
    int j = rand() % n;
    while (true) {
        int currentElement = matrix[i][j];
        int next_iElem = i;
        int next_jElem = j;

        if (i > 0 && matrix[i - 1][j] < matrix[next_iElem][next_jElem]) {
            next_iElem = i - 1; next_jElem = j;
        }
        if (i < n - 1 && matrix[i + 1][j] < matrix[next_iElem][next_jElem]) {
            next_iElem = i + 1; next_jElem = j;
        }
        if (j > 0 && matrix[i][j - 1] < matrix[next_iElem][next_jElem]) {
            next_iElem = i; next_jElem = j - 1;
        }
        if (j < n - 1 && matrix[i][j + 1] < matrix[next_iElem][next_jElem]) {
            next_iElem = i; next_jElem = j + 1;
        }
        if (next_iElem == i && next_jElem == j) {
            return matrix[i][j];
        }
        i = next_iElem;
        j = next_jElem;
    }
}

bool checkBrackets(std::string str) {
    //int bracketCnt = 0;

    //for (int i = 0; i < str.length(); i++) {
    //    if (str[i] == '(' || str[i] == ')' ||
    //        str[i] == '[' || str[i] == ']' ||
    //        str[i] == '{' || str[i] == '}')
    //    {
    //        bracketCnt++;
    //    }
    //}
    //if (bracketCnt % 2 != 0) {
    //    return false;
    //}
    Stack<char> brackets(str.length());
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '(' || str[i] == '[' || str[i] == '{') {
            brackets.push(str[i]);
            continue;
        }
        if (str[i] == ')')
        {
            if (brackets.isEmpty()) return false;
            if (brackets.top() == '(') brackets.pop();
        }
        if (str[i] == '}') {
            if (brackets.isEmpty()) return false;
            if (brackets.top() == '{') brackets.pop();
        }
        if (str[i] == ']') {
            if (brackets.isEmpty()) return false;
            if (brackets.top() == '[') brackets.pop();
        }
    }
    if (brackets.isEmpty()) return true;
    return false;
}

void readExpression(std::string str) {
    if (!checkBrackets(str)) {
        throw std::runtime_error("readExpression: Some brackets are missing");
    }
    // TODO. Maybe. Probably in the future...
}

int countIslands(const TVector<TVector<int>>& matrix) {
    if (matrix.is_empty()) return 0;

    int rows = matrix.size();
    int cols = matrix[0].size();

    DSU<int> dsu(rows * cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) continue;

            int current = i * cols + j;

            if (j > 0 && matrix[i][j - 1] == 1) {
                dsu.unionSets(current, i * cols + (j - 1));
            }

            if (i > 0 && matrix[i - 1][j] == 1) {
                dsu.unionSets(current, (i - 1) * cols + j);
            }

            if (j < cols - 1 && matrix[i][j + 1] == 1) {
                dsu.unionSets(current, i * cols + (j + 1));
            }

            if (i < rows - 1 && matrix[i + 1][j] == 1) {
                dsu.unionSets(current, (i + 1) * cols + j);
            }
        }
    }

    std::vector<bool> uniqueRoot(rows * cols);
    int islandCount = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 1) {
                int root = dsu.find(i * cols + j);
                if (!uniqueRoot[root]) {
                    uniqueRoot[root] = true;
                    islandCount++;
                }
            }
        }
    }

    return islandCount;
}