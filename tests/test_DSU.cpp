#include <gtest/gtest.h>

#include "../lib_dsu/DSU.h"

TEST(DSUTest, ZeroSizeConstructor) {
    ASSERT_ANY_THROW(DSU<int> dsu(0));
}

TEST(DSUTest, SizeConstructor) {
    DSU<int> dsu(10);
    EXPECT_EQ(dsu.size(), 10);

    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(dsu.find(i), i);
    }
}

TEST(DSUTest, CopyConstructor) {
    DSU<int> dsu1(5);
    dsu1.unionSets(0, 1);
    dsu1.unionSets(2, 3);

    DSU<int> dsu2 = dsu1;

    EXPECT_TRUE(dsu2.isConnected(0, 1));
    EXPECT_TRUE(dsu2.isConnected(2, 3));
    EXPECT_FALSE(dsu2.isConnected(0, 2));

    dsu2.unionSets(1, 2);
    EXPECT_TRUE(dsu2.isConnected(0, 3));
    EXPECT_FALSE(dsu1.isConnected(0, 3));
}

TEST(DSUTest, SimpleUnionTest) {
    DSU<int> dsu(5);

    dsu.unionSets(0, 1);
    EXPECT_TRUE(dsu.isConnected(0, 1));
    EXPECT_EQ(dsu.find(0), dsu.find(1));

    dsu.unionSets(2, 3);
    EXPECT_TRUE(dsu.isConnected(2, 3));
    EXPECT_FALSE(dsu.isConnected(0, 3));
}

TEST(DSUTest, FindMethodsTests) {
    DSU<int> dsu(10);

    dsu.unionSets(0, 1);
    dsu.unionSets(1, 2);
    dsu.unionSets(3, 4);
    dsu.unionSets(4, 5);
    dsu.unionSets(0, 3);

    for (int i = 0; i < 6; i++) {
        EXPECT_EQ(dsu.find(i), dsu.findRec(i));
    }
}

TEST(DSUTest, UnionWithSelf) {
    DSU<int> dsu(5);

    dsu.unionSets(2, 2);
    EXPECT_EQ(dsu.find(2), 2);

    dsu.unionSets(2, 3);
    EXPECT_TRUE(dsu.isConnected(2, 3));
}

TEST(DSUTest, AssignmentDSU) {
    DSU<int> dsu1(5);
    dsu1.unionSets(0, 1);
    dsu1.unionSets(2, 3);

    DSU<int> dsu2(3);
    dsu2 = dsu1;

    EXPECT_EQ(dsu2.size(), 5);
    EXPECT_TRUE(dsu2.isConnected(0, 1));
    EXPECT_TRUE(dsu2.isConnected(2, 3));

    dsu2 = dsu2;
    EXPECT_TRUE(dsu2.isConnected(0, 1));
}

TEST(DSUTest, MultipleUnionsOperations) {
    DSU<int> dsu(10);

    dsu.unionSets(0, 9);
    dsu.unionSets(1, 8);
    dsu.unionSets(2, 7);
    dsu.unionSets(3, 6);
    dsu.unionSets(4, 5);

    EXPECT_TRUE(dsu.isConnected(0, 9));
    EXPECT_TRUE(dsu.isConnected(1, 8));
    EXPECT_TRUE(dsu.isConnected(2, 7));
    EXPECT_TRUE(dsu.isConnected(3, 6));
    EXPECT_TRUE(dsu.isConnected(4, 5));

    dsu.unionSets(9, 8);
    dsu.unionSets(7, 6);
    dsu.unionSets(5, 0);


    EXPECT_TRUE(dsu.isConnected(0, 1));
    EXPECT_TRUE(dsu.isConnected(2, 3));
    EXPECT_FALSE(dsu.isConnected(0, 2));
    EXPECT_FALSE(dsu.isConnected(1, 3));
    EXPECT_FALSE(dsu.isConnected(4, 6));
    EXPECT_FALSE(dsu.isConnected(5, 7));
    EXPECT_FALSE(dsu.isConnected(8, 2));
    EXPECT_FALSE(dsu.isConnected(9, 3));
}
