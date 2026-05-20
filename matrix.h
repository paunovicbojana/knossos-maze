#pragma once

/**
 * @file matrix.h
 * @brief This header file contains the Matrix class which is 
		  responsiable for the whole maze organization
 * @author Bojana Paunovic
 * @date 28.12.2024.
 */

#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <stdexcept>
#include "cell.h"
#include "random_engine.h"
#include "const.h"

class Matrix {
	std::vector<std::vector<Cell>> matrix;
	Cell robot, minotaur, enter, exit;
	RandomEngine engine;
public:
	int row_count, col_count, effect_count, wall_count;
	int min_wall_count = 2 * (row_count + col_count);
	Matrix(int, int, int);
	Matrix(const Matrix&) = delete;
	Matrix& operator=(const Matrix&) = delete;
	std::vector<Cell>& operator[](int i) { return matrix[i]; }
	bool is_wall(int x, int y) const {
		if (matrix[y][x] == WALL) return true;
		return false;
	}
	bool is_exit(int x, int y) const {
		if (matrix[y][x] == EXIT) return true;
		return false;
	}
	bool is_robot(int x, int y) const {
		if (matrix[y][x] == ROBOT) return true;
		return false;
	}
	bool is_minotaur(int x, int y) const {
		if (matrix[y][x] == MINOTAUR) return true;
		return false;
	}
	bool is_effect(int x, int y) const {
		if (matrix[y][x] == EFFECT) return true;
		return false;
	}
	std::vector<std::vector<Cell>>& get_matrix() { return matrix; }
	int get_random(int x, int y) { return engine.random(x, y); }
	Cell& get_robot() { return robot; }
	Cell& get_minotaur() { return minotaur; }
	Cell& get_exit() { return exit; }
	void set_robot(int x, int y) { 
		robot.x = x; 
		robot.y = y; 
		matrix[y][x] = ROBOT; 
	}
	void set_minotaur(int x, int y) { 
		minotaur.x = x; 
		minotaur.y = y; 
		matrix[y][x] = MINOTAUR; 
	}
	void set_exit(int x, int y) {
		exit.x = x;
		exit.y = y;
		matrix[y][x] = EXIT;
	}
	void print_matrix(bool fog = false);
	void clear(const Cell& c) { matrix[c.y][c.x] = PASSAGE; }
	void clear(int x, int y) { matrix[y][x] = PASSAGE; }
	friend std::ostream& operator<<(std::ostream&, const Matrix&);
};