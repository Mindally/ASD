#include <gtest/gtest.h>

#include "../lib_doubly_linked_list/DoublyLinkedList.h"
#include "../lib_tvector/TVector.h"

#include <string>

TEST(DoublyLinkedListTest, DefaultConstructor) {
	DoublyLinkedList<int> l;
	EXPECT_EQ(l.isEmpty(), true);
	EXPECT_EQ(l.size(), 0);
	EXPECT_EQ(l.begin(), l.end());
}

TEST(DoublyLinkedListTest, SizeConstructor) {
	DoublyLinkedList<int> l(5);
	EXPECT_EQ(l.isEmpty(), false);
	EXPECT_EQ(l.size(), 5);
	TVector<int> values;
	for (int val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<int>({ 0, 0, 0, 0, 0 }));
}

TEST(DoublyLinkedListTest, SizeDataConstructor) {
	DoublyLinkedList<int> l(5, 4);
	EXPECT_EQ(l.isEmpty(), false);
	EXPECT_EQ(l.size(), 5);
	TVector<int> values;
	for (int val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<int>({ 4, 4, 4, 4, 4 }));
}

TEST(DoublyLinkedListTest, TVectorConstructor) {
	TVector<int> vec({ 2, 7, 45, -7 });
	DoublyLinkedList<int> l(vec);
	EXPECT_EQ(l.isEmpty(), false);
	EXPECT_EQ(l.size(), 4);
	TVector<int> values;
	for (int val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<int>({ 2, 7, 45, -7 }));
}

TEST(DoublyLinkedListTest, InitListConstructor) {
	std::initializer_list<int> init({ 7, 77, 777, -7777, 5, 6 });
	DoublyLinkedList<int> l(init);
	EXPECT_EQ(l.isEmpty(), false);
	EXPECT_EQ(l.size(), 6);
	TVector<int> values;
	for (int val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<int>({ 7, 77, 777, -7777, 5, 6 }));
}

TEST(DoublyLinkedListTest, CopyConstructor) {
	DoublyLinkedList<int> data({ 19, 18, 17, 14, 17 });
	DoublyLinkedList<int> l(data);
	EXPECT_EQ(l.isEmpty(), false);
	EXPECT_EQ(l.size(), 5);
	TVector<int> values;
	for (int val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<int>({ 19, 18, 17, 14, 17 }));
}

TEST(DoublyLinkedListTest, AssignList) {
	DoublyLinkedList<int> data({ 19, 18, 17, 14, 17 });
	DoublyLinkedList<int> l;
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

TEST(DoublyLinkedListTest, AssignTVector) {
	TVector<int> vec({ 1, 2, -3, 40 });
	DoublyLinkedList<int> l;
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

TEST(DoublyLinkedListTest, IsEqual) {
	DoublyLinkedList<int> l1({ 3, 1 });
	DoublyLinkedList<int> l2({ 3, 1, 5, 7 });
	l1.pushBack(5);
	l1.pushBack(7);
	EXPECT_EQ(l1 == l2, true);
}

TEST(DoublyLinkedListTest, IsNotEqual) {
	DoublyLinkedList<int> l1({ 3, 1 });
	DoublyLinkedList<int> l2({ 3, 1, 5, 7 });
	EXPECT_EQ(l1 != l2, true);
}

TEST(DoublyLinkedListTest, ToTVector) {
	TVector<int> data({ 1, 2, -3, 40 });
	DoublyLinkedList<int> l({ 1, 2, -3, 40 });
	TVector<int> vec;
	vec = l.toTVector();
	EXPECT_TRUE(vec == data);
}

TEST(DoublyLinkedListTest, PushFront) {
	DoublyLinkedList<double> l({ 3.17 });
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

TEST(DoublyLinkedListTest, PushBack) {
	DoublyLinkedList<double> l({ 5.93 });
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

TEST(DoublyLinkedListTest, InsertOutOfRangeExeption) {
	DoublyLinkedList<int> l({ 4, 5 });
	ASSERT_ANY_THROW(l.insert(4, 5));
}

TEST(DoublyLinkedListTest, InsertIntoMiddlePosition) {
	DoublyLinkedList<std::string> l({ "TEST1" });
	l.pushBack("TEST2");
	l.pushBack("TEST3");
	l.pushBack("TEST4");
	l.insert(2, "TESTINSERT");
	EXPECT_EQ(l.isEmpty(), false);
	TVector<std::string> values;
	for (std::string val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, TVector<std::string>({ "TEST1", "TEST2", "TESTINSERT", "TEST3", "TEST4" }));
}

TEST(DoublyLinkedListTest, InsertAtFront) {
	DoublyLinkedList<std::string> l({ "TEST1" });
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

TEST(DoublyLinkedListTest, InsertAtBack) {
	DoublyLinkedList<std::string> l({ "TEST1" });
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

TEST(DoublyLinkedListTest, InsertNodeNullptrExeption) {
	DoublyLinkedList<int> l({ 1, 2 });
	ASSERT_ANY_THROW(l.insertAtNode(nullptr, 4));
}

TEST(DoublyLinkedListTest, InsertToEmptyListExeption) {
	DoublyLinkedList<int> l;
	ASSERT_ANY_THROW(l.insertAtNode(&doubly_linked::Node<int>(1, nullptr, nullptr), 4));
}

TEST(DoublyLinkedListTest, PopFrontEmptyListExeption) {
	DoublyLinkedList<int> l;
	ASSERT_ANY_THROW(l.popFront());
}

TEST(DoublyLinkedListTest, PopFront) {
	DoublyLinkedList<int> l({ 1, 2, 3, 4, 5, 6 });
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

TEST(DoublyLinkedListTest, PopBackEmptyListExeption) {
	DoublyLinkedList<int> l;
	ASSERT_ANY_THROW(l.popBack());
}

TEST(DoublyLinkedListTest, PopBack) {
	DoublyLinkedList<int> l({ 1, 2, 3, 4, 5, 6 });
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

TEST(DoublyLinkedListTest, EraseOutOfRangeExeption) {
	DoublyLinkedList<int> l({ 4, 5 });
	ASSERT_ANY_THROW(l.erase(2));
}

TEST(DoublyLinkedListTest, EraseMiddlePosition) {
	DoublyLinkedList<std::string> l({ "TEST1" });
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
	EXPECT_EQ(values, TVector<std::string>({ "TEST1", "TEST2" }));
}

TEST(DoublyLinkedListTest, EraseFront) {
	DoublyLinkedList<std::string> l({ "TEST1" });
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

TEST(DoublyLinkedListTest, EraseBack) {
	DoublyLinkedList<std::string> l({ "TEST1" });
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

TEST(DoublyLinkedListTest, EraseNodeNullptrExeption) {
	DoublyLinkedList<int> l({ 1, 2 });
	ASSERT_ANY_THROW(l.eraseNode(nullptr));
}

TEST(DoublyLinkedListTest, EraseEmptyListExeption) {
	DoublyLinkedList<int> l;
	ASSERT_ANY_THROW(l.eraseNode(&doubly_linked::Node<int>(1, nullptr, nullptr)));
}

TEST(DoublyLinkedListTest, IteratorEmptyList) {
	DoublyLinkedList<int> l;

	EXPECT_EQ(l.begin(), l.end());

	int count = 0;
	for (auto it = l.begin(); it != l.end(); ++it) {
		count++;
	}
	EXPECT_EQ(count, 0);
}

TEST(DoublyLinkedListTest, IteratorReadOperations) {
	DoublyLinkedList<int> l({ 1, 4, 3 });
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

TEST(DoublyLinkedListTest, IteratorReadOperationsBackwards) {
	DoublyLinkedList<int> l({ 1, 4, 3 });
	l.pushBack(1);

	auto it = l.rbegin();
	EXPECT_EQ(*it, 1);
	--it;
	EXPECT_EQ(*it, 3);
	--it;
	EXPECT_EQ(*it, 4);
	--it;
	EXPECT_EQ(*it, 1);

	std::vector<int> values;
	for (int val : l) {
		values.push_back(val);
	}
	EXPECT_EQ(values, std::vector<int>({ 1, 4, 3, 1 }));
}

TEST(DoublyLinkedListTest, IteratorForWriteOperations) {
	DoublyLinkedList<int> l({ 11, 22 });

	int i = 2;
	for (auto it = l.rbegin(); it != l.rend(); it--) {
		*it *= i;
		i++;
	}
	auto it = l.rbegin();
	EXPECT_EQ(*it, 44);
	--it;
	EXPECT_EQ(*it, 33);
}


TEST(DoublyLinkedListTest, IteratorWriteOperations) {
	DoublyLinkedList<int> l({ 11, 22 });

	auto it = l.begin();
	*it = 100;
	++it;
	*it = 200;

	it = l.begin();
	EXPECT_EQ(*it, 100);
	++it;
	EXPECT_EQ(*it, 200);
}

TEST(DoublyLinkedListTest, ConstIteratorEmptyList) {
	const DoublyLinkedList<int> l;

	EXPECT_EQ(l.begin(), l.end());

	int count = 0;
	for (auto it = l.begin(); it != l.end(); ++it) {
		count++;
	}
	EXPECT_EQ(count, 0);
}

TEST(DoublyLinkedListTest, ConstIteratorReadOperations) {
	const DoublyLinkedList<int> l({ 1, 4, 3 });

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
