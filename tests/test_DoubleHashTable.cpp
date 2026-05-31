#include <gtest/gtest.h>

#include "../table_double_hash_table/DoubleHashTable.h"

TEST(DoubleHashTableTest, CreateEmptyTable) {
    DoubleHashTable<int> table;
    EXPECT_TRUE(table.isEmpty());
    EXPECT_EQ(0, table.size());
    EXPECT_EQ(nullptr, table.find("key"));
    EXPECT_FALSE(table.contains("key"));
    EXPECT_FALSE(table.isFull());
    EXPECT_GT(table.capacity(), 0);
}

TEST(DoubleHashTableTest, InsertAndFind) {
    DoubleHashTable<std::string> table(10);

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

TEST(DoubleHashTableTest, InsertDuplicateKey) {
    DoubleHashTable<double> table;

    table.insert("test", 1);
    EXPECT_ANY_THROW(table.insert("test", 2));
}


TEST(DoubleHashTableTest, EraseElement) {
    DoubleHashTable<int> table;

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

TEST(DoubleHashTableTest, EraseNonExistentKey) {
    DoubleHashTable<int> table;
    EXPECT_ANY_THROW(table.erase("nonexistent"));
}

TEST(DoubleHashTableTest, EraseThenFindWithCollision) {
    DoubleHashTable<int> table(5);

    table.insert("abc", 111);
    table.insert("cba", 222);
    table.insert("bac", 333);

    table.erase("cba");
    EXPECT_FALSE(table.contains("cba"));

    EXPECT_TRUE(table.contains("abc"));
    EXPECT_TRUE(table.contains("bac"));
    EXPECT_EQ(111, *table.find("abc"));
    EXPECT_EQ(333, *table.find("bac"));

    table.insert("cba", 444);
    EXPECT_TRUE(table.contains("cba"));
    EXPECT_EQ(444, *table.find("cba"));
    EXPECT_EQ(3, table.size());
}

TEST(DoubleHashTableTest, ReuseDeletedSlot) {
    DoubleHashTable<std::string> table(5);

    table.insert("first", "value1");
    table.erase("first");

    table.insert("second", "value2");
    EXPECT_TRUE(table.contains("second"));
    EXPECT_FALSE(table.contains("first"));
    EXPECT_EQ("value2", *table.find("second"));
    EXPECT_EQ(1, table.size());
}

TEST(DoubleHashTableTest, FullTable) {
    DoubleHashTable<int> table(3);

    table.insert("a", 1);
    table.insert("b", 2);
    table.insert("c", 3);

    EXPECT_EQ(3, table.size());
    EXPECT_TRUE(table.isFull());

    EXPECT_ANY_THROW(table.insert("d", 4));
}

TEST(DoubleHashTableTest, CopyConstructor) {
    DoubleHashTable<int> table1;
    table1.insert("x", 10);
    table1.insert("y", 20);

    DoubleHashTable<int> table2(table1);

    EXPECT_TRUE(table2.contains("x"));
    EXPECT_TRUE(table2.contains("y"));
    EXPECT_EQ(10, *table2.find("x"));
    EXPECT_EQ(20, *table2.find("y"));

    table2.insert("z", 30);
    EXPECT_FALSE(table1.contains("z"));
    EXPECT_EQ(2, table1.size());
    EXPECT_EQ(3, table2.size());
}

TEST(DoubleHashTableTest, DoubleHashingResolvesCollisions) {
    DoubleHashTable<int> table(5);

    table.insert("abc", 1);
    table.insert("cba", 2);
    table.insert("acb", 3);
    table.insert("bac", 4);

    EXPECT_TRUE(table.contains("abc"));
    EXPECT_TRUE(table.contains("cba"));
    EXPECT_TRUE(table.contains("acb"));
    EXPECT_TRUE(table.contains("bac"));

    EXPECT_EQ(1, *table.find("abc"));
    EXPECT_EQ(2, *table.find("cba"));
    EXPECT_EQ(3, *table.find("acb"));
    EXPECT_EQ(4, *table.find("bac"));
    EXPECT_EQ(4, table.size());
    EXPECT_FALSE(table.isFull());
}

TEST(DoubleHashTableTest, SearchPassesThroughDeleted) {
    DoubleHashTable<std::string> table(10);

    table.insert("first", "val1");
    table.insert("second", "val2");
    table.insert("third", "val3");

    table.erase("first");

    auto* val3 = table.find("third");
    ASSERT_NE(nullptr, val3);
    EXPECT_EQ("val3", *val3);
}

TEST(DoubleHashTableTest, ContainsAndSize) {
    DoubleHashTable<char> table;
    EXPECT_FALSE(table.contains("anything"));
    table.insert("a", 'A');
    EXPECT_TRUE(table.contains("a"));
    EXPECT_EQ(1, table.size());
    table.erase("a");
    EXPECT_FALSE(table.contains("a"));
    EXPECT_EQ(0, table.size());
}

TEST(DoubleHashTableTest, InsertAfterErase) {
    DoubleHashTable<int> table(5);
    table.insert("key1", 1);
    table.insert("key2", 2);
    table.insert("key3", 3);
    table.erase("key2");
    table.insert("key4", 4);
    EXPECT_TRUE(table.contains("key1"));
    EXPECT_FALSE(table.contains("key2"));
    EXPECT_TRUE(table.contains("key3"));
    EXPECT_TRUE(table.contains("key4"));
    EXPECT_EQ(3, table.size());
}

TEST(DoubleHashTableTest, InsertDuplicateKeyAfterDeleted) {
    DoubleHashTable<int> table(5);

    table.insert("first", 1);
    table.insert("second", 2);
    table.erase("first");

    EXPECT_ANY_THROW(table.insert("second", 3));
    EXPECT_TRUE(table.contains("second"));
    EXPECT_EQ(1, table.size());
}

TEST(DoubleHashTableTest, InsertUsesDeletedSlot) {
    DoubleHashTable<int> table(5);

    table.insert("key1", 10);
    table.insert("key2", 20);
    table.erase("key1");

    table.insert("key3", 30);

    EXPECT_TRUE(table.contains("key3"));
    EXPECT_FALSE(table.contains("key1"));
    EXPECT_EQ(2, table.size());
}

TEST(DoubleHashTableTest, CollisionResolutionByDoubleHashing) {
    DoubleHashTable<int> table(7);

    table.insert("ab", 1);
    table.insert("ba", 1);

    EXPECT_TRUE(table.contains("ab"));
    EXPECT_TRUE(table.contains("ba"));
}