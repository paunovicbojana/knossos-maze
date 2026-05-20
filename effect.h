#pragma once

/**
 * @file effect.h
 * @brief This header file contains base class Effect 
            which some special effects will inherit
 * @author Bojana Paunovic
 * @date 28.12.2024.
 */

#include <string>
#include "game.h"
class Game;
struct Effect {
    virtual ~Effect() = default;
    virtual std::string get_name() = 0;
    virtual void does(Game&) {};
    virtual bool break_wall() { return false; }
    Effect& operator=(const Effect&) = delete;
};