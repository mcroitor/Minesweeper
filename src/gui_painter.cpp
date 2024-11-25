#include "gui_painter.h"
#include <iostream>
#include <string>
#include <format>

void GuiPainter::ClearScreen() const
{
    // Clear the screen
    std::cout << "\033[2J";
}

void GuiPainter::DrawField(Field field) const
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
            std::cout << field.GetCell(x, y).ToString();
        }
        std::cout << "|\n";
    }
    std::cout << std::format("+{}+\n", std::string(field.GetWidth(), '-'));
}

void GuiPainter::DrawMessage(const std::string &message) const
{
    std::cout << message << std::endl;
}

void GuiPainter::DrawCursor(Point cursor) const
{
    // set the cursor position to the cell, draw the cursor
    std::cout << std::format("\033[{};{}H", cursor.y + 1, cursor.x + 1);
    std::cout << "X";
}