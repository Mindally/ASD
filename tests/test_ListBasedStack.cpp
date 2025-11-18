#include <gtest/gtest.h>

#include "../lib_list_based_stack/ListBasedStack.h"

TEST(ListBasedStackTest, DefaultConstructor) {
	ListBasedStack<int> s;
	EXPECT_EQ(s.isEmpty(), true);
	EXPECT_EQ(s.isFull(), false);
	EXPECT_EQ(s.size(), 0);
	EXPECT_EQ(s.capacity(), STACK_DEFAULT_SIZE);
	ASSERT_ANY_THROW(s.top());
}

TEST(ListBasedStackTest, ZeroSizeConstructor) {
	ASSERT_ANY_THROW(ListBasedStack<int> s(0));
}

TEST(ListBasedStackTest, SizeConstructor) {
	ListBasedStack<int> s(10);
	EXPECT_EQ(s.isEmpty(), true);
	EXPECT_EQ(s.isFull(), false);
	EXPECT_EQ(s.size(), 0);
	EXPECT_EQ(s.capacity(), 10);
	ASSERT_ANY_THROW(s.top());
}

TEST(ListBasedStackTest, SizeValueConstructor) {
	ListBasedStack<int> s(10, 5);
	EXPECT_EQ(s.isEmpty(), false);
	EXPECT_EQ(s.isFull(), true);
	EXPECT_EQ(s.size(), 10);
	EXPECT_EQ(s.capacity(), 10);
	EXPECT_EQ(s.top(), 5);
}

TEST(ListBasedStackTest, TVectorConstructor) {
	TVector<int> vec({2, 7, 45, -7});
	ListBasedStack<int> s(vec);
	EXPECT_EQ(s.isEmpty(), false);
	EXPECT_EQ(s.isFull(), true);
	EXPECT_EQ(s.size(), 4);
	EXPECT_EQ(s.capacity(), 4);
	EXPECT_EQ(s.top(), -7);
}

TEST(ListBasedStackTest, InitListConstructor) {
	ListBasedStack<int> s({ 2, 7, 45, -8 });
	EXPECT_EQ(s.isEmpty(), false);
	EXPECT_EQ(s.isFull(), true);
	EXPECT_EQ(s.size(), 4);
	EXPECT_EQ(s.capacity(), 4);
	EXPECT_EQ(s.top(), -8);
}

TEST(ListBasedStackTest, CopyConstructor) {
	ListBasedStack<int> s1({ 9, 0, 0, 6 });
	ListBasedStack<int> s2(s1);
	EXPECT_EQ(s2.isEmpty(), false);
	EXPECT_EQ(s2.isFull(), true);
	EXPECT_EQ(s2.size(), 4);
	EXPECT_EQ(s2.capacity(), 4);
	EXPECT_EQ(s2.top(), 6);

	s1.pop();
	EXPECT_EQ(s2.top(), 6);
}

TEST(ListBasedStackTest, AssignListBasedStack) {
	ListBasedStack<int> s1;
	ListBasedStack<int> s2({ 9, 0, 0, 6 });
	s1.assign(s2);
	EXPECT_EQ(s1.isEmpty(), false);
	EXPECT_EQ(s1.isFull(), true);
	EXPECT_EQ(s1.size(), 4);
	EXPECT_EQ(s1.capacity(), 4);
	EXPECT_EQ(s1.top(), 6);

	s2.pop();
	EXPECT_EQ(s1.top(), 6);
}

TEST(ListBasedStackTest, AssignTVector) {
	ListBasedStack<int> s1;
	TVector<int> vec({1, 2, -3, 40});
	s1.assign(vec);
	EXPECT_EQ(s1.isEmpty(), false);
	EXPECT_EQ(s1.isFull(), true);
	EXPECT_EQ(s1.size(), 4);
	EXPECT_EQ(s1.capacity(), 4);
	EXPECT_EQ(s1.top(), 40);

	vec.pop_back();
	EXPECT_EQ(s1.top(), 40);
}

TEST(ListBasedStackTest, ToTVector) {
	TVector<int> data({ 1, 2, -3, 40 });
	ListBasedStack<int> s1({ 1, 2, -3, 40 });
	TVector<int> vec;
	vec = s1.toTVector();
	EXPECT_TRUE(vec == data);
}

TEST(ListBasedStackTest, ToStack) {
	ListBasedStack<int> s({ 1, 2, 3 });
	Stack<int> result;
	result = s.toStack();
	EXPECT_EQ(result.top(), 3);
}

TEST(ListBasedStackTest, PushFromFullExeption) {
	ListBasedStack<int> s({ 9, 0, 0, 6 });
	ASSERT_ANY_THROW(s.push(7));
}

TEST(ListBasedStackTest, PushFromEmpty) {
	ListBasedStack<int> s({2, 4});
	s.pop();
	s.pop();
	EXPECT_EQ(s.isEmpty(), true);
	s.push(10);
	EXPECT_EQ(s.size(), 1);
	EXPECT_EQ(s.capacity(), 2);
	EXPECT_EQ(s.top(), 10);
}

TEST(ListBasedStackTest, Push) {
	ListBasedStack<int> s(10);
	s.push(-12);
	EXPECT_EQ(s.isEmpty(), false);
	EXPECT_EQ(s.isFull(), false);
	EXPECT_EQ(s.size(), 1);
	EXPECT_EQ(s.capacity(), 10);
	EXPECT_EQ(s.top(), -12);
}

TEST(ListBasedStackTest, PopFromEmpty) {
	ListBasedStack<int> s;
	ASSERT_ANY_THROW(s.pop());
}

TEST(ListBasedStackTest, Pop) {
	ListBasedStack<int> s({4, 7, 8});
	s.pop();
	EXPECT_EQ(s.top(), 7);

	s.pop();
	EXPECT_EQ(s.top(), 4);

	s.pop();
	EXPECT_EQ(s.isEmpty(), true);
	EXPECT_EQ(s.size(), 0);
	EXPECT_EQ(s.capacity(), 3);
	ASSERT_ANY_THROW(s.top());
}

TEST(ListBasedStackTest, Clear) {
	ListBasedStack<int> s({ 4, 7, 8 });
	s.clear();
	EXPECT_EQ(s.isEmpty(), true);
	EXPECT_EQ(s.isFull(), false);
	EXPECT_EQ(s.size(), 0);
	EXPECT_EQ(s.capacity(), 3);
}

TEST(ListBasedStackTest, ReserveLessElements) {
	ListBasedStack<int> s({ 4, 7, 8 });
	EXPECT_EQ(s.isEmpty(), false);
	EXPECT_EQ(s.isFull(), true);
	EXPECT_EQ(s.size(), 3);
	EXPECT_EQ(s.capacity(), 3);

	s.reserve(1);

	EXPECT_EQ(s.isEmpty(), false);
	EXPECT_EQ(s.isFull(), true);
	EXPECT_EQ(s.size(), 3);
	EXPECT_EQ(s.capacity(), 3);
}

TEST(ListBasedStackTest, ReserveMoreElements) {
	ListBasedStack<int> s({ 1, 2, 3 });
	EXPECT_EQ(s.isEmpty(), false);
	EXPECT_EQ(s.isFull(), true);
	EXPECT_EQ(s.size(), 3);
	EXPECT_EQ(s.capacity(), 3);

	s.reserve(10);

	EXPECT_EQ(s.isEmpty(), false);
	EXPECT_EQ(s.isFull(), false);
	EXPECT_EQ(s.size(), 3);
	EXPECT_EQ(s.capacity(), 10);
}

TEST(ListBasedStackTest, ShrinkToFitToEmptyException) {
	ListBasedStack<int> s;
	ASSERT_ANY_THROW(s.shrinkToFit());
}

TEST(ListBasedStackTest, ShrinkToFitFull) {
	ListBasedStack<int> s({ 4, 7, 8 });
	EXPECT_EQ(s.isEmpty(), false);
	EXPECT_EQ(s.isFull(), true);
	EXPECT_EQ(s.size(), 3);
	EXPECT_EQ(s.capacity(), 3);

	s.shrinkToFit();

	EXPECT_EQ(s.isEmpty(), false);
	EXPECT_EQ(s.isFull(), true);
	EXPECT_EQ(s.size(), 3);
	EXPECT_EQ(s.capacity(), 3);
}

TEST(ListBasedStackTest, ShrinkToFit) {
	ListBasedStack<int> s({ 4, 7, 8 });
	EXPECT_EQ(s.isEmpty(), false);
	EXPECT_EQ(s.isFull(), true);
	EXPECT_EQ(s.size(), 3);
	EXPECT_EQ(s.capacity(), 3);

	s.pop();
	s.pop();
	s.shrinkToFit();

	EXPECT_EQ(s.isEmpty(), false);
	EXPECT_EQ(s.isFull(), true);
	EXPECT_EQ(s.size(), 1);
	EXPECT_EQ(s.capacity(), 1);
}

TEST(ListBasedStackTest, TopExeption) {
	ListBasedStack<int> s({2});
	EXPECT_EQ(s.top(), 2);
	s.pop();
	ASSERT_ANY_THROW(s.top());
}

TEST(ListBasedStackTest, Top) {
	ListBasedStack<int> s(5);
	s.push(2);
	EXPECT_EQ(s.top(), 2);
	s.push(3);
	EXPECT_EQ(s.top(), 3);
	s.push(4);
	EXPECT_EQ(s.top(), 4);
}

TEST(ListBasedStackTest, IsEmpty) {
	ListBasedStack<int> s;
	EXPECT_EQ(s.isEmpty(), true);
}

TEST(ListBasedStackTest, IsNotEmpty) {
	ListBasedStack<int> s({-57, 4});
	EXPECT_EQ(s.isEmpty(), false);
	s.pop();
	EXPECT_EQ(s.isEmpty(), false);
	s.pop();
	EXPECT_EQ(s.isEmpty(), true);
}

TEST(ListBasedStackTest, IsFull) {
	ListBasedStack<int> s({-1, 6});
	EXPECT_EQ(s.isFull(), true);
	s.pop();
	EXPECT_EQ(s.isFull(), false);
	s.pop();
	EXPECT_EQ(s.isFull(), false);
}

TEST(ListBasedStackTest, IsNotFull) {
	ListBasedStack<int> s({ 1, 7, -46});
	EXPECT_EQ(s.isFull(), true);
	s.pop();
	EXPECT_EQ(s.isFull(), false);
	s.pop();
	EXPECT_EQ(s.isFull(), false);
}
