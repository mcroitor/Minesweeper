#include "engine.h"
#include "console_painter..h"
#include "gui_painter.h"
#include <termios.h>
#include <unistd.h>

int __get_char()
{
    // get char without waiting for enter
    // do not show the char on the screen
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    // if the char is ESC, read two more chars to get the arrow key
    if (ch == 27)
    {
        getchar();
        ch = getchar();
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

Engine::Engine() : field{20, 10, 20},
                   cursor{.x = 1, .y = 1},
                   painter{new GuiPainter}
{
    painter->ClearScreen();
    field.Init();
}

Engine::~Engine()
{
    delete painter;
}

void Engine::Run()
{
    while (true)
    {
        painter->DrawField(field);
        painter->DrawCursor(cursor);
        // get user input
        // todo: input without screen echo
        char c = __get_char();
        // process user input
        switch (c)
        {
        // arrow up - move cursor up
        case 65:
            cursor.y = cursor.y <= 1 ? 1 : cursor.y - 1;
            break;
        case 66:
            cursor.y = cursor.y >= field.GetHeight() ? field.GetHeight() : cursor.y + 1;
            break;
        case 68:
            cursor.x = cursor.x <= 1 ? 1 : cursor.x - 1;
            break;
        case 67:
            cursor.x = cursor.x >= field.GetWidth() ? field.GetWidth() : cursor.x + 1;
            break;
        // esc - exit
        case 27:
            return;
        // 'f' - mark / unmark cell
        case 'f':
            field.ToggleFlag(cursor.x - 1, cursor.y - 1);
            break;
        // ' ' - open cell
        case ' ':
            field.OpenCell(cursor.x - 1, cursor.y - 1);
            if (field.GetCell(cursor.x - 1, cursor.y - 1).HasMine())
            {
                painter->DrawCursor({1, field.GetHeight() + 2});
                painter->DrawMessage("Game over!");
                return;
            }
            if (field.GetCell(cursor.x - 1, cursor.y - 1).GetNeighbors() == 0)
            {
                field.OpenNeighbors(cursor.x - 1, cursor.y - 1);
            }
            break;
        }
        // check if the game is won
        if (field.IsOpened())
        {
            painter->DrawCursor({1, field.GetHeight() + 2});
            painter->DrawMessage("You won!");
            return;
        }
    }
}