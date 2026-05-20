/**
 * @file const.cpp
 * @brief This file contains values used in more than one 
			place in code for better readability
 * @author Bojana Paunovic
 * @date 28.12.2024.
 */

#include "const.h"

int dx[4] = { 0, 0, -1, 1 };  // Movement in x-direction
int dy[4] = { -1, 1, 0, 0 };  // Movement in y-direction
std::vector<int> directions = { 0, 1, 2, 3 };  // Up, down, left, right