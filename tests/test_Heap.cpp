#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "../lib_heap/Heap.h"
#include "../lib_tvector/TVector.h"

TEST(HeapTest, DefaultConstructor) {
    Heap<int, std::string> heap;
    EXPECT_TRUE(heap.isEmpty());
    EXPECT_EQ(heap.size(), 0);
    EXPECT_ANY_THROW(heap.top());
    EXPECT_ANY_THROW(heap.extract());
}

TEST(HeapTest, InsertAndTop) {
    Heap<int, std::string> heap;
    heap.insert(5, "five");
    EXPECT_FALSE(heap.isEmpty());
    EXPECT_EQ(heap.size(), 1);
    auto top = heap.top();
    EXPECT_EQ(top.first, 5);
    EXPECT_EQ(top.second, "five");
}

TEST(HeapTest, InsertAndTopEqualKeys) {
    Heap<int, std::string> heap;
    heap.insert(1, "first");
    heap.insert(1, "second");
    heap.insert(1, "third");
    EXPECT_EQ(heap.size(), 3);
    auto top = heap.top();
    EXPECT_EQ(top.first, 1);
    EXPECT_EQ(top.second, "first");
}

TEST(HeapTest, ExtractInOrder) {
    Heap<int, int> heap;
    TVector<int> keys({ 5, 2, 8, 1, 9, 3 });
    for (int k : keys) {
        heap.insert(k, k * 10);
    }

    TVector<int> extracted;
    while (!heap.isEmpty()) {
        extracted.push_back(heap.extract().first);
    }

    TVector<int> expected({ 1, 2, 3, 5, 8, 9 });
    EXPECT_EQ(extracted, expected);
}

TEST(HeapTest, ExtractFromEmpty) {
    Heap<int, int> heap;
    EXPECT_ANY_THROW(heap.extract());
    EXPECT_ANY_THROW(heap.top());
}

TEST(HeapTest, TopAfterExtract) {
    Heap<int, int> heap;
    heap.insert(10, 100);
    heap.insert(5, 50);
    heap.extract();
    heap.extract();
    EXPECT_ANY_THROW(heap.top());
    EXPECT_ANY_THROW(heap.extract());
}