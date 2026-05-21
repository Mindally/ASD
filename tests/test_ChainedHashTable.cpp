#include <gtest/gtest.h>

#include "../table_chained_hash_table/ChainedHashTable.h"

TEST(ChainedHashTableTest, CreateEmptyTable) {
    ChainedHashTable<int> table;
    EXPECT_TRUE(table.isEmpty());
    EXPECT_EQ(0, table.size());
    EXPECT_EQ(nullptr, table.find("key"));
    EXPECT_FALSE(table.contains("key"));
    EXPECT_GT(table.capacity(), 0);
    EXPECT_FALSE(table.isFull());
}

TEST(ChainedHashTableTest, InsertAndFind) {
    ChainedHashTable<std::string> table(10);

    table.insert("key1", "value1");
    table.insert("key2", "value2");

    EXPECT_FALSE(table.isEmpty());
    EXPECT_EQ(2, table.size());

    auto* val1 = table.find("key1");
    auto* val2 = table.find("key2");

    ASSERT_NE(nullptr, val1);
    ASSERT_NE(nullptr, val2);
    EXPECT_EQ("value1", *val1);
    EXPECT_EQ("value2", *val2);

    EXPECT_TRUE(table.contains("key1"));
    EXPECT_TRUE(table.contains("key2"));
}

TEST(ChainedHashTableTest, InsertDuplicateKey) {
    ChainedHashTable<double> table;

    table.insert("test", 1);
    EXPECT_ANY_THROW(table.insert("test", 2));
}

TEST(ChainedHashTableTest, EraseElement) {
    ChainedHashTable<int> table;

    table.insert("key1", 100);
    table.insert("key2", 200);

    EXPECT_TRUE(table.contains("key1"));
    EXPECT_EQ(2, table.size());

    table.erase("key1");

    EXPECT_FALSE(table.contains("key1"));
    EXPECT_TRUE(table.contains("key2"));
    EXPECT_EQ(1, table.size());
    EXPECT_EQ(nullptr, table.find("key1"));
}

TEST(ChainedHashTableTest, EraseNonExistentKey) {
    ChainedHashTable<int> table;
    EXPECT_ANY_THROW(table.erase("nonexistent"));
}

TEST(ChainedHashTableTest, HandleCollisions) {
    ChainedHashTable<std::string> table(3);

    table.insert("abc", "value1");
    table.insert("cba", "value2");
    table.insert("acb", "value3");

    EXPECT_TRUE(table.contains("abc"));
    EXPECT_TRUE(table.contains("cba"));
    EXPECT_TRUE(table.contains("acb"));

    auto* val1 = table.find("abc");
    auto* val2 = table.find("cba");
    auto* val3 = table.find("acb");

    ASSERT_NE(nullptr, val1);
    ASSERT_NE(nullptr, val2);
    ASSERT_NE(nullptr, val3);
    EXPECT_EQ("value1", *val1);
    EXPECT_EQ("value2", *val2);
    EXPECT_EQ("value3", *val3);
    EXPECT_EQ(3, table.size());
}

TEST(ChainedHashTableTest, CollisionsWithErase) {
    ChainedHashTable<int> table(3);

    table.insert("aaa", 111);
    table.insert("bbb", 222);
    table.insert("ccc", 333);

    table.erase("bbb");

    EXPECT_FALSE(table.contains("bbb"));
    EXPECT_TRUE(table.contains("aaa"));
    EXPECT_TRUE(table.contains("ccc"));
    EXPECT_EQ(2, table.size());

    auto* val1 = table.find("aaa");
    auto* val3 = table.find("ccc");
    ASSERT_NE(nullptr, val1);
    ASSERT_NE(nullptr, val3);
    EXPECT_EQ(111, *val1);
    EXPECT_EQ(333, *val3);
}

TEST(ChainedHashTableTest, InsertAfterErase) {
    ChainedHashTable<std::string> table(3);
    table.insert("first", "A");
    table.insert("second", "B");
    table.erase("first");
    table.insert("third", "C");
    EXPECT_TRUE(table.contains("second"));
    EXPECT_TRUE(table.contains("third"));
    EXPECT_FALSE(table.contains("first"));
    EXPECT_EQ(2, table.size());
}

TEST(ChainedHashTableTest, CopyConstructor) {
    ChainedHashTable<int> table1;
    table1.insert("x", 10);
    table1.insert("y", 20);

    ChainedHashTable<int> table2(table1);

    EXPECT_TRUE(table2.contains("x"));
    EXPECT_TRUE(table2.contains("y"));
    EXPECT_EQ(10, *table2.find("x"));
    EXPECT_EQ(20, *table2.find("y"));

    table2.insert("z", 30);
    EXPECT_FALSE(table1.contains("z"));
    EXPECT_EQ(2, table1.size());
    EXPECT_EQ(3, table2.size());
}

TEST(ChainedHashTableTest, ContainsAndSize) {
    ChainedHashTable<char> table;
    EXPECT_FALSE(table.contains("anything"));
    table.insert("a", 'A');
    EXPECT_TRUE(table.contains("a"));
    EXPECT_EQ(1, table.size());
    table.erase("a");
    EXPECT_FALSE(table.contains("a"));
    EXPECT_EQ(0, table.size());
}