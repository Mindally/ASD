#include "../lib_point/point.h"
#include <iostream>
#include <cmath>
#pragma once
class circle
{
	point _centre;
	int _radius;
public:
	circle();
	circle(point, int);
	circle(int, int, int);
	circle(const circle&);

	void setPoint(point);
	void setCordsCentre(int, int);
	void setRadius(int);

	void assign(const circle&);
	void consolePrint(bool);
	bool isEqual(const circle&);
	double distanceBetweenCentres(const circle&);

	point getCentre() const;
	int getCentreCordX() const;
	int getCentreCordY() const;
	int getRadius() const;
	int getDiameter() const;

};

