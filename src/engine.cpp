#include "engine.h"
#include "console_painter..h"
#include "gui_painter.h"

Engine::Engine(): field(20, 10, 20)
{
    field.Init();
}

void Engine::Run()
{
    // AbstractPainter* painter = new ConsolePainter();
    AbstractPainter* painter = new GuiPainter();
    while (true)
    {
        painter->DrawField(field);
        // get user input
        char c = getchar();
        // process user input
    }
}