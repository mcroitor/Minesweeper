#pragma once

#include "field.h"
#include "point.h"
#include <string>


struct AbstractPainter{
    virtual ~AbstractPainter() = default;
    virtual void ClearScreen() const = 0;
    virtual void DrawField(Field field) const = 0;
    virtual void DrawMessage(const std::string& message) const = 0;
    virtual void SetCursor(Point point) const = 0;
    virtual void DrawCursor(Point point) const = 0;
};