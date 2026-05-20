#pragma once

/**
 * @file shield.h
 * @brief This header file contains inherited class Shield that saves the Robot from the Minotaur in case of the attack
 * @author Bojana Paunovic
 * @date 28.12.2024.
 */

#include "effect.h"

struct Shield : Effect {
    std::string get_name() override {
        return "shield";
    }
    void does(Game&) override {
        std::cout << "Phew! The shield saved you from the Minotaur. Be careful!\n";
        std::cout << "Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
};
