#pragma once

/**
 * @file game.h
 * @brief This header file contains the main Game 
			class which operates the entire game
 * @author Bojana Paunovic
 * @date 28.12.2024.
 */

#include "const.h"
#include "matrix.h"
#include "effect.h"
#include "maze_generator.h"
#include "file_manager.h"
#include <memory>


class Game {
	bool running, is_minotaur_alive, is_robot_alive;
	double generation_time;
	int effect_counter;
	Matrix matrix;
	std::unique_ptr<Effect> effect;
	FileManager file_manager;
public:
	std::string state;
	Game(int, int, int);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void run();
	void print();
	bool move_robot(int);
	void move_minotaur();
	bool validate(int, int);
	bool validate_move(int, int);
	void handle_invalid_move() const;
	void handle_minotaur(int, int);
	void kill_minotaur() { is_minotaur_alive = false; }
	bool is_fog() const;
	bool is_hammer() const;
	Matrix& get_matrix() { return matrix; }
	void generate_special();
	void validate_input(int&, std::string);
	void move(int);
};