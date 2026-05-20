#pragma once

/**
 * @file const.h
 * @brief This header file contains values used in 
			multiple functions for better readability
 * @author Bojana Paunovic
 * @date 28.12.2024.
 */

#include <vector>

extern int dx[4];
extern int dy[4];
extern std::vector<int> directions;

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int QUIT = -1;
const int ERROR = -2;

const char WALL = '#';
const char PASSAGE = '.';
const char ROBOT = 'R';
const char MINOTAUR = 'M';
const char ENTRANCE = 'U';
const char EXIT = 'I';
const char EFFECT = 'P';

const int EFFECT_DURATION = 3;