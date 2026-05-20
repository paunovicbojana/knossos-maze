#pragma once

/**
 * @file file_manager.h
 * @brief This header file contains class 
          FileManager that works with files
 * @author Bojana Paunovic
 * @date 28.12.2024.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "matrix.h"

class FileManager {
public:
    void write_state(const std::string& state, const Matrix& matrix) {
        std::ofstream file("game_state.txt");
        if (file.is_open()) {
            file << state << "\n\n" << matrix;
            file.close();
            std::cout << "Final game state saved to game_state.txt\n";
        }
        else {
            throw std::runtime_error("Failed to save the game state to a file.\n");
        }
    }

    void read_state(Matrix& matrix, std::string filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filepath);
        }

        std::string line;
        int row = 0;
        while (std::getline(file, line)) {
            for (int col = 0; col < matrix.col_count && col < line.size(); ++col) {
                char cell_type = line[col];
                if (cell_type == MINOTAUR) matrix.set_minotaur(col, row);
                else if (cell_type == EXIT) matrix.set_exit(col, row);
                else if (cell_type == ROBOT) matrix.set_robot(col, row);
                matrix.get_matrix()[row][col] = cell_type;
            }
            ++row;
        }
        file.close();
    }
};
