#pragma once

/**
 * @file sword.h
 * @brief This header file contains inherited class 
          Sword that can kill the Minotaur
 * @author Bojana Paunovic
 * @date 28.12.2024.
 */

#include "effect.h"

struct Sword : Effect {
    std::string get_name() override {
        return "sword";
    }
    void does(Game& g) override {
        std::cout << "You killed the Minotaur with a sword! Now find the exit.\n";
        std::cout << "Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        g.kill_minotaur();
    }
};
