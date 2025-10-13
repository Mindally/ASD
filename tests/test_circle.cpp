#include <gtest/gtest.h>

#include "../lib_point/point.h"
#include "../lib_circle/circle.h"

TEST(CircleTest, DefaultConstructor) {
	circle c;
	EXPECT_EQ(c.getCentreCordX(), 0);
	EXPECT_EQ(c.getCentreCordY(), 0);
	EXPECT_EQ(c.getRadius(), 1);
}

TEST(CircleTest, ParameterizedConstructor) {
    point p(10, 20);
    circle c(p, 15);
    EXPECT_EQ(c.getCentreCordX(), 10);
    EXPECT_EQ(c.getCentreCordY(), 20);
    EXPECT_EQ(c.getRadius(), 15);
}

TEST(CircleTest, CopyConstructor) {
    circle c1(10, 20, 15);
    circle c2(c1);
    EXPECT_EQ(c1.isEqual(c2), true);
}

TEST(CircleTest, SetPoint) {
    circle c;
    point p(20, 20);
    c.setPoint(p);
    EXPECT_EQ(c.getCentreCordX(), 20);
    EXPECT_EQ(c.getCentreCordY(), 20);
}

TEST(CircleTest, SetCordsCentre) {
    circle c;
    c.setCordsCentre(20, 10);
    EXPECT_EQ(c.getCentreCordX(), 20);
    EXPECT_EQ(c.getCentreCordY(), 10);
}

TEST(CircleTest, SetRadiusValid) {
    circle c;
    c.setRadius(5);
    EXPECT_EQ(c.getRadius(), 5);
}

TEST(CircleTest, SetRadiusThrowsException) {
    circle c;
    EXPECT_THROW(c.setRadius(-5), std::invalid_argument);
}

TEST(CircleTest, AssignOtherCircle) {
    circle c1;
    circle c2(10, 0, 10);
    c1.assign(c2);
    EXPECT_EQ(c1.isEqual(c2), true);
}

TEST(CircleTest, DistanceBetweenCentres) {
    circle c1(0, 0, 1);
    circle c2(2, 0, 1);
    EXPECT_EQ(c1.distanceBetweenCentres(c2), 2);
}