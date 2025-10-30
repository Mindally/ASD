#include <gtest/gtest.h>

#include "../lib_queue/queue.h"

TEST(QueueTest, DefaultConstructor) {
	Queue<int> q;
	EXPECT_EQ(q.isEmpty(), true);
	EXPECT_EQ(q.isFull(), false);
	ASSERT_ANY_THROW(q.head());
	ASSERT_ANY_THROW(q.tail());
}

TEST(QueuekTest, SizeConstructor) {
	Queue<int> q(10);
	EXPECT_EQ(q.isEmpty(), true);
	EXPECT_EQ(q.isFull(), false);
	ASSERT_ANY_THROW(q.head());
	ASSERT_ANY_THROW(q.tail());
}

TEST(QueueTest, TVectorConstructor) {
	TVector<int> vec({ 2, 7, 45, -7 });
	Queue<int> q(vec);
	EXPECT_EQ(q.isEmpty(), false);
	EXPECT_EQ(q.isFull(), true);
	EXPECT_EQ(q.head(), 2);
	EXPECT_EQ(q.tail(), -7);
}

TEST(QueueTest, InitListConstructor) {
	Queue<int> q({ 2, 7, 45, -88 });
	EXPECT_EQ(q.isEmpty(), false);
	EXPECT_EQ(q.isFull(), true);
	EXPECT_EQ(q.head(), 2);
	EXPECT_EQ(q.tail(), -88);
}

TEST(QueueTest, CopyConstructor) {
	Queue<int> s1({ 9, 0, 0, 6 });
	Queue<int> s2(s1);
	EXPECT_EQ(s2.isEmpty(), false);
	EXPECT_EQ(s2.isFull(), true);
	EXPECT_EQ(s2.head(), 9);
	EXPECT_EQ(s2.tail(), 6);

	s1.pop();
	EXPECT_EQ(s2.head(), 9);
}

TEST(QueueTest, PushFromFullExeption) {
	Queue<int> q({ 9, 0, 0, 6 });
	ASSERT_ANY_THROW(q.push(7));
}

TEST(QueueTest, PushFromEmpty) {
	Queue<int> q({ 2, 4 });
	q.pop();
	q.pop();
	EXPECT_EQ(q.isEmpty(), true);
	q.push(10);
	EXPECT_EQ(q.isEmpty(), false);
}

TEST(QueueTest, Push) {
	Queue<int> q(10);
	q.push(-12);
	EXPECT_EQ(q.isEmpty(), false);
	EXPECT_EQ(q.isFull(), false);
}

TEST(QueueTest, PopFromEmpty) {
	Queue<int> q;
	ASSERT_ANY_THROW(q.pop());
}

TEST(QueueTest, Pop) {
	Queue<int> q({ 4, 7, 8 });
	q.pop();
	EXPECT_EQ(q.isEmpty(), false);
	EXPECT_EQ(q.isFull(), false);
	EXPECT_EQ(q.tail(), 8);
	EXPECT_EQ(q.head(), 7);
}

TEST(QueueTest, Clear) {
	Queue<int> q({ 4, 7, 8 });
	q.clear();
	EXPECT_EQ(q.isEmpty(), true);
	EXPECT_EQ(q.isFull(), false);
}

TEST(QueueTest, IsEmpty) {
	Queue<int> q;
	EXPECT_EQ(q.isEmpty(), true);
}

TEST(QueueTest, IsNotEmpty) {
	Queue<int> q({ 1, 4 });
	EXPECT_EQ(q.isEmpty(), false);
	q.pop();
	EXPECT_EQ(q.isEmpty(), false);
	q.pop();
	EXPECT_EQ(q.isEmpty(), true);
}

TEST(QueueTest, IsFull) {
	Queue<int> q({ -8, 8 });
	EXPECT_EQ(q.isFull(), true);
	q.pop();
	EXPECT_EQ(q.isFull(), false);
	q.pop();
	EXPECT_EQ(q.isFull(), false);
}

TEST(QueueTest, IsNotFull) {
	Queue<int> q({ 1, 4, 88 });
	EXPECT_EQ(q.isFull(), true);
	q.pop();
	EXPECT_EQ(q.isFull(), false);
	q.pop();
	EXPECT_EQ(q.isFull(), false);
}
