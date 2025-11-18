#include <gtest/gtest.h>

#include "../lib_list_based_queue/ListBasedQueue.h"
#include "../lib_queue/Queue.h"

TEST(ListBasedQueueTest, DefaultConstructor) {
	ListBasedQueue<int> q;
	EXPECT_EQ(q.isEmpty(), true);
	EXPECT_EQ(q.isFull(), false);
	EXPECT_EQ(q.size(), 0);
	EXPECT_EQ(q.capacity(), QUEUE_DEFAULT_SIZE);
	ASSERT_ANY_THROW(q.head());
	ASSERT_ANY_THROW(q.tail());
}

TEST(ListBasedQueueTest, ZeroSizeConstructor) {
	ASSERT_ANY_THROW(ListBasedQueue<int> s(0));
}

TEST(ListBasedQueueTest, SizeConstructor) {
	ListBasedQueue<int> q(10);
	EXPECT_EQ(q.isEmpty(), true);
	EXPECT_EQ(q.isFull(), false);
	EXPECT_EQ(q.size(), 0);
	EXPECT_EQ(q.capacity(), 10);
	ASSERT_ANY_THROW(q.head());
	ASSERT_ANY_THROW(q.tail());
}

TEST(ListBasedQueueTest, SizeValueConstructor) {
	ListBasedQueue<int> q(10, 5);
	EXPECT_EQ(q.isEmpty(), false);
	EXPECT_EQ(q.isFull(), true);
	EXPECT_EQ(q.size(), 10);
	EXPECT_EQ(q.capacity(), 10);
	EXPECT_EQ(q.head(), 5);
	EXPECT_EQ(q.tail(), 5);
}

TEST(ListBasedQueueTest, TVectorConstructor) {
	TVector<int> vec({ 2, 7, 45, -7 });
	ListBasedQueue<int> q(vec);
	EXPECT_EQ(q.isEmpty(), false);
	EXPECT_EQ(q.isFull(), true);
	EXPECT_EQ(q.size(), 4);
	EXPECT_EQ(q.capacity(), 4);
	EXPECT_EQ(q.head(), 2);
	EXPECT_EQ(q.tail(), -7);
}

TEST(ListBasedQueueTest, InitListConstructor) {
	ListBasedQueue<int> q({ 2, 7, 45, -3 });
	EXPECT_EQ(q.isEmpty(), false);
	EXPECT_EQ(q.isFull(), true);
	EXPECT_EQ(q.size(), 4);
	EXPECT_EQ(q.capacity(), 4);
	EXPECT_EQ(q.head(), 2);
	EXPECT_EQ(q.tail(), -3);
}

TEST(ListBasedQueueTest, CopyConstructor) {
	ListBasedQueue<int> q1({ 9, 0, 0, 6 });
	ListBasedQueue<int> q2(q1);
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

TEST(ListBasedQueueTest, AssignListBasedQueue) {
	ListBasedQueue<int> q2({ 1, 2, 5, 4 });
	ListBasedQueue<int> q1;
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

TEST(ListBasedQueueTest, AssignTVector) {
	TVector<int> data({5, 6, 3, 2, 1, 7});
	ListBasedQueue<int> q2({ 5, 6, 3, 2, 1, 7 });
	ListBasedQueue<int> q1;
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

TEST(ListBasedQueueTest, ToTVector) {
	TVector<int> data({ 1, 2, -3, 40 });
	ListBasedQueue<int> q({ 1, 2, -3, 40 });
	TVector<int> vec;
	vec = q.toTVector();
	EXPECT_TRUE(vec == data);
}

TEST(ListBasedQueueTest, ToQueue) {
	ListBasedQueue<int> q({ 1, 2, 3 });
	Queue<int> result;
	result = q.toQueue();
	EXPECT_EQ(result.head(), 1);
	EXPECT_EQ(result.tail(), 3);
}

TEST(ListBasedQueueTest, PushFromFullExeption) {
	ListBasedQueue<int> q({ 9, 0, 0, 6 });
	ASSERT_ANY_THROW(q.push(7));
}

TEST(ListBasedQueueTest, PushFromEmpty) {
	ListBasedQueue<int> q({ 2, 4 });
	q.pop();
	q.pop();
	EXPECT_EQ(q.isEmpty(), true);
	q.push(10);
	EXPECT_EQ(q.isEmpty(), false);
}

TEST(ListBasedQueueTest, Push) {
	ListBasedQueue<int> q(10);
	q.push(-12);
	EXPECT_EQ(q.isEmpty(), false);
	EXPECT_EQ(q.isFull(), false);
}

TEST(ListBasedQueueTest, PopFromEmpty) {
	ListBasedQueue<int> q;
	ASSERT_ANY_THROW(q.pop());
}

TEST(ListBasedQueueTest, Pop) {
	ListBasedQueue<int> q({ 4, 7, -13 });
	q.pop();
	EXPECT_EQ(q.isEmpty(), false);
	EXPECT_EQ(q.isFull(), false);
	EXPECT_EQ(q.tail(), -13);
	EXPECT_EQ(q.head(), 7);
}

TEST(ListBasedQueueTest, Clear) {
	ListBasedQueue<int> q({ 176, -45, 8 });
	q.clear();
	EXPECT_EQ(q.isEmpty(), true);
	EXPECT_EQ(q.isFull(), false);
}

TEST(ListBasedQueueTest, ReserveLessElements) {
	ListBasedQueue<int> q({ 4, 7, 8 });
	EXPECT_EQ(q.isEmpty(), false);
	EXPECT_EQ(q.isFull(), true);
	EXPECT_EQ(q.tail(), 8);
	EXPECT_EQ(q.head(), 4);
	EXPECT_EQ(q.size(), 3);
	EXPECT_EQ(q.capacity(), 3);

	q.reserve(1);

	EXPECT_EQ(q.isEmpty(), false);
	EXPECT_EQ(q.isFull(), true);
	EXPECT_EQ(q.tail(), 8);
	EXPECT_EQ(q.head(), 4);
	EXPECT_EQ(q.size(), 3);
	EXPECT_EQ(q.capacity(), 3);
}

TEST(ListBasedQueueTest, ReserveMoreElements) {
	ListBasedQueue<int> q({ 1, 2, 3 });
	EXPECT_EQ(q.isEmpty(), false);
	EXPECT_EQ(q.isFull(), true);
	EXPECT_EQ(q.tail(), 3);
	EXPECT_EQ(q.head(), 1);
	EXPECT_EQ(q.size(), 3);
	EXPECT_EQ(q.capacity(), 3);

	q.reserve(10);

	EXPECT_EQ(q.isEmpty(), false);
	EXPECT_EQ(q.isFull(), false);
	EXPECT_EQ(q.tail(), 3);
	EXPECT_EQ(q.head(), 1);
	EXPECT_EQ(q.size(), 3);
	EXPECT_EQ(q.capacity(), 10);
}

TEST(ListBasedQueueTest, ShrinkToFitToEmptyException) {
	ListBasedQueue<int> q;
	ASSERT_ANY_THROW(q.shrinkToFit());
}

TEST(ListBasedQueueTest, ShrinkToFitFull) {
	ListBasedQueue<int> q({ 4, 7, 8 });
	EXPECT_EQ(q.isEmpty(), false);
	EXPECT_EQ(q.isFull(), true);
	EXPECT_EQ(q.tail(), 8);
	EXPECT_EQ(q.head(), 4);
	EXPECT_EQ(q.size(), 3);
	EXPECT_EQ(q.capacity(), 3);

	q.shrinkToFit();

	EXPECT_EQ(q.isEmpty(), false);
	EXPECT_EQ(q.isFull(), true);
	EXPECT_EQ(q.tail(), 8);
	EXPECT_EQ(q.head(), 4);
	EXPECT_EQ(q.size(), 3);
	EXPECT_EQ(q.capacity(), 3);
}

TEST(ListBasedQueueTest, ShrinkToFit) {
	ListBasedQueue<int> q({ 4, 7, 8 });
	EXPECT_EQ(q.isEmpty(), false);
	EXPECT_EQ(q.isFull(), true);
	EXPECT_EQ(q.tail(), 8);
	EXPECT_EQ(q.head(), 4);
	EXPECT_EQ(q.size(), 3);
	EXPECT_EQ(q.capacity(), 3);

	q.pop();
	q.pop();
	q.shrinkToFit();

	EXPECT_EQ(q.isEmpty(), false);
	EXPECT_EQ(q.isFull(), true);
	EXPECT_EQ(q.tail(), 8);
	EXPECT_EQ(q.head(), 8);
	EXPECT_EQ(q.size(), 1);
	EXPECT_EQ(q.capacity(), 1);
}

TEST(ListBasedQueueTest, IsEmpty) {
	ListBasedQueue<int> q;
	EXPECT_EQ(q.isEmpty(), true);
}

TEST(ListBasedQueueTest, IsNotEmpty) {
	ListBasedQueue<int> q({ 13, 51 });
	EXPECT_EQ(q.isEmpty(), false);
	q.pop();
	EXPECT_EQ(q.isEmpty(), false);
	q.pop();
	EXPECT_EQ(q.isEmpty(), true);
}

TEST(ListBasedQueueTest, IsFull) {
	ListBasedQueue<int> q({ -94, 13 });
	EXPECT_EQ(q.isFull(), true);
	q.pop();
	EXPECT_EQ(q.isFull(), false);
	q.pop();
	EXPECT_EQ(q.isFull(), false);
}

TEST(ListBasedQueueTest, IsNotFull) {
	ListBasedQueue<int> q({ 6, 66, 777 });
	EXPECT_EQ(q.isFull(), true);
	q.pop();
	EXPECT_EQ(q.isFull(), false);
	q.pop();
	EXPECT_EQ(q.isFull(), false);
}
