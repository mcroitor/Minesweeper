#pragma once

#include "field.h"

struct AbstractPainter{
    virtual void DrawField(Field) = 0;
};