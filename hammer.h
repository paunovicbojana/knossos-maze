#pragma once

/**
 * @file hammer.h
 * @brief This header file contains inherited class Hammer
          which indicates that it can break a wall
 * @author Bojana Paunovic
 * @date 28.12.2024.
 */

#include "effect.h"

struct Hammer : Effect {
    std::string get_name() override {
        return "hammer";
    }
    bool break_wall() override { return true; }
};
