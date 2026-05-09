#include <gtest/gtest.h>
#include "../table_unsorted_table_on_array/UnsortedOnArray.h"

TEST(UnsortedTableOnArrayTest, InsertAndFind) {
    UnsortedTableOnArray<int, std::string> table;
    table.insert(10, "ten");
    table.insert(20, "twenty");
    table.insert(5, "five");

    auto* val = table.find(20);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, "twenty");

    val = table.find(5);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, "five");

    EXPECT_EQ(table.find(42), nullptr);
}

TEST(UnsortedTableOnArrayTest, UpdateValue) {
    UnsortedTableOnArray<std::string, int> table;
    table.insert("apple", 100);
    table.insert("banana", 200);

    table.insert("apple", 999);

    auto* val = table.find("apple");
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, 999);
    val = table.find("banana");
    EXPECT_EQ(*val, 200);
}

TEST(UnsortedTableOnArrayTest, EraseKey) {
    UnsortedTableOnArray<char, double> table;
    table.insert('A', 1.5);
    table.insert('B', 2.5);
    table.insert('C', 3.5);

    table.erase('B');
    EXPECT_EQ(table.find('B'), nullptr);
    EXPECT_NE(table.find('A'), nullptr);
    EXPECT_NE(table.find('C'), nullptr);

    table.erase('Z');

    table.erase('A');
    table.erase('C');
    EXPECT_TRUE(table.isEmpty());
}

TEST(UnsortedTableOnArrayTest, CheckEmpty) {
    UnsortedTableOnArray<int, bool> table;
    EXPECT_TRUE(table.isEmpty());

    table.insert(1, true);
    EXPECT_FALSE(table.isEmpty());

    table.erase(1);
    EXPECT_TRUE(table.isEmpty());
}

TEST(UnsortedTableOnArrayTest, TestPointer) {
    UnsortedTableOnArray<int, int> table;
    table.insert(42, 100);

    int* ptr = table.find(42);
    ASSERT_NE(ptr, nullptr);
    *ptr = 500;

    auto* check = table.find(42);
    EXPECT_EQ(*check, 500);
}

TEST(UnsortedTableOnArrayTest, ContainsKey) {
    UnsortedTableOnArray<double, std::string> table;
    table.insert(3.14, "pi");
    table.insert(2.71, "e");

    EXPECT_TRUE(table.contains(3.14));
    EXPECT_TRUE(table.contains(2.71));
    EXPECT_FALSE(table.contains(1.0));
    EXPECT_FALSE(table.contains(0.0));
}

TEST(UnsortedTableOnArrayTest, InsertAfterErase) {
    UnsortedTableOnArray<int, int> table;
    table.insert(1, 1);
    table.insert(2, 2);
    table.insert(3, 3);
    table.erase(2);
    table.insert(4, 4);

    EXPECT_TRUE(table.contains(1));
    EXPECT_FALSE(table.contains(2));
    EXPECT_TRUE(table.contains(3));
    EXPECT_TRUE(table.contains(4));
    EXPECT_EQ(*table.find(4), 4);
}