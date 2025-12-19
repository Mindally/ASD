#pragma once

#include <string>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include "../lib_stack/stack.h"

const int MAX_N = 100;
int findLocalMin(int matrix[][MAX_N], int n);

bool checkBrackets(std::string);

void readExpression(std::string);