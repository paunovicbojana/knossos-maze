#pragma once

/**
 * @file cell.h
 * @brief This header file contains class Cell for better 
            organization and code readability
 * @author Bojana Paunovic
 * @date 28.12.2024.
 */

class Cell {
    char object;         // An object in the cell
public:
    int x, y;            // Coordinates of the cell
    bool is_visited;     // Flag indicating whether the cell has been visited

    // Default constructor
    Cell() : x(0), y(0), object('#'), is_visited(false) {}
    // Parameterized constructor
    Cell(int x, int y, char object, bool is_visited = false)
        : x(x), y(y), object(object), is_visited(is_visited) {}

    Cell& operator=(char c) { object = c; return *this; }
    bool operator==(char c) const { if (object == c) return true; return false; }
    bool operator!=(char c) const { if (object != c) return true; return false; }
    friend std::ostream& operator<<(std::ostream& s, const Cell& c) {
        s << c.object;
        return s;
    }
};
