#include <gtest/gtest.h>

#include "../lib_stack/stack.h"

TEST(StackTest, DefaultConstructor) {
	Stack<int> s;
	EXPECT_EQ(s.isEmpty(), true);
	EXPECT_EQ(s.isFull(), false);
}

TEST(StackTest, SizeConstructor) {
	Stack<int> s(10);
	EXPECT_EQ(s.isEmpty(), true);
	EXPECT_EQ(s.isFull(), false);
	ASSERT_ANY_THROW(s.top());
}

TEST(StackTest, TVectorConstructor) {
	TVector<int> vec({2, 7, 45, -7});
	Stack<int> s(vec);
	EXPECT_EQ(s.isEmpty(), false);
	EXPECT_EQ(s.isFull(), true);
	EXPECT_EQ(s.top(), -7);
}

TEST(StackTest, InitListConstructor) {
	Stack<int> s({ 2, 7, 45, -88 });
	EXPECT_EQ(s.isEmpty(), false);
	EXPECT_EQ(s.isFull(), true);
	EXPECT_EQ(s.top(), -88);
}

TEST(StackTest, CopyConstructor) {
	Stack<int> s1({ 9, 0, 0, 6 });
	Stack<int> s2(s1);
	EXPECT_EQ(s2.isEmpty(), false);
	EXPECT_EQ(s2.isFull(), true);
	EXPECT_EQ(s2.top(), 6);

	s1.pop();
	EXPECT_EQ(s2.top(), 6);
}

TEST(StackTest, AssignStack) {
	Stack<int> s1;
	Stack<int> s2({ 9, 0, 0, 6 });
	s1.assign(s2);
	EXPECT_EQ(s1.isEmpty(), false);
	EXPECT_EQ(s1.isFull(), true);
	EXPECT_EQ(s1.top(), 6);

	s2.pop();
	EXPECT_EQ(s1.top(), 6);
}

TEST(StackTest, AssignTVector) {
	Stack<int> s1;
	TVector<int> vec({1, 2, -3, 40});
	s1.assign(vec);
	EXPECT_EQ(s1.isEmpty(), false);
	EXPECT_EQ(s1.isFull(), true);
	EXPECT_EQ(s1.top(), 40);

	vec.pop_back();
	EXPECT_EQ(s1.top(), 40);
}

TEST(StackTest, ToTVector) {
	TVector<int> data({ 1, 2, -3, 40 });
	Stack<int> s1({ 1, 2, -3, 40 });
	TVector<int> vec;
	vec = s1.toTVector();
	EXPECT_TRUE(vec == data);
}

TEST(StackTest, PushFromFullExeption) {
	Stack<int> s({ 9, 0, 0, 6 });
	ASSERT_ANY_THROW(s.push(7));
}

TEST(StackTest, PushFromEmpty) {
	Stack<int> s({2, 4});
	s.pop();
	s.pop();
	EXPECT_EQ(s.isEmpty(), true);
	s.push(10);
	EXPECT_EQ(s.top(), 10);
}

TEST(StackTest, Push) {
	Stack<int> s(10);
	s.push(-12);
	EXPECT_EQ(s.isEmpty(), false);
	EXPECT_EQ(s.isFull(), false);
	EXPECT_EQ(s.top(), -12);
}

TEST(StackTest, PopFromEmpty) {
	Stack<int> s;
	ASSERT_ANY_THROW(s.pop());
}

TEST(StackTest, Pop) {
	Stack<int> s({4, 7, 8});
	s.pop();
	EXPECT_EQ(s.top(), 7);

	s.pop();
	EXPECT_EQ(s.top(), 4);

	s.pop();
	EXPECT_EQ(s.isEmpty(), true);
	ASSERT_ANY_THROW(s.top());
}

TEST(StackTest, Clear) {
	Stack<int> s({ 4, 7, 8 });
	s.clear();
	EXPECT_EQ(s.isEmpty(), true);
	EXPECT_EQ(s.isFull(), false);
}

TEST(StackTest, TopExeption) {
	Stack<int> s({2});
	EXPECT_EQ(s.top(), 2);
	s.pop();
	ASSERT_ANY_THROW(s.top());
}

TEST(StackTest, Top) {
	Stack<int> s(5);
	s.push(2);
	EXPECT_EQ(s.top(), 2);
	s.push(3);
	EXPECT_EQ(s.top(), 3);
	s.push(4);
	EXPECT_EQ(s.top(), 4);
}

TEST(StackTest, IsEmpty) {
	Stack<int> s;
	EXPECT_EQ(s.isEmpty(), true);
}

TEST(StackTest, IsNotEmpty) {
	Stack<int> s({-57, 4});
	EXPECT_EQ(s.isEmpty(), false);
	s.pop();
	EXPECT_EQ(s.isEmpty(), false);
	s.pop();
	EXPECT_EQ(s.isEmpty(), true);
}

TEST(StackTest, IsFull) {
	Stack<int> s({-1, 6});
	EXPECT_EQ(s.isFull(), true);
	s.pop();
	EXPECT_EQ(s.isFull(), false);
	s.pop();
	EXPECT_EQ(s.isFull(), false);
}

TEST(StackTest, IsNotFull) {
	Stack<int> s({ 1, 7, -46});
	EXPECT_EQ(s.isFull(), true);
	s.pop();
	EXPECT_EQ(s.isFull(), false);
	s.pop();
	EXPECT_EQ(s.isFull(), false);
}
