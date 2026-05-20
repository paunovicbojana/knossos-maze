#pragma once

/**
 * @file maze_generator.h
 * @brief This header file contains the MazeGenerator class 
		  which is responsiable for randomly generating the maze matrix
 * @author Bojana Paunovic
 * @date 28.12.2024.
 */

#include "matrix.h"
#include <stack>
#include <vector>
#include <chrono>
#include <tuple>
#include <string>

namespace MazeGenerator {
	double generate_maze(Matrix&);
	void dfs(Matrix&, int, int);
	void remove_walls(Matrix&);
	void put_minotaur(Matrix&);
	void put_effects(Matrix&);
};