#pragma once

#include "abstract_painter.h"

struct ConsolePainter : AbstractPainter
{
    void DrawField(Field field) const override;
    void DrawMessage(const std::string&) const override;
    void DrawCursor(Point) const override;
};