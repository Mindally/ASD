#include "circle.h"

circle::circle() {
	_centre.setCords(0, 0);
	_radius = 1;
}

circle::circle(point centre, int radius) {
	if (radius <= 0) throw std::invalid_argument("circle: radius must be positive");
	_centre.assign(centre);
	_radius = radius;
}

circle::circle(int x, int y, int radius) {
	if (radius <= 0) throw std::invalid_argument("circle: radius must be positive");
	_centre.setCords(x, y);
	_radius = radius;

}
circle::circle(const circle& other) {
	_centre.assign(other._centre);
	_radius = other._radius;
}

void circle::setPoint(point other) {
	_centre.assign(other);
}
void circle::setCordsCentre(int x, int y) {
	_centre.setCords(x, y);
}
void circle::setRadius(int radius) {
	if (radius <= 0) throw std::invalid_argument("circle: radius must be positive");
	_radius = radius;
}

void circle::assign(const circle& other) {
	setPoint(other._centre);
	setRadius(other._radius);
}
void circle::consolePrint(bool endl) {
	std::cout << "C_X: " << getCentreCordX() << " C_Y: " << getCentreCordY() << " RAD: " << getRadius();
	if (endl) std::cout << std::endl;
}

bool circle::isEqual(const circle& other) {
	return (_centre.isEqual(other._centre) && _radius == other._radius);
}

double circle::distanceBetweenCentres(const circle& other) {
	return _centre.distanceBetween(other._centre);
}

point circle::getCentre() const {
	return _centre;
}
int circle::getCentreCordX() const {
	return _centre.getCordX();
}
int circle::getCentreCordY() const {
	return _centre.getCordY();
}
int circle::getRadius() const {
	return _radius;
}
int circle::getDiameter() const {
	return _radius * 2;
}