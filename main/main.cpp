// Copyright 2025 Artem Denisov

#define MATRIX_CONSOLE_UI
#ifdef MATRIX_CONSOLE_UI

#include <iostream>
#include <iomanip>
#include "../lib_matrixConsoleUI/matrixConsoleUI.h"

int main() {
	matrixConsoleUI matrixApplication;
	matrixApplication.start();
}

#endif  // MATRIX_CONSOLE_UI
