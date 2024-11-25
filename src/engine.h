#pragma once

#include "field.h"
#include "point.h"
#include "abstract_painter.h"

class Engine{
    Field field;
    Point cursor;
    AbstractPainter* painter;
public:
    Engine();
    ~Engine();
    void Run();
};