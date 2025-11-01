#include <gtest/gtest.h>

#include "../lib_queue/queue.h"

TEST(QueueTest, DefaultConstructor) {
	Queue<int> q;
	EXPECT_EQ(q.isEmpty(), true);
	EXPECT_EQ(q.isFull(), false);
	EXPECT_EQ(q.size(), 0);
	EXPECT_EQ(q.capacity(), QUEUE_DEFAULT_SIZE);
	ASSERT_ANY_THROW(q.head());
	ASSERT_ANY_THROW(q.tail());
}

TEST(QueueTest, ZeroSizeConstructor) {
	ASSERT_ANY_THROW(Queue<int> s(0));
}

TEST(QueueTest, SizeConstructor) {
	Queue<int> q(10);
	EXPECT_EQ(q.isEmpty(), true);
	EXPECT_EQ(q.isFull(), false);
	EXPECT_EQ(q.size(), 0);
	EXPECT_EQ(q.capacity(), 10);
	ASSERT_ANY_THROW(q.head());
	ASSERT_ANY_THROW(q.tail());
}

TEST(QueueTest, SizeValueConstructor) {
	Queue<int> q(10, 5);
	EXPECT_EQ(q.isEmpty(), false);
	EXPECT_EQ(q.isFull(), true);
	EXPECT_EQ(q.size(), 10);
	EXPECT_EQ(q.capacity(), 10);
	EXPECT_EQ(q.head(), 5);
	EXPECT_EQ(q.tail(), 5);
}

TEST(QueueTest, TVectorConstructor) {
	TVector<int> vec({ 2, 7, 45, -7 });
	Queue<int> q(vec);
	EXPECT_EQ(q.isEmpty(), false);
	EXPECT_EQ(q.isFull(), true);
	EXPECT_EQ(q.size(), 4);
	EXPECT_EQ(q.capacity(), 4);
	EXPECT_EQ(q.head(), 2);
	EXPECT_EQ(q.tail(), -7);
}

TEST(QueueTest, InitListConstructor) {
	Queue<int> q({ 2, 7, 45, -3 });
	EXPECT_EQ(q.isEmpty(), false);
	EXPECT_EQ(q.isFull(), true);
	EXPECT_EQ(q.size(), 4);
	EXPECT_EQ(q.capacity(), 4);
	EXPECT_EQ(q.head(), 2);
	EXPECT_EQ(q.tail(), -3);
}

TEST(QueueTest, CopyConstructor) {
	Queue<int> q1({ 9, 0, 0, 6 });
	Queue<int> q2(q1);
	EXPECT_EQ(q2.isEmpty(), false);
	EXPECT_EQ(q2.isFull(), true);
	EXPECT_EQ(q2.size(), 4);
	EXPECT_EQ(q2.capacity(), 4);
	EXPECT_EQ(q2.head(), 9);
	EXPECT_EQ(q2.tail(), 6);

	q1.pop();
	EXPECT_EQ(q2.head(), 9);
	EXPECT_EQ(q2.size(), 4);
	EXPECT_EQ(q2.capacity(), 4);
}

TEST(QueueTest, AssignQueue) {
	Queue<int> q2({ 1, 2, 5, 4 });
	Queue<int> q1;
	q1.assign(q2);
	EXPECT_EQ(q1.isEmpty(), false);
	EXPECT_EQ(q1.isFull(), true);
	EXPECT_EQ(q1.size(), 4);
	EXPECT_EQ(q1.capacity(), 4);
	EXPECT_EQ(q1.head(), 1);
	EXPECT_EQ(q1.tail(), 4);

	q2.pop();
	EXPECT_EQ(q1.head(), 1);
	EXPECT_EQ(q1.tail(), 4);
	EXPECT_EQ(q1.size(), 4);
	EXPECT_EQ(q1.capacity(), 4);
}

TEST(QueueTest, AssignTVector) {
	TVector<int> data({5, 6, 3, 2, 1, 7});
	Queue<int> q2({ 5, 6, 3, 2, 1, 7 });
	Queue<int> q1;
	q1.assign(data);
	EXPECT_EQ(q1.isEmpty(), false);
	EXPECT_EQ(q1.isFull(), true);
	EXPECT_EQ(q1.size(), 6);
	EXPECT_EQ(q1.capacity(), 6);
	EXPECT_EQ(q1.head(), 5);
	EXPECT_EQ(q1.tail(), 7);

	data.pop_back();
	EXPECT_EQ(q1.head(), 5);
	EXPECT_EQ(q1.tail(), 7);
	EXPECT_EQ(q1.size(), 6);
	EXPECT_EQ(q1.capacity(), 6);
}

TEST(QueueTest, ToTVector) {
	TVector<int> data({ 1, 2, -3, 40 });
	Queue<int> q({ 1, 2, -3, 40 });
	TVector<int> vec;
	vec = q.toTVector();
	EXPECT_TRUE(vec == data);
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
	Queue<int> q({ 4, 7, -13 });
	q.pop();
	EXPECT_EQ(q.isEmpty(), false);
	EXPECT_EQ(q.isFull(), false);
	EXPECT_EQ(q.tail(), -13);
	EXPECT_EQ(q.head(), 7);
}

TEST(QueueTest, Clear) {
	Queue<int> q({ 176, -45, 8 });
	q.clear();
	EXPECT_EQ(q.isEmpty(), true);
	EXPECT_EQ(q.isFull(), false);
}

TEST(QueueTest, IsEmpty) {
	Queue<int> q;
	EXPECT_EQ(q.isEmpty(), true);
}

TEST(QueueTest, IsNotEmpty) {
	Queue<int> q({ 13, 51 });
	EXPECT_EQ(q.isEmpty(), false);
	q.pop();
	EXPECT_EQ(q.isEmpty(), false);
	q.pop();
	EXPECT_EQ(q.isEmpty(), true);
}

TEST(QueueTest, IsFull) {
	Queue<int> q({ -94, 13 });
	EXPECT_EQ(q.isFull(), true);
	q.pop();
	EXPECT_EQ(q.isFull(), false);
	q.pop();
	EXPECT_EQ(q.isFull(), false);
}

TEST(QueueTest, IsNotFull) {
	Queue<int> q({ 6, 66, 777 });
	EXPECT_EQ(q.isFull(), true);
	q.pop();
	EXPECT_EQ(q.isFull(), false);
	q.pop();
	EXPECT_EQ(q.isFull(), false);
}
