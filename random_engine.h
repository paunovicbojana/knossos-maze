#pragma once

/**
 * @file random_engine.h
 * @brief This header file contains the RandomEngine class 
          for random number generation used across the whole game
 * @author Bojana Paunovic
 * @date 28.12.2024.
 */

#include <random>
class RandomEngine {
public:
    RandomEngine() {}
    int random(int x, int y) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dir_dist(x, y);
        return dir_dist(gen);
    }
};

