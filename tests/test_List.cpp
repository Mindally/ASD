#include <gtest/gtest.h>

#include "../lib_list/List.h"
#include "../lib_tvector/TVector.h"

#include <string>

TEST(ListTest, DefaultConstructor) {
	List<int> l;
	EXPECT_EQ(l.isEmpty(), true);
	EXPECT_EQ(l.size(), 0);
	EXPECT_EQ(l.begin(), l.end());
}

TEST(ListTest, SizeConstructor) {
	List<int> l(5);
	EXPECT_EQ(l.isEmpty(), false);
	EXPECT_EQ(l.size(), 5);
	TVector<int> values;
	for (int val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<int>({ 0, 0, 0, 0, 0 }));
}

TEST(ListTest, SizeDataConstructor) {
	List<int> l(5, 4);
	EXPECT_EQ(l.isEmpty(), false);
	EXPECT_EQ(l.size(), 5);
	TVector<int> values;
	for (int val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<int>({ 4, 4, 4, 4, 4 }));
}

TEST(ListTest, TVectorConstructor) {
	TVector<int> vec({ 2, 7, 45, -7 });
	List<int> l(vec);
	EXPECT_EQ(l.isEmpty(), false);
	EXPECT_EQ(l.size(), 4);
	TVector<int> values;
	for (int val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<int>({ 2, 7, 45, -7 }));
}

TEST(ListTest, InitListConstructor) {
	std::initializer_list<int> init({ 7, 77, 777, -7777, 5, 6 });
	List<int> l(init);
	EXPECT_EQ(l.isEmpty(), false);
	EXPECT_EQ(l.size(), 6);
	TVector<int> values;
	for (int val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<int>({ 7, 77, 777, -7777, 5, 6 }));
}

TEST(ListTest, CopyConstructor) {
	List<int> data({ 19, 18, 17, 14, 17 });
	List<int> l(data);
	EXPECT_EQ(l.isEmpty(), false);
	EXPECT_EQ(l.size(), 5);
	TVector<int> values;
	for (int val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<int>({ 19, 18, 17, 14, 17 }));
}

TEST(ListTest, AssignList) {
	List<int> data({ 19, 18, 17, 14, 17 });
	List<int> l;
	l.assign(data);
	EXPECT_EQ(l.isEmpty(), false);
	EXPECT_EQ(l.size(), 5);
	TVector<int> values;
	for (int val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<int>({ 19, 18, 17, 14, 17 }));

	data.popBack();
	data.popBack();
	data.popBack();
	values.clear();
	for (int val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<int>({ 19, 18, 17, 14, 17 }));
}

TEST(ListTest, AssignTVector) {
	TVector<int> vec({ 1, 2, -3, 40 });
	List<int> l;
	l.assign(vec);
	EXPECT_EQ(l.isEmpty(), false);
	EXPECT_EQ(l.size(), 4);
	TVector<int> values;
	for (int val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<int>({ 1, 2, -3, 40 }));

	vec.pop_back();
	vec.pop_back();
	values.clear();
	for (int val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<int>({ 1, 2, -3, 40 }));
}

TEST(ListTest, IsEqual) {
	List<int> l1({3, 1});
	List<int> l2({ 3, 1, 5, 7});
	l1.pushBack(5);
	l1.pushBack(7);
	EXPECT_EQ(l1 == l2, true);
}

TEST(ListTest, IsNotEqual) {
	List<int> l1({ 3, 1 });
	List<int> l2({ 3, 1, 5, 7 });
	EXPECT_EQ(l1 != l2, true);
}

TEST(ListTest, ToTVector) {
	TVector<int> data({ 1, 2, -3, 40 });
	List<int> l({ 1, 2, -3, 40 });
	TVector<int> vec;
	vec = l.toTVector();
	EXPECT_TRUE(vec == data);
}

TEST(ListTest, PushFront) {
	List<double> l({3.17});
	l.pushFront(0.44);
	l.pushFront(1.72);
	l.pushFront(2.18);
	EXPECT_EQ(l.isEmpty(), false);
	TVector<double> values;
	for (double val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<double>({ 2.18, 1.72, 0.44, 3.17 }));
}

TEST(ListTest, PushBack) {
	List<double> l({5.93});
	l.pushBack(0.44);
	l.pushBack(1.72);
	l.pushBack(2.18);
	EXPECT_EQ(l.isEmpty(), false);
	TVector<double> values;
	for (double val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<double>({ 5.93, 0.44, 1.72, 2.18 }));
}

TEST(ListTest, InsertOutOfRangeExeption) {
	List<int> l({4, 5});
	ASSERT_ANY_THROW(l.insert(4, 5));
}

TEST(ListTest, InsertIntoMiddlePosition) {
	List<std::string> l({ "TEST1"});
	l.pushBack("TEST2");
	l.pushBack("TEST3");
	l.pushBack("TEST4");
	l.insert(2, "TESTINSERT");
	EXPECT_EQ(l.isEmpty(), false);
	TVector<std::string> values;
	for (std::string val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<std::string>({ "TEST1", "TEST2", "TESTINSERT", "TEST3", "TEST4"}));
}

TEST(ListTest, InsertAtFront) {
	List<std::string> l({ "TEST1" });
	l.pushBack("TEST2");
	l.pushBack("TEST3");
	l.pushBack("TEST4");
	l.insert(0, "TESTINSERT");
	EXPECT_EQ(l.isEmpty(), false);
	TVector<std::string> values;
	for (std::string val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<std::string>({ "TESTINSERT", "TEST1", "TEST2", "TEST3", "TEST4" }));
}

TEST(ListTest, InsertAtBack) {
	List<std::string> l({ "TEST1" });
	l.pushBack("TEST2");
	l.pushBack("TEST3");
	l.pushBack("TEST4");
	l.insert(4, "TESTINSERT");
	EXPECT_EQ(l.isEmpty(), false);
	TVector<std::string> values;
	for (std::string val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<std::string>({ "TEST1", "TEST2", "TEST3", "TEST4", "TESTINSERT" }));
}

TEST(ListTest, InsertNodeNullptrExeption) {
	List<int> l({ 1, 2 });
	ASSERT_ANY_THROW(l.insertAtNode(nullptr, 4));
}

TEST(ListTest, InsertToEmptyListExeption) {
	List<int> l;
	ASSERT_ANY_THROW(l.insertAtNode(&singly_linked::Node<int>(1, nullptr), 4));
}

TEST(ListTest, PopFrontEmptyListExeption) {
	List<int> l;
	ASSERT_ANY_THROW(l.popFront());
}

TEST(ListTest, PopFront) {
	List<int> l({ 1, 2, 3, 4, 5, 6 });
	l.popFront();
	l.popFront();
	l.popFront();
	EXPECT_EQ(l.isEmpty(), false);
	EXPECT_EQ(l.size(), 3);
	TVector<int> values;
	for (int val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<int>({ 4, 5, 6 }));
	l.popFront();
	l.popFront();
	l.popFront();
	EXPECT_EQ(l.isEmpty(), true);
	EXPECT_EQ(l.size(), 0);
}

TEST(ListTest, PopBackEmptyListExeption) {
	List<int> l;
	ASSERT_ANY_THROW(l.popBack());
}

TEST(ListTest, PopBack) {
	List<int> l({ 1, 2, 3, 4, 5, 6 });
	l.popBack();
	l.popBack();
	l.popBack();
	EXPECT_EQ(l.isEmpty(), false);
	EXPECT_EQ(l.size(), 3);
	TVector<int> values;
	for (int val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<int>({ 1, 2, 3 }));
	l.popBack();
	l.popBack();
	l.popBack();
	EXPECT_EQ(l.isEmpty(), true);
	EXPECT_EQ(l.size(), 0);
}

TEST(ListTest, EraseOutOfRangeExeption) {
	List<int> l({ 4, 5 });
	ASSERT_ANY_THROW(l.erase(2));
}

TEST(ListTest, EraseMiddlePosition) {
	List<std::string> l({ "TEST1" });
	l.pushBack("TEST2");
	l.pushBack("TEST3");
	l.pushBack("TEST4");
	l.erase(2);
	l.erase(2);
	EXPECT_EQ(l.isEmpty(), false);
	TVector<std::string> values;
	for (std::string val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<std::string>({ "TEST1", "TEST2"}));
}

TEST(ListTest, EraseFront) {
	List<std::string> l({ "TEST1" });
	l.pushBack("TEST2");
	l.pushBack("TEST3");
	l.pushBack("TEST4");
	l.erase(0);
	EXPECT_EQ(l.isEmpty(), false);
	TVector<std::string> values;
	for (std::string val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<std::string>({ "TEST2", "TEST3", "TEST4" }));
}

TEST(ListTest, EraseBack) {
	List<std::string> l({ "TEST1" });
	l.pushBack("TEST2");
	l.pushBack("TEST3");
	l.pushBack("TEST4");
	l.erase(3);
	l.erase(2);
	EXPECT_EQ(l.isEmpty(), false);
	TVector<std::string> values;
	for (std::string val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<std::string>({ "TEST1", "TEST2" }));
}

TEST(ListTest, EraseNodeNullptrExeption) {
	List<int> l({ 1, 2 });
	ASSERT_ANY_THROW(l.eraseNode(nullptr));
}

TEST(ListTest, EraseEmptyListExeption) {
	List<int> l;
	ASSERT_ANY_THROW(l.eraseNode(&singly_linked::Node<int>(1, nullptr)));
}

TEST(ListTest, IteratorEmptyList) {
	List<int> l;

	EXPECT_EQ(l.begin(), l.end());

	int count = 0;
	for (auto it = l.begin(); it != l.end(); ++it) {
		count++;
	}
	EXPECT_EQ(count, 0);
}

TEST(ListTest, IteratorReadOperations) {
	List<int> l({1, 4, 3});
	l.pushBack(1);

	auto it = l.begin();
	EXPECT_EQ(*it, 1);
	++it;
	EXPECT_EQ(*it, 4);
	++it;
	EXPECT_EQ(*it, 3);
	++it;
	EXPECT_EQ(*it, 1);

	std::vector<int> values;
	for (int val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, std::vector<int>({ 1, 4, 3, 1 }));
}

TEST(ListTest, IteratorWriteOperations) {
	List<int> l({11, 22});

	auto it = l.begin();
	*it = 100;
	++it;
	*it = 200;

	it = l.begin();
	EXPECT_EQ(*it, 100);
	++it;
	EXPECT_EQ(*it, 200);
}

TEST(ListTest, ConstIteratorEmptyList) {
	const List<int> l;

	EXPECT_EQ(l.begin(), l.end());

	int count = 0;
	for (auto it = l.begin(); it != l.end(); it++) {
		count++;
	}
	EXPECT_EQ(count, 0);
}

TEST(ListTest, ConstIteratorReadOperations) {
	const List<int> l({ 1, 4, 3 });

	auto it = l.begin();
	EXPECT_EQ(*it, 1);
	++it;
	EXPECT_EQ(*it, 4);
	++it;
	EXPECT_EQ(*it, 3);

	std::vector<int> values;
	for (int val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, std::vector<int>({ 1, 4, 3 }));
}
