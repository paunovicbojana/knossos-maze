#pragma once

/**
 * @file fog.h
 * @brief This header file contains inherited class Fog
          that returns the name of the effect
 * @author Bojana Paunovic
 * @date 28.12.2024.
 */

#include "effect.h"

struct Fog : Effect {
    std::string get_name() override {
        return "war fog";
    }
};