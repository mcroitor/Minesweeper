#include "engine.h"
#include "console_painter..h"
#include "gui_painter.h"

Engine::Engine() : 
    field{20, 10, 20},
    cursor{.x = 0, .y = 0},
    painter(new GuiPainter)
{
    field.Init();
}

Engine::~Engine(){
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
        char c = getchar();
        // char c = GetAsyncCharState();
        // process user input
        switch (c)
        {
        case 'w':
            cursor.y = cursor.y <= 1 ? 1 : cursor.y - 1;
            break;
        case 's':
            cursor.y = cursor.y >= field.GetHeight() ?
                field.GetHeight() :
                cursor.y + 1;
            break;
        case 'a':
            cursor.x = cursor.x <= 1 ? 1 : cursor.x - 1;
            break;
        case 'd':
            cursor.x = cursor.x >= field.GetWidth() ?
                field.GetWidth() :
                cursor.x + 1;
            break;
        case 'q':
            return;
        // ' ' - mark / unmark cell
        case ' ':
            field.ToggleFlag(cursor.x, cursor.y);
            break;
        // enter - open cell
        case '\n':
            field.OpenCell(cursor.x, cursor.y);
            break;
        }
    }
}