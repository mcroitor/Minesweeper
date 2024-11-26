#pragma once

#include <string>
#include "state.h"

class Cell
{
    State state;
    bool has_mine;
    int neighbors;

public:
    Cell(bool has_mine = false);
    Cell(const Cell &cell);
    ~Cell();
    int GetNeighbors() const;
    void SetNeighbors(int neighbors);
    State GetState() const;
    void Open();
    void ToggleFlag();
    std::string ToString() const;
    bool HasMine() const;
};
