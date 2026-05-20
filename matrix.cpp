/**
 * @file matrix.cpp
 * @brief This file contains functions from class Matrix 
          for constructing the primitive game maze and printing it
 * @author Bojana Paunovic
 * @date 28.12.2024.
 */

#include "matrix.h"

//Constructor for the Matrix class
Matrix::Matrix(int x, int y, int o) :
    row_count(x),
    col_count(y),
    effect_count(o),
    engine(),
    wall_count(x * y - 2 * (x + y) + 4 - 2)
{
    // Initialize the matrix with wall cells
    for (int i = 0; i < x; i++) {
        std::vector<Cell> row; // Temporary row vector
        for (int j = 0; j < y; j++) {
            row.emplace_back(i, j, WALL);
        }
        matrix.emplace_back(std::move(row));
    }
}

/**
 * @brief This function clears the console screen, then prints the matrix.
          If fog of war is enabled, only a limited view centered on 
          the robot's current position is displayed.
          This simulates a restricted field of vision, 
          enhancing gameplay dynamics.
 * @param fog A boolean flag indicating whether the fog of war is enabled.
 *            If `false`, the entire matrix is printed.
 *            If `true`, only a 3x3 area around the robot's position is shown.
 */
void Matrix::print_matrix(bool fog) {
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif

    if (!fog) {
        std::cout << *this;
    }
    else {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int x = robot.x + j;
                int y = robot.y + i;

                if (y >= 0 && y < row_count && x >= 0 && x < col_count) {
                    std::cout << matrix[y][x];
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& o, const Matrix& m) {
    for (const auto& row : m.matrix) {
        for (const Cell& c : row) {
            o << c;
        }
        o << std::endl;
    }
    return o;
}
