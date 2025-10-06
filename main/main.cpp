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


#define MATRIX_CONSOLE_UI
#ifdef MATRIX_CONSOLE_UI

#include <iostream>
#include <iomanip>
#include "../lib_matrixConsoleUI/matrixConsoleUI.h"

int main() {
	//matrixConsoleUI matrixApplication;
	//matrixApplication.start();
}

#endif  // MATRIX_CONSOLE_UI
