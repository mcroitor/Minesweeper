#pragma once

#include "field.h"
#include "point.h"
#include "abstract_painter.h"

class Engine{
    Field field;
    Point cursor;
    AbstractPainter* painter;
public:
    Engine(int width, int height, int nr_mines);
    ~Engine();
    /// @brief Main game loop
    void Run();
};