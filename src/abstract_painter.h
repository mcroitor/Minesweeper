#pragma once

#include "field.h"
#include "point.h"
#include <string>


struct AbstractPainter{
    virtual ~AbstractPainter() = default;
    virtual void ClearScreen() const = 0;
    virtual void DrawField(Field) const = 0;
    virtual void DrawMessage(const std::string&) const = 0;
    virtual void DrawCursor(Point) const = 0;
};