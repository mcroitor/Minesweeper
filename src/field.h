#pragma once

#include <vector>
#include "cell.h"

using std::vector;

class Field
{
    int width;
    int height;
    int nr_mines;
    vector<vector<Cell>> cells;

public:
    Field(int width, int height, int nr_mines);
    ~Field();

    int GetWidth();
    int GetHeight();

    void Init();
    void OpenCell(int x, int y);
    void ToggleFlag(int x, int y);
    bool IsCellOpened(int x, int y) const;
    bool IsCellFlagged(int x, int y) const;
    Cell GetCell(int x, int y) const;
    int GetNeighbors(int x, int y) const;

private:
    int CountNeighbors(int x, int y);
};
