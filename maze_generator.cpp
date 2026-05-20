/**
 * @file maze_generator.cpp
 * @brief Random maze generator with DFS and backtracking 
          ensuring a path from entrance to exit.
          Includes random placement of the Minotaur and 
          special effects along the path.
 * @author Bojana Paunovic
 * @date 03.01.2025.
 */

#include "maze_generator.h"

 /**
  * @brief This function initializes the maze boundaries, sets a random 
            entrance and exit, performs depth-first search (DFS) to 
            carve the maze, and adds robot, minotaur, and special effects. 
            The execution time is measured using a high-resolution clock.
  * @param m Reference to a Matrix object representing the maze matrix.
  * @return The time taken to generate the maze in milliseconds.
  */
namespace MazeGenerator {
    double generate_maze(Matrix& m) {
        auto start_time = std::chrono::high_resolution_clock::now();

        int entrance_col = m.get_random(2, m.col_count - 3);
        int exit_col = m.get_random(2, m.col_count - 3);

        for (int i = 0; i < m.row_count; i++) {
            m[i][0].is_visited = true;
            m[i][m.col_count - 1].is_visited = true;
        }
        for (int i = 1; i < m.col_count - 1; i++) {
            m[0][i].is_visited = true;
            m[m.row_count - 1][i].is_visited = true;
        }

        dfs(m, entrance_col, 1);

        m.clear(exit_col, m.row_count - 2);
        m.clear(exit_col, m.row_count - 3);

        remove_walls(m);

        m[0][entrance_col] = ENTRANCE;
        m.set_exit(exit_col, m.row_count - 1);
        m.set_robot(entrance_col, 1);

        put_minotaur(m);
        put_effects(m);

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed_time = end_time - start_time;

        return elapsed_time.count();
    }

    // Places the Minotaur randomly on a passage in the maze
    void put_minotaur(Matrix& m) {
        int minotaur_col, minotaur_row;
        do {
            minotaur_col = m.get_random(1, m.col_count - 2);
            minotaur_row = m.get_random(m.row_count / 2, m.row_count - 2);
        } while (m.is_wall(minotaur_col, minotaur_row));
        m.set_minotaur(minotaur_col, minotaur_row);
    }

    /**
     * @brief The function calculates whether the desired number of effects can
                fit in the maze without exceeding constraints.
                It randomly selects empty passage cells
                (excluding walls, existing effects, minotaur, or robot positions)
                and assigns them as special effect cells.
     * @param m Reference to a Matrix object representing the maze matrix.
     * @throws std::runtime_error If the number of effects exceeds the maximum
     *         possible for the given maze dimensions and wall count.
     */
    void put_effects(Matrix& m) {
        int effect_col, effect_row;
        int total = m.row_count * m.col_count - 2 * (m.row_count + m.col_count) + 2;
        if (total - m.wall_count < m.effect_count) {
            int max_effects = (total - m.min_wall_count) / 3;
            throw std::runtime_error("There cannot be more than " +
                std::to_string(max_effects) +
                " special effects for a maze with these dimensions!");
        }
        for (int i = 0; i < m.effect_count; i++) {
            do {
                effect_col = m.get_random(1, m.col_count - 2);
                effect_row = m.get_random(1, m.row_count - 2);
            } while (m[effect_row][effect_col] != PASSAGE);
            m[effect_row][effect_col] = EFFECT;
        }
    }

    // Removes some walls for better gameplay
    void remove_walls(Matrix& m) {
        int to_remove = m.get_random((m.wall_count - m.min_wall_count) / 3,
            2 * (m.wall_count - m.min_wall_count) / 3);

        for (int i = 0; i < to_remove; i++) {
            int col, row;
            do {
                col = m.get_random(1, m.col_count - 2);
                row = m.get_random(1, m.row_count - 2);
            } while (m[row][col] == PASSAGE);

            m.clear(col, row);
            --m.wall_count;
        }
    }

    /**
     * @brief This function uses an iterative approach with a stack to
                simulate recursion and carve passages in the maze.
                It explores neighboring cells in randomized directions,
                breaking walls to form paths and marking cells as visited.
                The algorithm ensures that passages are generated in
                a random but connected manner, and backtracking occurs when
                no unvisited neighbors are available.
     * @param m Reference to a Matrix object representing the maze grid.
     * @param start_x The x-coordinate of the starting cell.
     * @param start_y The y-coordinate of the starting cell.
     */
    void dfs(Matrix& m, int start_x, int start_y) {
        std::stack<std::tuple<int, int>> stack;

        stack.push({ start_x, start_y });
        m.clear(start_x, start_y);
        m[start_y][start_x].is_visited = true;
        --m.wall_count;


        while (!stack.empty()) {
            int x, y;
            std::tie(x, y) = stack.top();

            std::random_shuffle(directions.begin(), directions.end());

            bool moved = false;

            for (int i : directions) {
                int new_x = x + 2 * dx[i];
                int new_y = y + 2 * dy[i];

                if (new_x > 0 && new_y > 0 &&
                    new_x < m.col_count - 1 && new_y < m.row_count - 1 &&
                    !m[new_y][new_x].is_visited) {

                    m.clear(x + dx[i], y + dy[i]);
                    m[y + dy[i]][x + dx[i]].is_visited = true;
                    --m.wall_count;

                    m.clear(new_x, new_y);
                    m[new_y][new_x].is_visited = true;
                    --m.wall_count;

                    stack.push({ new_x, new_y });

                    moved = true;
                    break;
                }
            }

            if (!moved) {
                stack.pop();
            }
        }
    }
}
