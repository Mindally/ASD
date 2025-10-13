// Copyright 2025 Artem Denisov

//#define POINTCIRCLE
#ifdef POINTCIRCLE

#include "../lib_circle/circle.h"
#include "../lib_point/point.h"
#include <iostream>

enum IntersectStates { NoTouch, OnePoint, IntersectTwoTimes, OneInEnotherAndIntersect, OneInEnother, Equal };

IntersectStates isIntersect(circle circle1, circle circle2) {
    double d = circle1.distanceBetweenCentres(circle2);
    int R = circle1.getRadius();
    int r = circle2.getRadius();
    if (circle1.isEqual(circle2)) return Equal;
    if (d > R + r) return NoTouch;
    if (d == R + r) return OnePoint;
    if ((R - r < d) && (d < R + r)) return IntersectTwoTimes;
    if (d == R - r) return OneInEnotherAndIntersect;
    if (d < R - r) return OneInEnother;
}

int main()
{
    point testPoint;
    point CNSPoint(10, -10);
    point otherPoint(CNSPoint);
    testPoint.consolePrint(true);
    CNSPoint.consolePrint(true);
    otherPoint.consolePrint(true);
    testPoint.setCords(-86, 14);
    otherPoint.assign(testPoint);
    if (otherPoint.isEqual(testPoint) && testPoint.isEqual(otherPoint)) {
        std::cout << "Tochki ravni, prisvaivanie succesful" << std::endl;
    }
    else std::cout << "Tochki ne ravni, prisvaivanie unsuccesful" << std::endl;
    std::cout << "Distance between 10, -10 & -86, 14 = " << CNSPoint.distanceBetween(testPoint) << std::endl;

    circle testCircle;
    circle CNSCircle(CNSPoint, 10);
    circle otherCircle1(20, 20, 5);
    circle otherCircle2(otherCircle1);
    testCircle.consolePrint(true);
    CNSCircle.consolePrint(true);
    otherCircle1.consolePrint(true);
    otherCircle2.consolePrint(true);
    otherCircle1.assign(testCircle);
    if (otherCircle1.isEqual(testCircle) && testCircle.isEqual(otherCircle1)) {
        std::cout << "Circles ravni, prisvaivanie succesful" << std::endl;
    }
    else std::cout << "Circles ne ravni, prisvaivanie unsuccesful" << std::endl;

    circle distCircle1(0, 0, 1);
    circle distCircle2(0, 0, 1);
    std::cout << "Distance Equal: " << isIntersect(distCircle1, distCircle2) << std::endl;

    distCircle1.setCordsCentre(1, 0);
    distCircle2.setCordsCentre(-1, 0);
    std::cout << "Distance OneTime: " << isIntersect(distCircle1, distCircle2) << std::endl;

    distCircle1.setCordsCentre(100, 0);
    distCircle2.setCordsCentre(-1, 0);
    std::cout << "Distance NoTouch: " << isIntersect(distCircle1, distCircle2) << std::endl;

    distCircle1.setCordsCentre(1, 0);
    distCircle2.setCordsCentre(0, 0);
    std::cout << "Distance IntersectTwoTimes: " << isIntersect(distCircle1, distCircle2) << std::endl;

    distCircle1.setCordsCentre(0, 0);
    distCircle2.setCordsCentre(1, 0);
    distCircle1.setRadius(2);
    distCircle2.setRadius(1);
    std::cout << "Distance OneInEnotherAndIntersect: " << isIntersect(distCircle1, distCircle2) << std::endl;

    distCircle1.setCordsCentre(0, 0);
    distCircle2.setCordsCentre(0, 0);
    distCircle1.setRadius(2);
    distCircle2.setRadius(1);
    std::cout << "Distance OneInEnother: " << isIntersect(distCircle1, distCircle2) << std::endl;

}

#endif // POINTCIRCLE


//#define MATRIX_CONSOLE_UI
#ifdef MATRIX_CONSOLE_UI

#include <iostream>
#include <iomanip>
#include "../lib_matrixConsoleUI/matrixConsoleUI.h"

int main() {
	//matrixConsoleUI matrixApplication;
	//matrixApplication.start();
}

#endif // POINTCIRCLE


#define MATRIX_LOCAL_MIN
#ifdef MATRIX_LOCAL_MIN

#include <iostream>
#include "../lib_algorithms/algorithms.h"

#define MAX_N 100

bool checkLocalMin(int matrix[][MAX_N], int n, int value, int row, int col) {
    if (row > 0 && matrix[row - 1][col] <= value) return false;
    if (row < n - 1 && matrix[row + 1][col] <= value) return false;
    if (col > 0 && matrix[row][col - 1] <= value) return false;
    if (col < n - 1 && matrix[row][col + 1] <= value) return false;
    return true;
}

void testBasicMatrix() {
    const int n = 3;
    int matrix[MAX_N][MAX_N] = {
        {3, 1, 2},
        {5, 8, 4},
        {7, 6, 9}
    };
    int result = findLocalMin(matrix, n);

    int found_i = -1, found_j = -1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (matrix[i][j] == result) {
                found_i = i;
                found_j = j;
            }

    if (!checkLocalMin(matrix, n, result, found_i, found_j) ||
        (result != 1 && result != 6)) {
        std::cout << "1. FAILED\n";
    }
    else {
        std::cout << "1. PASSED\n";
    }
}

void testSingleElement() {
    const int n = 1;
    int matrix[MAX_N][MAX_N] = { {42} };
    int result = findLocalMin(matrix, n);

    int found_i = -1, found_j = -1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (matrix[i][j] == result) {
                found_i = i;
                found_j = j;
            }

    if (!checkLocalMin(matrix, n, result, found_i, found_j) || result != 42) {
        std::cout << "2. FAILED\n";
    }
    else {
        std::cout << "2. PASSED\n";
    }
}

void testTwoByTwo() {
    const int n = 2;
    int matrix[MAX_N][MAX_N] = {
        {5, 2},
        {7, 3}
    };
    int result = findLocalMin(matrix, n);

    int found_i = -1, found_j = -1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (matrix[i][j] == result) {
                found_i = i;
                found_j = j;
            }

    if (!checkLocalMin(matrix, n, result, found_i, found_j) ||
        (result != 2 && result != 3)) {
        std::cout << "3. FAILED\n";
    }
    else {
        std::cout << "3. PASSED\n";
    }
}

void testCornerMin() {
    const int n = 3;
    int matrix[MAX_N][MAX_N] = {
        {6, 5, 1},
        {7, 8, 9},
        {10,11,12}
    };
    int result = findLocalMin(matrix, n);

    int found_i = -1, found_j = -1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (matrix[i][j] == result) {
                found_i = i;
                found_j = j;
            }

    if (!checkLocalMin(matrix, n, result, found_i, found_j) || result != 1) {
        std::cout << "4. FAILED\n";
    }
    else {
        std::cout << "4. PASSED\n";
    }
}

void testMiddleMin() {
    const int n = 3;
    int matrix[MAX_N][MAX_N] = {
        {8,7,6},
        {5,1,4},
        {9,3,10}
    };
    int result = findLocalMin(matrix, n);

    int found_i = -1, found_j = -1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (matrix[i][j] == result) {
                found_i = i;
                found_j = j;
            }

    if (!checkLocalMin(matrix, n, result, found_i, found_j) || result != 1) {
        std::cout << "5. FAILED\n";
    }
    else {
        std::cout << "5. PASSED\n";
    }
}

void testSidesMin() {
    const int n = 3;
    int matrix[MAX_N][MAX_N] = {
        {9,8,7},
        {6,5,1},
        {3,2,4}
    };
    int result = findLocalMin(matrix, n);

    int found_i = -1, found_j = -1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (matrix[i][j] == result) {
                found_i = i;
                found_j = j;
            }

    if (!checkLocalMin(matrix, n, result, found_i, found_j) ||
        (result != 1 && result != 2)) {
        std::cout << "6. FAILED\n";
    }
    else {
        std::cout << "6. PASSED\n";
    }
}

int main() {
    testBasicMatrix();
    testSingleElement();
    testTwoByTwo();
    testCornerMin();
    testMiddleMin();
    testSidesMin();

    return 0;
}

#endif  // MATRIX_LOCAL_MIN
