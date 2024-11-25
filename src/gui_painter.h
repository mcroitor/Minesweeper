#pragma once

#include "abstract_painter.h"

struct GuiPainter : AbstractPainter
{
    void DrawField(Field field) const override;
    void DrawMessage(const std::string& message) const override;
    void DrawCursor(Point cursor) const override;
};