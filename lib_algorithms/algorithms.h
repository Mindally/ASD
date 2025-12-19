#pragma once

#include <string>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include "../lib_stack/stack.h"
#include "../lib_tvector/TVector.h"
#include "../lib_dsu/DSU.h"
#include "../lib_list/List.h"
#include <unordered_set>

const int MAX_N = 100;
int findLocalMin(int matrix[][MAX_N], int n);

bool checkBrackets(std::string);

void readExpression(std::string);

int countIslands(const TVector<TVector<int>>&);

template <class T> bool isLooped(const List<T>& list) {
    if (list.isEmpty()) return false;

    auto slow = list.begin();
    auto fast = list.begin();

    if (slow.getNode() != nullptr &&
        slow.getNode()->next == slow.getNode()) {
        return true;
    }

    while (slow != list.end() && fast != list.end()) {
        ++slow;
        if (slow == list.end()) return false;

        ++fast;
        if (fast == list.end()) return false;
        ++fast;
        if (fast == list.end()) return false;

        if (slow == fast) return true;
    }

    return false;
}

template <class T> bool isLoopedWithMarkers(List<T>& list) {
    if (list.isEmpty()) return false;

    std::unordered_set<singly_linked::Node<T>*> visited_nodes;

    for (auto it = list.begin(); it != list.end(); ++it) {
        auto node = it.getNode();

        if (visited_nodes.find(node) != visited_nodes.end()) {
            return true;
        }

        visited_nodes.insert(node);
    }

    return false;
}


template <class T> singly_linked::Node<T>* findLoopStart(List<T>& list) {
    if (list.isEmpty()) return nullptr;

    auto slow = list.begin();
    auto fast = list.begin();

    while (fast != list.end()) {
        ++slow;
        if (slow == list.end()) return nullptr;

        ++fast;
        if (fast == list.end()) return nullptr;
        ++fast;
        if (fast == list.end()) return nullptr;

        if (slow == fast) {
            break;
        }
    }
    if (fast == list.end()) return nullptr;

    slow = list.begin();

    while (slow != fast) {
        ++slow;
        ++fast;
    }
    return slow.getNode();
}