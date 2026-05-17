#include <gtest/gtest.h>
#include "../table_unsorted_table_on_list/UnsortedOnList.h"

TEST(UnsortedTableOnListTest, InsertAndFind) {
    UnsortedTableOnList<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    auto* val = table.find(2);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, "two");

    EXPECT_EQ(table.find(4), nullptr);
}

TEST(UnsortedTableOnListTest, UpdateExistingKey) {
    UnsortedTableOnList<int, std::string> table;
    table.insert(1, "one");
    table.insert(1, "ONE");

    auto* val = table.find(1);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(*val, "ONE");
}

TEST(UnsortedTableOnListTest, Erase) {
    UnsortedTableOnList<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    table.erase(2);

    EXPECT_EQ(table.find(2), nullptr);
    EXPECT_NE(table.find(1), nullptr);
    EXPECT_NE(table.find(3), nullptr);
}

TEST(UnsortedTableOnListTest, EraseNotExist) {
    UnsortedTableOnList<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_ANY_THROW(table.erase(666));
}

TEST(UnsortedTableOnListTest, IsEmpty) {
    UnsortedTableOnList<int, std::string> table;
    EXPECT_TRUE(table.isEmpty());

    table.insert(42, "answer");
    EXPECT_FALSE(table.isEmpty());

    table.erase(42);
    EXPECT_TRUE(table.isEmpty());
}

TEST(UnsortedTableOnListTest, PointerTest) {
    UnsortedTableOnList<int, std::string> table;
    table.insert(1, "one");

    auto* val = table.find(1);
    ASSERT_NE(val, nullptr);
    *val = "modified";

    auto* check = table.find(1);
    EXPECT_EQ(*check, "modified");
}

TEST(UnsortedTableOnListTest, Contains) {
    UnsortedTableOnList<int, std::string> table;
    table.insert(100, "hundred");

    EXPECT_TRUE(table.contains(100));
    EXPECT_FALSE(table.contains(200));
}

TEST(UnsortedTableOnListTest, InsertAfterErase) {
    UnsortedTableOnList<int, int> table;
    for (int i = 1; i <= 3; ++i) table.insert(i, i);
    table.erase(2);
    table.insert(4, 4);

    EXPECT_TRUE(table.contains(1));
    EXPECT_FALSE(table.contains(2));
    EXPECT_TRUE(table.contains(3));
    EXPECT_TRUE(table.contains(4));
}

TEST(UnsortedTableOnListTest, WorksWithStringKeys) {
    UnsortedTableOnList<std::string, double> table;
    table.insert("pi", 3.14);
    table.insert("e", 2.71);

    auto* val = table.find("pi");
    ASSERT_NE(val, nullptr);
    EXPECT_DOUBLE_EQ(*val, 3.14);

    EXPECT_TRUE(table.contains("e"));
    EXPECT_FALSE(table.contains("answer"));
}