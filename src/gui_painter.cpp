#include "gui_painter.h"
#include <iostream>
#include <string>
#include <format>

void GuiPainter::DrawField(Field field)
{
    // Set cursor position to the top-left corner of the console
    std::cout << "\033[0;0H";
    // Draw the field
    std::cout << std::format("+{}+\n", std::string(field.GetWidth(), '-'));
    for (int y = 0; y < field.GetHeight(); y++)
    {
        std::cout << "|";
        for (int x = 0; x < field.GetWidth(); x++)
        {
            if(field.IsCellOpened(x, y))
            {
                if(field.IsCellFlagged(x, y))
                {
                    std::cout << "P";
                }
                else
                {
                    int mines = field.GetNeighbors(x, y);
                    if(mines == 0)
                    {
                        std::cout << " ";
                    }
                    else
                    {
                        std::cout << mines;
                    }
                }
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << "|\n";
    }
    std::cout << std::format("+{}+\n", std::string(field.GetWidth(), '-'));
}