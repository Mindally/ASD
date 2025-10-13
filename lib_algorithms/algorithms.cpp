#include <cstdlib>
#include <ctime>
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