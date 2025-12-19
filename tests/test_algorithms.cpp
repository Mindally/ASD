#include <gtest/gtest.h>

#include "../lib_algorithms/algorithms.h"

TEST(CheckBracketsTest, SingleOpeningBracket) {
	EXPECT_FALSE(checkBrackets("("));
	EXPECT_FALSE(checkBrackets("{"));
	EXPECT_FALSE(checkBrackets("["));
}

TEST(CheckBracketsTest, SingleClosingBracket) {
	EXPECT_FALSE(checkBrackets(")"));
	EXPECT_FALSE(checkBrackets("}"));
	EXPECT_FALSE(checkBrackets("]"));
}

TEST(CheckBracketsTest, SimpleBalancedBrackets) {
	EXPECT_TRUE(checkBrackets("()"));
	EXPECT_TRUE(checkBrackets("{}"));
	EXPECT_TRUE(checkBrackets("[]"));
}

TEST(CheckBracketsTest, MixedBalancedBrackets) {
	EXPECT_TRUE(checkBrackets("()[]{}"));
	EXPECT_TRUE(checkBrackets("({[]})"));
	EXPECT_TRUE(checkBrackets("[{()}]"));
}

TEST(CheckBracketsTest, NestedBalancedBrackets) {
	EXPECT_TRUE(checkBrackets("({[]})"));
	EXPECT_TRUE(checkBrackets("[({})]"));
	EXPECT_TRUE(checkBrackets("{([])}"));
}

TEST(CheckBracketsTest, SequentialBalancedBrackets) {
	EXPECT_TRUE(checkBrackets("(){}[]"));
	EXPECT_TRUE(checkBrackets("([]){}"));
	EXPECT_TRUE(checkBrackets("{()}[{}]"));
}

TEST(CheckBracketsTest, UnbalancedMoreOpening) {
	EXPECT_FALSE(checkBrackets("({"));
	EXPECT_FALSE(checkBrackets("[{("));
	EXPECT_FALSE(checkBrackets("({["));
}

TEST(CheckBracketsTest, UnbalancedMoreClosing) {
	EXPECT_FALSE(checkBrackets(")}"));
	EXPECT_FALSE(checkBrackets("])}"));
	EXPECT_FALSE(checkBrackets("())"));
}

TEST(CheckBracketsTest, WrongOrderBrackets) {
	EXPECT_FALSE(checkBrackets(")("));
	EXPECT_FALSE(checkBrackets("}{"));
	EXPECT_FALSE(checkBrackets("]["));
	EXPECT_FALSE(checkBrackets("([)]"));
	EXPECT_FALSE(checkBrackets("{(})"));
}

TEST(CheckBracketsTest, MixedWrongOrder) {
	EXPECT_FALSE(checkBrackets("(]"));
	EXPECT_FALSE(checkBrackets("[}"));
	EXPECT_FALSE(checkBrackets("{)"));
	EXPECT_FALSE(checkBrackets("([)]"));
	EXPECT_FALSE(checkBrackets("{[}]"));
}

TEST(CheckBracketsTest, StringWithOtherCharacters) {
	EXPECT_TRUE(checkBrackets("(abc)"));
	EXPECT_TRUE(checkBrackets("a{b[c]d}e"));
	EXPECT_TRUE(checkBrackets("hello (world) {test} [array]"));

	EXPECT_FALSE(checkBrackets("(abc"));
	EXPECT_FALSE(checkBrackets("abc]"));
	EXPECT_FALSE(checkBrackets("a{b(c)d"));
}

TEST(CheckBracketsTest, EdgeCases) {
	EXPECT_TRUE(checkBrackets("()"));
	EXPECT_TRUE(checkBrackets("{}"));
	EXPECT_TRUE(checkBrackets("[]"));
	EXPECT_FALSE(checkBrackets("(}"));
	EXPECT_FALSE(checkBrackets("[)"));
	EXPECT_FALSE(checkBrackets("{)"));
}

TEST(CheckBracketsTest, OnlyOneTypeOfBracket) {
	EXPECT_TRUE(checkBrackets("((()))"));
	EXPECT_TRUE(checkBrackets("{{{}}}"));
	EXPECT_TRUE(checkBrackets("[[[]]]"));

	EXPECT_FALSE(checkBrackets("((())"));
	EXPECT_FALSE(checkBrackets("{{}}}"));
	EXPECT_FALSE(checkBrackets("[[[]]"));
}

TEST(CheckBracketsTest, RealExamples) {
	EXPECT_TRUE(checkBrackets("f(x) = [(x + 1) * {x - 2}]"));
}

TEST(DSUTask, CountIslands) {
	TVector<TVector<int>> matrix1(5);
	TVector<TVector<int>> matrix2(5);
	TVector<TVector<int>> matrix3(5);

	matrix1[0] = TVector<int>{ 0, 1, 0, 0, 1 };
	matrix1[1] = TVector<int>{ 0, 1, 1, 0, 1 };
	matrix1[2] = TVector<int>{ 1, 1, 0, 1, 1 };
	matrix1[3] = TVector<int>{ 0, 0, 0, 0, 1 };
	matrix1[4] = TVector<int>{ 1, 0, 1, 1, 1 };

	matrix2[0] = TVector<int>{ 0, 0, 1, 0, 0 };
	matrix2[1] = TVector<int>{ 0, 0, 1, 0, 0 };
	matrix2[2] = TVector<int>{ 1, 1, 1, 1, 1 };
	matrix2[3] = TVector<int>{ 0, 0, 1, 0, 0 };
	matrix2[4] = TVector<int>{ 0, 0, 1, 0, 0 };

	matrix3[0] = TVector<int>{ 1, 1, 0, 1, 1 };
	matrix3[1] = TVector<int>{ 1, 1, 0, 1, 1 };
	matrix3[2] = TVector<int>{ 0, 0, 0, 0, 0 };
	matrix3[3] = TVector<int>{ 1, 1, 0, 1, 1 };
	matrix3[4] = TVector<int>{ 1, 1, 0, 1, 1 };

	EXPECT_EQ(countIslands(matrix1), 3);
	EXPECT_EQ(countIslands(matrix2), 1);
	EXPECT_EQ(countIslands(matrix3), 4);
}

TEST(CheckLoopsTest, TurtleRabbitNoLoop) {
	List<int> list;
	list.pushBack(1);
	list.pushBack(2);
	list.pushBack(3);
	EXPECT_FALSE(isLooped(list));
}

TEST(CheckLoopsTest, TurtleRabbitLoop) {
	List<int> list;
	list.pushBack(1);
	list.pushBack(2);
	list.pushBack(3);
	list.pushBack(4);

	auto last = list.begin();
	auto temp = list.begin();
	while (++temp != list.end()) {
		++last;
	}

	auto second = list.begin();
	++second;

	auto last_node = last.getNode();
	auto second_node = second.getNode();

	auto original_next = last_node->next;
	last_node->next = second_node;

	EXPECT_TRUE(isLooped(list));

	last_node->next = original_next;
}

TEST(CheckLoopsTest, TurtleRabbitLoopSingle) {
	List<int> list;
	list.pushBack(1);

	auto only = list.begin();
	auto node = only.getNode();
	auto original_next = node->next;

	node->next = node;

	EXPECT_TRUE(isLooped(list));

	node->next = original_next;
}

TEST(IsLoopedReverseTest, EmptyList) {
	List<int> list;
	bool result = isLoopedWithMarkers(list);
	EXPECT_FALSE(result);
}

TEST(FindLoopTest, EmptyList) {
	List<int> list;

	auto result = findLoopStart(list);
	EXPECT_EQ(result, nullptr);
}

TEST(FindLoopTest, NoLoop) {
	List<int> list;
	list.pushBack(1);
	list.pushBack(2);
	list.pushBack(3);

	auto result = findLoopStart(list);
	EXPECT_EQ(result, nullptr);
}

TEST(FindLoopTest, SingleElementNoLoop) {
	List<int> list;
	list.pushBack(42);

	auto result = findLoopStart(list);
	EXPECT_EQ(result, nullptr);
}

TEST(FindLoopTest, SingleElementLoop) {
	List<int> list;
	list.pushBack(42);

	auto it = list.begin();
	auto node = it.getNode();

	auto original_next = node->next;
	node->next = node;

	auto result = findLoopStart(list);
	EXPECT_NE(result, nullptr);
	EXPECT_EQ(result, node);

	node->next = original_next;
}

TEST(FindLoopTest, TwoElementLoop) {
	List<int> list;
	list.pushBack(1);
	list.pushBack(2);

	auto it1 = list.begin();
	auto it2 = list.begin();
	++it2;

	auto node1 = it1.getNode();
	auto node2 = it2.getNode();

	auto original_next = node2->next;
	node2->next = node1;

	auto result = findLoopStart(list);
	EXPECT_NE(result, nullptr);
	EXPECT_EQ(result, node1);

	node2->next = original_next;
}

TEST(FindLoopTest, LoopInMiddle) {
	List<int> list;
	list.pushBack(1);
	list.pushBack(2);
	list.pushBack(3);
	list.pushBack(4);
	list.pushBack(5);

	auto it = list.begin();
	++it; ++it;
	auto node3 = it.getNode();
	++it;
	auto node4 = it.getNode();
	++it;
	auto node5 = it.getNode();

	auto original_next = node5->next;
	node5->next = node3;

	auto result = findLoopStart(list);
	EXPECT_NE(result, nullptr);
	EXPECT_EQ(result, node3);

	node5->next = original_next;
}

TEST(FindLoopTest, FullCycle) {
	List<int> list;
	list.pushBack(1);
	list.pushBack(2);
	list.pushBack(3);

	auto it = list.begin();
	auto node1 = it.getNode();
	++it;
	auto node2 = it.getNode();
	++it;
	auto node3 = it.getNode();

	auto original_next = node3->next;
	node3->next = node1;

	auto result = findLoopStart(list);
	EXPECT_NE(result, nullptr);
	EXPECT_EQ(result, node1);

	node3->next = original_next;
}

TEST(FindLoopTest, IteratorStillWorks) {
	List<int> list;
	list.pushBack(1);
	list.pushBack(2);
	list.pushBack(3);

	auto result = findLoopStart(list);
	EXPECT_EQ(result, nullptr);

	std::vector<int> values;
	for (int val : list) {
		values.push_back(val);
	}
	EXPECT_EQ(values, std::vector<int>({ 1, 2, 3 }));
}

TEST(FindLoopTest, LoopInMiddleLarge) {
	List<int> list;
	for (int i = 1; i <= 10; i++) {
		list.pushBack(i);
	}

	auto it_cycle_start = list.begin();
	for (int i = 0; i < 4; ++i) {
		++it_cycle_start;
	}

	auto it_end = list.begin();
	while (true) {
		auto next_it = it_end;
		++next_it;
		if (next_it == list.end()) break;
		++it_end;
	}

	auto* node_cycle_start = it_cycle_start.getNode();
	auto* node_end = it_end.getNode();

	auto original_next = node_end->next;
	node_end->next = node_cycle_start;

	auto result = findLoopStart(list);
	EXPECT_NE(result, nullptr);
	EXPECT_EQ(result, node_cycle_start);
	EXPECT_EQ(result->value, 5);

	node_end->next = original_next;
}

TEST(IsLoopedReverseTest, NoLoop) {
	List<int> list;
	list.pushBack(1);
	list.pushBack(2);
	list.pushBack(3);
	EXPECT_FALSE(isLoopedWithMarkers(list));
}

TEST(IsLoopedReverseTest, LoopExists) {
	List<int> list;
	list.pushBack(1);
	list.pushBack(2);
	list.pushBack(3);

	auto it1 = list.begin();
	auto it3 = list.begin();
	++it3; ++it3;

	auto node1 = it1.getNode();
	auto node3 = it3.getNode();

	auto original_next = node3->next;
	node3->next = node1;

	EXPECT_TRUE(isLoopedWithMarkers(list));

	node3->next = original_next;
}

TEST(LoopDetectionLargeListTest, NoLoop) {
	List<int> list;
	for (int i = 0; i < 1000; ++i) {
		list.pushBack(i);
	}

	EXPECT_FALSE(isLooped(list));
	EXPECT_FALSE(isLoopedWithMarkers(list));
	EXPECT_EQ(findLoopStart(list), nullptr);
}

TEST(LoopDetectionLargeListTest, WithLoop) {
	List<int> list;
	for (int i = 0; i < 100; ++i) {
		list.pushBack(i);
	}

	auto it_middle = list.begin();
	auto it_end = list.begin();

	for (int i = 0; i < 50; ++i) {
		++it_middle;
	}

	while (true) {
		auto next_it = it_end;
		++next_it;
		if (next_it == list.end()) break;
		++it_end;
	}

	auto middle_node = it_middle.getNode();
	auto end_node = it_end.getNode();

	auto original_next = end_node->next;
	end_node->next = middle_node;

	EXPECT_TRUE(isLooped(list));
	EXPECT_TRUE(isLoopedWithMarkers(list));

	auto loop_start = findLoopStart(list);
	EXPECT_NE(loop_start, nullptr);
	EXPECT_EQ(loop_start, middle_node);
	EXPECT_EQ(loop_start->value, 50);

	end_node->next = original_next;
}