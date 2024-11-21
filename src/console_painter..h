#pragma once

#include "abstract_painter.h"

struct ConsolePainter : AbstractPainter
{
    void DrawField(Field field) override;
};