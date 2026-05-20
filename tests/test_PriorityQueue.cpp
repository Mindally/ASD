#include <gtest/gtest.h>

#include "../lib_tvector/TVector.h"
#include "../lib_priority_queue/PriorityQueue.h"

TEST(PriorityQueueTest, DefaultConstructor) {
    PriorityQueue<int, std::string> q;
    EXPECT_TRUE(q.isEmpty());
    EXPECT_EQ(q.size(), 0);
    EXPECT_ANY_THROW(q.peek());
    EXPECT_ANY_THROW(q.extract());
}

TEST(PriorityQueueTest, AddAndPeek) {
    PriorityQueue<int, std::string> q;
    q.add(5, "five");
    EXPECT_FALSE(q.isEmpty());
    EXPECT_EQ(q.size(), 1);
    auto top = q.peek();
    EXPECT_EQ(top.first, 5);
    EXPECT_EQ(top.second, "five");
}

TEST(PriorityQueueTest, AddAndExtract) {
    PriorityQueue<int, std::string> q;
    q.add(5, "five");
    auto elem = q.extract();
    EXPECT_EQ(elem.first, 5);
    EXPECT_EQ(elem.second, "five");
    EXPECT_TRUE(q.isEmpty());
}

TEST(PriorityQueueTest, StabilityForEqualKeys) {
    PriorityQueue<int, std::string> q;
    q.add(2, "A");
    q.add(1, "B");
    q.add(2, "C");
    q.add(2, "D");
    q.add(1, "E");

    TVector<std::string> extracted;
    while (!q.isEmpty()) {
        extracted.push_back(q.extract().second);
    }
    TVector<std::string> expected({ "B", "E", "A", "C", "D" });
    EXPECT_EQ(extracted, expected);
}

TEST(PriorityQueueTest, ExtractFromEmpty) {
    PriorityQueue<int, int> q;
    EXPECT_ANY_THROW(q.extract());
    EXPECT_ANY_THROW(q.peek());
}

TEST(PriorityQueueTest, PeekAfterExtracts) {
    PriorityQueue<int, int> q;
    q.add(10, 100);
    q.add(5, 50);
    q.extract();
    q.extract();
    EXPECT_ANY_THROW(q.peek());
    EXPECT_ANY_THROW(q.extract());
}