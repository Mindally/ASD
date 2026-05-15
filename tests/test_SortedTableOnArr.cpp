#include <gtest/gtest.h>
#include "../table_sorted_table_on_array/SortedOnArray.h"

TEST(SortedTableOnArrayTest, InsertAndFind) {
    SortedTableOnArray<int, std::string> table;

    table.insert(5, "five");
    table.insert(1, "one");
    table.insert(3, "three");
    table.insert(2, "two");
    table.insert(4, "four");

    EXPECT_TRUE(table.contains(1));
    EXPECT_TRUE(table.contains(2));
    EXPECT_TRUE(table.contains(3));
    EXPECT_TRUE(table.contains(4));
    EXPECT_TRUE(table.contains(5));

    EXPECT_EQ(*table.find(1), "one");
    EXPECT_EQ(*table.find(2), "two");
    EXPECT_EQ(*table.find(3), "three");
    EXPECT_EQ(*table.find(4), "four");
    EXPECT_EQ(*table.find(5), "five");

    EXPECT_FALSE(table.contains(6));
    EXPECT_EQ(table.find(6), nullptr);
}

TEST(SortedTableOnArrayTest, UpdateValue) {
    SortedTableOnArray<int, std::string> table;
    table.insert(42, "answer");
    table.insert(42, "ANSWER");

    auto* val = table.find(42);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, "ANSWER");
}

TEST(SortedTableOnArrayTest, Erase) {
    SortedTableOnArray<int, std::string> table;
    table.insert(10, "ten");
    table.insert(20, "twenty");
    table.insert(30, "thirty");

    table.erase(20);

    EXPECT_FALSE(table.contains(20));
    EXPECT_TRUE(table.contains(10));
    EXPECT_TRUE(table.contains(30));
    EXPECT_EQ(table.find(20), nullptr);
    EXPECT_EQ(*table.find(10), "ten");
}

TEST(SortedTableOnArrayTest, EraseNonexist) {
    SortedTableOnArray<int, std::string> table;
    table.insert(100, "hundred");
    table.erase(999);

    EXPECT_TRUE(table.contains(100));
    EXPECT_FALSE(table.isEmpty());
}

TEST(SortedTableOnArrayTest, Contains) {
    SortedTableOnArray<int, std::string> table;
    table.insert(7, "seven");
    table.insert(8, "eight");

    EXPECT_TRUE(table.contains(7));
    EXPECT_TRUE(table.contains(8));
    EXPECT_FALSE(table.contains(9));
}

TEST(SortedTableOnArrayTest, IsEmpty) {
    SortedTableOnArray<int, std::string> table;
    EXPECT_TRUE(table.isEmpty());

    table.insert(1, "one");
    EXPECT_FALSE(table.isEmpty());

    table.erase(1);
    EXPECT_TRUE(table.isEmpty());
}

TEST(SortedTableOnArrayTest, EmptyTable) {
    SortedTableOnArray<int, int> empty;
    EXPECT_EQ(empty.find(10), nullptr);
    EXPECT_FALSE(empty.contains(10));
    empty.erase(10);
    EXPECT_TRUE(empty.isEmpty());
}

TEST(SortedTableOnArrayTest, DifferentTypes) {
    SortedTableOnArray<std::string, int> table;
    table.insert("apple", 1);
    table.insert("grape", 26);
    table.insert("banana", 2);

    EXPECT_TRUE(table.contains("apple"));
    EXPECT_TRUE(table.contains("banana"));
    EXPECT_TRUE(table.contains("grape"));
    EXPECT_EQ(*table.find("apple"), 1);
    EXPECT_EQ(*table.find("banana"), 2);
    EXPECT_EQ(table.find("cat"), nullptr);
}

TEST(SortedTableOnArrayTest, InsertBoundaries) {
    SortedTableOnArray<int, std::string> table;
    table.insert(50, "mid");
    table.insert(10, "left");
    table.insert(90, "right");
    table.insert(30, "left-mid");
    table.insert(70, "right-mid");

    EXPECT_TRUE(table.contains(10));
    EXPECT_TRUE(table.contains(30));
    EXPECT_TRUE(table.contains(50));
    EXPECT_TRUE(table.contains(70));
    EXPECT_TRUE(table.contains(90));
    EXPECT_EQ(*table.find(30), "left-mid");
}

TEST(SortedTableOnArrayTest, EraseThenInsert) {
    SortedTableOnArray<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    table.erase(2);
    EXPECT_FALSE(table.contains(2));

    table.insert(2, "TWO");
    EXPECT_TRUE(table.contains(2));
    EXPECT_EQ(*table.find(2), "TWO");
    EXPECT_TRUE(table.contains(1));
    EXPECT_TRUE(table.contains(3));
}