#pragma once

#include "abstract_painter.h"

struct GuiPainter : AbstractPainter
{
    void DrawField(Field field) override;
};