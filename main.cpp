/**
 * @file main.cpp
 * @brief This file contains the main function of the program that 
            loads command line arguments and runs the game
 * @author Bojana Paunovic
 * @date 28.12.2024.
 */

#include <iostream>
#include <string>
#include "game.h"

int main(int argc, char** argv) {
    int expected_arguments = 3; 
    try {
        if (argc != expected_arguments + 1) 
            throw std::runtime_error("Invalid number of arguments!");

        // Parse command-line arguments
        char* r = argv[1];
        char* c = argv[2];
        char* o = argv[3];

        // Convert arguments to integers
        int rows = std::stoi(r);
        if (rows <= 15) 
            throw std::runtime_error("Row count must be greater than 15!");

        int cols = std::stoi(c);
        if (cols <= 15) 
            throw std::runtime_error("Column count must be greater than 15!");

        int effects = std::stoi(o);
        if (effects <= 3) 
            throw std::runtime_error("Effect count must be greater than 3!");

        // Initialize the game with the provided parameters and run
        Game game(rows, cols, effects);
        game.run();
        return 0;
    }
    catch (std::exception& e) {
        std::cerr << e.what();
        return -1;
    }
}
