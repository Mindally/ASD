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
    Stack<char> brackets(str.length() / 2);
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
}