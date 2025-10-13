#include <gtest/gtest.h>

#include "../lib_stack/stack.h"

TEST(StackTest, DefaultConstructor) {
	stack<int> s;
	EXPECT_EQ(s.isEmpty(), true);
	EXPECT_EQ(s.isFull(), true);
}

TEST(StackTest, SizeConstructor) {
	stack<int> s(10);
	EXPECT_EQ(s.isEmpty(), true);
	EXPECT_EQ(s.isFull(), false);
	ASSERT_ANY_THROW(s.top());
}

TEST(StackTest, TVectorConstructor) {
	TVector<int> vec({2, 7, 45, -7});
	stack<int> s(vec);
	EXPECT_EQ(s.isEmpty(), false);
	EXPECT_EQ(s.isFull(), true);
	EXPECT_EQ(s.top(), -7);
}

TEST(StackTest, InitListConstructor) {
	stack<int> s({ 2, 7, 45, -88 });
	EXPECT_EQ(s.isEmpty(), false);
	EXPECT_EQ(s.isFull(), true);
	EXPECT_EQ(s.top(), -88);
}

TEST(StackTest, CopyConstructor) {
	stack<int> s1({ 9, 0, 0, 6 });
	stack<int> s2(s1);
	EXPECT_EQ(s2.isEmpty(), false);
	EXPECT_EQ(s2.isFull(), true);
	EXPECT_EQ(s2.top(), 6);

	s1.pop();
	EXPECT_EQ(s2.top(), 6);
}

TEST(StackTest, PushFromFullExeption) {
	stack<int> s({ 9, 0, 0, 6 });
	ASSERT_ANY_THROW(s.push(7));
}

TEST(StackTest, PushFromEmpty) {
	stack<int> s({2, 4});
	s.pop();
	s.pop();
	EXPECT_EQ(s.isEmpty(), true);
	s.push(10);
	EXPECT_EQ(s.top(), 10);
}

TEST(StackTest, Push) {
	stack<int> s(10);
	s.push(-12);
	EXPECT_EQ(s.isEmpty(), false);
	EXPECT_EQ(s.isFull(), false);
	EXPECT_EQ(s.top(), -12);
}

TEST(StackTest, PopFromEmpty) {
	stack<int> s;
	ASSERT_ANY_THROW(s.pop());
}

TEST(StackTest, Pop) {
	stack<int> s({4, 7, 8});
	s.pop();
	EXPECT_EQ(s.top(), 7);

	s.pop();
	EXPECT_EQ(s.top(), 4);

	s.pop();
	EXPECT_EQ(s.isEmpty(), true);
	ASSERT_ANY_THROW(s.top());
}

TEST(StackTest, Clear) {
	stack<int> s({ 4, 7, 8 });
	s.clear();
	EXPECT_EQ(s.isEmpty(), true);
	EXPECT_EQ(s.isFull(), false);
}

TEST(StackTest, TopExeption) {
	stack<int> s({2});
	EXPECT_EQ(s.top(), 2);
	s.pop();
	ASSERT_ANY_THROW(s.top());
}

TEST(StackTest, Top) {
	stack<int> s(5);
	s.push(2);
	EXPECT_EQ(s.top(), 2);
	s.push(8);
	EXPECT_EQ(s.top(), 8);
	s.push(14);
	EXPECT_EQ(s.top(), 14);
}

TEST(StackTest, IsEmpty) {
	stack<int> s;
	EXPECT_EQ(s.isEmpty(), true);
}

TEST(StackTest, IsNotEmpty) {
	stack<int> s({1, 4});
	EXPECT_EQ(s.isEmpty(), false);
	s.pop();
	EXPECT_EQ(s.isEmpty(), false);
	s.pop();
	EXPECT_EQ(s.isEmpty(), true);
}

TEST(StackTest, IsFull) {
	stack<int> s({-8, 8});
	EXPECT_EQ(s.isFull(), true);
	s.pop();
	EXPECT_EQ(s.isFull(), false);
	s.pop();
	EXPECT_EQ(s.isFull(), false);
}

TEST(StackTest, IsNotFull) {
	stack<int> s({ 1, 4, 88});
	EXPECT_EQ(s.isFull(), true);
	s.pop();
	EXPECT_EQ(s.isFull(), false);
	s.pop();
	EXPECT_EQ(s.isFull(), false);
}
