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

Engine::Engine(int width, int height, int nr_mines) : field{width, height, nr_mines},
                   cursor{.x = 1, .y = 1},
                   painter{new GuiPainter}
{
    painter->ClearScreen();
    // write info usage
    painter->SetCursor({field.GetWidth() + 3, 1});
    painter->DrawMessage("Use arrow keys to move cursor");
    painter->SetCursor({field.GetWidth() + 3, 2});
    painter->DrawMessage("Press 'f' to mark / unmark cell");
    painter->SetCursor({field.GetWidth() + 3, 3});
    painter->DrawMessage("Press 'space' to open cell");
    painter->SetCursor({field.GetWidth() + 3, 4});
    painter->DrawMessage("Press triple 'esc' to exit");
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
        // check if the game is won
        if (field.IsOpened())
        {
            painter->SetCursor({1, field.GetHeight() + 2});
            painter->DrawMessage("You won!");
            return;
        }
        // get user input
        // todo: input without screen echo
        auto c = __get_char();
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
                painter->SetCursor({1, field.GetHeight() + 2});
                painter->DrawMessage("Game over!");
                return;
            }
            if (field.GetCell(cursor.x - 1, cursor.y - 1).GetNeighbors() == 0)
            {
                field.OpenNeighbors(cursor.x - 1, cursor.y - 1);
            }
            break;
        }
    }
}