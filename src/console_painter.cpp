#include "console_painter..h"

#include <iostream>

void ConsolePainter::DrawField(Field field)
{
    // draw top border
    for(int i = 0; i < field.GetWidth() + 2; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;

    // draw field
    for(int y = 0; y < field.GetHeight(); y++) {
        std::cout << "|";
        for(int x = 0; x < field.GetWidth(); x++) {
            if(field.IsCellOpened(x, y)) {
                std::cout << field.GetNeighbors(x, y);
            } else if(field.IsCellFlagged(x, y)) {
                std::cout << "F";
            } else {
                std::cout << " ";
            }
        }
    }
}