#ifndef MATRIXCONSOLEUI_H
#define MATRIXCONSOLEUI_H

#include <iostream>
#include <stdexcept>
#include <windows.h>
#include <conio.h>

#include "../lib_matrix/matrix.h"
#include "../lib_mathVector/mathVector.h"
#include "../lib_triangleMatrix/triangleMatrix.h"

class matrixConsoleUI {
public:
    void start();

private:
    void setColor(int text, int bg) const;
    void clearConsole() const;
    int getChoice(int minOption, int maxOption) const;
    void getMatrixSize(size_t& rows, size_t& cols) const;
    void getVectorSize(size_t& size) const;

    template <typename T>
    matrix<T> inputMatrix() const;

    template <typename T>
    triangleMatrix<T> inputTriangleMatrix() const;

    template <typename T>
    mathVector<T> inputVector() const;

    void showMainMenu() const;
    void processChoice(int choice);
};

#endif // MATRIXCONSOLEUI_H