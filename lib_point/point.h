#include <cmath>
#include <iostream>
#pragma once
class point
{
	int _x, _y;
public:
	point();
	point(int, int);
	point(const point&);

	void setCords(int, int);
	void setCordX(int);
	void setCordY(int);

	void assign(const point&);
	bool isEqual(const point&);

	void consolePrint(bool);

	int getCordX() const;
	int getCordY() const;
	double distanceBetween(const point&);
};

