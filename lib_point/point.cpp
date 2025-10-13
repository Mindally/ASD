#include "point.h"

point::point() {
	_x = 0;
	_y = 0;
}

point::point(int x, int y) {
	_x = x;
	_y = y;
}

point::point(const point& other) {
	_x = other._x;
	_y = other._y;
}

void point::setCords(int x, int y) {
	setCordX(x);
	setCordY(y);
}

void point::setCordX(int x) {
	_x = x;
}

void point::setCordY(int y) {
	_y = y;
}

void point::assign(const point& other) {
	_x = other._x;
	_y = other._y;
}
bool point::isEqual(const point& other) {
	return (_x == other._x && _y == other._y);
}

void point::consolePrint(bool endl) {
	std::cout << "X: " << getCordX() << " Y: " << getCordY();
	if (endl) std::cout << std::endl;
}

int point::getCordX() const {
	return _x;
}

int point::getCordY() const {
	return _y;
}

double point::distanceBetween(const point& other) {
	return sqrt(pow(_x - other._x, 2) + pow(_y - other._y, 2));
}