//#include "matrixConsoleUI.h"
//
//void matrixConsoleUI::start() {
//    while (true) {
//        showMainMenu();
//        int choice = getChoice(0, 9);
//
//        if (choice == 0) break;
//
//        try {
//            processChoice(choice);
//        }
//        catch (const std::exception& e) {
//            std::cout << "Error: " << e.what() << std::endl;
//            std::cout << "Press any key to continue...";
//            _getch();
//        }
//    }
//}
//
//void matrixConsoleUI::setColor(int text, int bg) const {
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//    SetConsoleTextAttribute(hConsole, (bg << 4) | text);
//}
//
//void matrixConsoleUI::clearConsole() const {
//    system("cls");
//}
//
//int matrixConsoleUI::getChoice(int minOption, int maxOption) const {
//    int choice;
//    while (true) {
//        std::cout << "Select option (" << minOption << "-" << maxOption << "): ";
//        std::cin >> choice;
//        if (choice < minOption || choice > maxOption) {
//            std::cout << "Input error! Please try again.\n";
//        }
//        else {
//            return choice;
//        }
//    }
//}
//
//void matrixConsoleUI::getMatrixSize(size_t& rows, size_t& cols) const {
//    std::cout << "Enter number of rows: ";
//    std::cin >> rows;
//    std::cout << "Enter number of columns: ";
//    std::cin >> cols;
//}
//
//void matrixConsoleUI::getVectorSize(size_t& size) const {
//    std::cout << "Enter vector size: ";
//    std::cin >> size;
//}
//
//template <typename T>
//matrix<T> matrixConsoleUI::inputMatrix() const {
//    size_t rows, cols;
//    getMatrixSize(rows, cols);
//    matrix<T> matrix(rows, cols);
//    std::cout << "Enter matrix elements:\n";
//    std::cin >> matrix;
//    return matrix;
//}
//
//template <typename T>
//triangleMatrix<T> matrixConsoleUI::inputTriangleMatrix() const {
//    size_t rows, cols;
//    getMatrixSize(rows, cols);
//    triangleMatrix<T> matrix(rows, cols);
//    std::cout << "Enter triangle matrix elements:\n";
//    std::cin >> matrix;
//    return matrix;
//}
//
//template <typename T>
//mathVector<T> matrixConsoleUI::inputVector() const {
//    size_t size;
//    getVectorSize(size);
//    mathVector<T> vector(size);
//    std::cout << "Enter vector elements:\n";
//    std::cin >> vector;
//    return vector;
//}
//
//void matrixConsoleUI::showMainMenu() const {
//    clearConsole();
//    setColor(2, 0);
//    std::cout << "=== MATRIX CALCULATOR ===\n";
//    setColor(7, 0);
//    std::cout << "1. Matrix * Matrix\n"
//        << "2. Matrix * Vector\n"
//        << "3. Vector * Matrix\n"
//        << "4. Vector * Vector (scalar product)\n"
//        << "5. Matrix + Matrix\n"
//        << "6. Matrix - Matrix\n"
//        << "7. TriangleMatrix + TriangleMatrix\n"
//        << "8. TriangleMatrix - TriangleMatrix\n"
//        << "9. TriangleMatrix * TriangleMatrix\n"
//        << "0. Exit\n";
//}
//
//void matrixConsoleUI::processChoice(int choice) {
//    clearConsole();
//
//    switch (choice) {
//    case 1: { // Matrix * Matrix
//        std::cout << "=== MATRIX * MATRIX ===\n";
//        matrix<int> m1 = inputMatrix<int>();
//        matrix<int> m2 = inputMatrix<int>();
//        matrix<int> result = m1 * m2;
//        std::cout << "Result:\n" << result;
//        break;
//    }
//    case 2: { // Matrix * Vector
//        std::cout << "=== MATRIX * VECTOR ===\n";
//        matrix<int> m = inputMatrix<int>();
//        mathVector<int> v = inputVector<int>();
//        mathVector<int> result = m * v;
//        std::cout << "Result:\n" << result;
//        break;
//    }
//    case 3: { // Vector * Matrix
//        std::cout << "=== VECTOR * MATRIX ===\n";
//        mathVector<int> v = inputVector<int>();
//        matrix<int> m = inputMatrix<int>();
//        mathVector<int> result = v * m;
//        std::cout << "Result:\n" << result;
//        break;
//    }
//    case 4: { // Vector * Vector
//        std::cout << "=== VECTOR * VECTOR (SCALAR) ===\n";
//        mathVector<int> v1 = inputVector<int>();
//        mathVector<int> v2 = inputVector<int>();
//        int result = v1 * v2;
//        std::cout << "Result: " << result << std::endl;
//        break;
//    }
//    case 5: { // Matrix + Matrix
//        std::cout << "=== MATRIX + MATRIX ===\n";
//        matrix<int> m1 = inputMatrix<int>();
//        matrix<int> m2 = inputMatrix<int>();
//        matrix<int> result = m1 + m2;
//        std::cout << "Result:\n" << result;
//        break;
//    }
//    case 6: { // Matrix - Matrix
//        std::cout << "=== MATRIX - MATRIX ===\n";
//        matrix<int> m1 = inputMatrix<int>();
//        matrix<int> m2 = inputMatrix<int>();
//        matrix<int> result = m1 - m2;
//        std::cout << "Result:\n" << result;
//        break;
//    }
//    case 7: { // TriangleMatrix + TriangleMatrix
//        std::cout << "=== TRIANGLEMATRIX + TRIANGLEMATRIX ===\n";
//        triangleMatrix<int> tm1 = inputTriangleMatrix<int>();
//        triangleMatrix<int> tm2 = inputTriangleMatrix<int>();
//        triangleMatrix<int> result = tm1 + tm2;
//        std::cout << "Result:\n" << result;
//        break;
//    }
//    case 8: { // TriangleMatrix - TriangleMatrix
//        std::cout << "=== TRIANGLEMATRIX - TRIANGLEMATRIX ===\n";
//        triangleMatrix<int> tm1 = inputTriangleMatrix<int>();
//        triangleMatrix<int> tm2 = inputTriangleMatrix<int>();
//        triangleMatrix<int> result = tm1 - tm2;
//        std::cout << "Result:\n" << result;
//        break;
//    }
//    case 9: { // TriangleMatrix * TriangleMatrix
//        std::cout << "=== TRIANGLEMATRIX * TRIANGLEMATRIX ===\n";
//        triangleMatrix<int> tm1 = inputTriangleMatrix<int>();
//        triangleMatrix<int> tm2 = inputTriangleMatrix<int>();
//        triangleMatrix<int> result = tm1 * tm2;
//        std::cout << "Result:\n" << result;
//        break;
//    }
//    }
//
//    std::cout << "\nPress any key to continue...";
//    _getch();
//}
//
//template matrix<int> matrixConsoleUI::inputMatrix<int>() const;
//template triangleMatrix<int> matrixConsoleUI::inputTriangleMatrix<int>() const;
//template mathVector<int> matrixConsoleUI::inputVector<int>() const;