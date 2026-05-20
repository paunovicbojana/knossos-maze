/**
 * @file game.cpp
 * @brief This file contains functions from the class Game 
            which is responsible for player movement, 
            input validation, effects generation...
 * @author Bojana Paunovic
 * @date 28.12.2024.
 */

#include "game.h"
#include "hammer.h"
#include "shield.h"
#include "sword.h"
#include "fog.h"

// Constructor for the Game class
Game::Game(int x, int y, int o) :
    running(true),
    is_minotaur_alive(true),
    is_robot_alive(true),
    generation_time(0),
    effect_counter(0),
    matrix(x, y, o), 
    file_manager()
{
    generation_time = MazeGenerator::generate_maze(matrix);

    //file_manager.read_state(matrix, "test/maze1.txt");
}

// Prints the game matrix, with or without war fog
void Game::print() {
    if (is_fog()) matrix.print_matrix(true);
    else matrix.print_matrix();
}

// Validates if the given coordinates are within the maze boundaries
bool Game::validate(int x, int y) {
    return y > 0 && x > 0
        && y < matrix.row_count - 1 && x < matrix.col_count - 1;
}

// Checks if the current effect is a hammer
bool Game::is_hammer() const {
    return effect && effect->break_wall();
}

// Checks if the current effect is fog
bool Game::is_fog() const {
    return effect && 
        effect->get_name() == "war fog";
}

// Handles an invalid move
void Game::handle_invalid_move() const {
    std::cout << "Cannot go through the wall!\n\n";
}

/**
 * @brief This function determines the outcome of an encounter between 
            the robot and the Minotaur. If an effect is active, it is 
            applied, and the robot may escape if the Minotaur is defeated. 
            Otherwise, the Minotaur moves to its new position, 
            and the game ends with the robot's death. 
            The game state is updated and printed.
 * @param x The x-coordinate of the Minotaur's current position.
 * @param y The y-coordinate of the Minotaur's current position.
 */
void Game::handle_minotaur(int x, int y) {
    if (effect) {
        effect->does(*this);
        if (!is_minotaur_alive) {
            Cell& r = matrix.get_robot();
            matrix.clear(r);
            matrix.set_robot(x, y);
            print();
        }
        else if (effect->get_name() == "shield") return;
        else {
            matrix.set_minotaur(x, y);
            state = "You lost. The Minotaur ate you!\n";
            std::cout << state;
            is_robot_alive = false;
            running = false;
        }
    }
    else if (is_minotaur_alive){
        matrix.set_minotaur(x, y);
        state = "You lost. The Minotaur ate you!\n";
        std::cout << state;
        is_robot_alive = false;
        running = false;
    }
}

// Validates if the robot can move to the new coordinates
bool Game::validate_move(int x, int y) {
    if (matrix.is_exit(x, y)) {
        state = "You won!\n";
        std::cout << state;
        running = false;
    }
    else if (!validate(x, y) || (matrix.is_wall(x, y) && !is_hammer())) {
        handle_invalid_move();
    }
    else {
        return true;
    }
    return false;
}

// Generates a random special effect and applies it
void Game::generate_special() {
    int random_effect = matrix.get_random(0, 3);
    switch (random_effect) {
    case 0:
        effect = std::make_unique<Hammer>();
        break;
    case 1:
        effect = std::make_unique<Shield>();
        break;
    case 2:
        effect = std::make_unique<Sword>();
        break;
    case 3:
        effect = std::make_unique<Fog>();
        break;
    }
    effect_counter = EFFECT_DURATION + 1;
    std::cout << "You found a " + effect->get_name() + "!\n";
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

/**
 * @brief This function validates the movement based on the maze's constraints.
            If the destination contains the Minotaur, it handles the interaction.
            If the destination contains a special effect, it triggers the effect.
            The robot's position is updated, and its previous location is cleared.
            If an effect is active, its duration is decremented, and the effect 
            is reset when its duration ends.
 * @param direction The direction in which to move the robot (index of dx/dy arrays).
 * @return `true` if the robot successfully moves to a new position, otherwise `false`.
 */

bool Game::move_robot(int direction) {
    Cell r = matrix.get_robot();
    int new_x = r.x + dx[direction];
    int new_y = r.y + dy[direction];
    if (validate_move(new_x, new_y)) {
        if (matrix.is_minotaur(new_x, new_y)) {
            handle_minotaur(new_x, new_y);
            return false;
        }
        if (matrix.is_effect(new_x, new_y)) 
            generate_special();
        matrix.set_robot(new_x, new_y);
        matrix.clear(r);

        if (effect_counter > 0) {
            --effect_counter;
            if (effect_counter == 0) {
                effect = nullptr;
                std::cout << "The effect has worn off.\n";
                std::cout << "Press Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
            }
        }
        return true;
    }
    return false;
}

/**
 * @brief Moves the Minotaur randomly or strategically toward the robot or an effect.
 * It prioritizes the following actions:
 * 
 *  1. Move toward the robot and handle interaction if the robot is adjacent.
 * 
 *  2. Destroy a special effect if the Minotaur can move to its position.
 * 
 *  3. If neither is possible, the Minotaur moves randomly to a valid position.
 * 
* The Minotaur cannot move through walls and avoids invalid positions.
 */
void Game::move_minotaur() {
    Cell m = matrix.get_minotaur();
    bool moved = false;

    for (int direction = 0; direction < directions.size(); ++direction) {
        int new_x = m.x + dx[direction];
        int new_y = m.y + dy[direction];

        if (matrix.is_robot(new_x, new_y)) {
            handle_minotaur(new_x, new_y);
            if (is_minotaur_alive && is_robot_alive) return;
            matrix.clear(m);
            return;
        }
        else if (matrix.is_effect(new_x, new_y)) {
            matrix.set_minotaur(new_x, new_y);
            matrix.clear(m);
            std::cout << "The Minotaur destroyed the special item!\n";
            std::cout << "Press Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            return;
        }
    }

    while (!moved) {
        int direction = matrix.get_random(UP, RIGHT);
        int new_x = m.x + dx[direction];
        int new_y = m.y + dy[direction];

        if (matrix.is_wall(new_x, new_y)) {
            continue;
        }
        else if (validate(new_x, new_y)) {
            matrix.set_minotaur(new_x, new_y);
            matrix.clear(m);
            moved = true;
        }
    }
}

// Validates the user input for movement direction or quit
void Game::validate_input(int& direction, std::string input) {
    if (input == "W" || input == "w") {
        direction = UP;
    }
    else if (input == "S" || input == "s") {
        direction = DOWN;
    }
    else if (input == "A" || input == "a") {
        direction = LEFT;
    }
    else if (input == "D" || input == "d") {
        direction = RIGHT;
    }
    else if (input == "Q" || input == "q") {
        direction = QUIT;
        std::cout << "Thanks for playing!\n";
        state = "You quit.";
        running = false;
    }
    else {
        direction = ERROR;
        std::cout << "Unknown command\n\n";
    }
}

// Executes the robot's movement, then moves the Minotaur and prints the game state
void Game::move(int direction) {
    bool moved = false;
    moved = move_robot(direction);
    if (!moved) return;
    if (is_minotaur_alive) move_minotaur();
    if (is_robot_alive) print();
    else running = false;
}

/**
 * @brief Main game loop to handle user input and manage the game state.
          The function waits for user input to determine the robot's movement.
          Validates the input and processes the move if valid.
          If the user decides to quit, the loop ends. 
          At the end of the game, the current state and maze configuration
          are saved to a file using the `file_manager`.
 */
void Game::run() {
    print();
    std::string input;
    while (running) {
        std::cout << "> ";
        std::cin >> input;
        std::cout << "\n";
        int direction;
        validate_input(direction, input);
        if (direction == ERROR) 
            continue;
        if (direction != QUIT) 
            move(direction);
    }

    file_manager.write_state(state, matrix);
}