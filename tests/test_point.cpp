#include <gtest/gtest.h>

#include "../lib_point/point.h"

TEST(PointTest, DefaultConstructor) {
    point p;
    EXPECT_EQ(p.getCordX(), 0);
    EXPECT_EQ(p.getCordY(), 0);
}

TEST(PointTest, ParametersConstructor) {
    point p(-10, 43);
    EXPECT_EQ(p.getCordX(), -10);
    EXPECT_EQ(p.getCordY(), 43);
}

TEST(PointTest, CopyConstructor) {
    point p1(-10, 43);
    point p2(p1);
    EXPECT_EQ(p2.isEqual(p1), true);
}

TEST(PointTest, SetCordX) {
    point p;
    p.setCordX(10);
    EXPECT_EQ(p.getCordX(), 10);
}

TEST(PointTest, SetCordY) {
    point p;
    p.setCordY(-20);
    EXPECT_EQ(p.getCordY(), -20);
}

TEST(PointTest, SetCords) {
    point p;
    p.setCords(10, -20);
    EXPECT_EQ(p.getCordX(), 10);
    EXPECT_EQ(p.getCordY(), -20);
}

TEST(PointTest, Assign) {
    point p1;
    point p2(-88, 13);
    p1.assign(p2);
    EXPECT_EQ(p1.isEqual(p2), true);
}

TEST(PointTest, DistanceBetween) {
    point p1(0, 0);
    point p2(4, 0);
    EXPECT_EQ(p1.distanceBetween(p2), 4);
}