#include "field.h"
#include <ctime>

Field::Field(int width, int height, int nr_mines) : width(width), height(height), nr_mines(nr_mines)
{
    cells.resize(height);
    for (int i = 0; i < height; i++)
    {
        cells[i].resize(width);
        for (int j = 0; j < width; j++)
        {
            cells[i][j] = Cell(false);
        }
    }
    // set mines
    srand(time(NULL));
    for (int i = 0; i < nr_mines; i++)
    {
        int x = rand() % width;
        int y = rand() % height;
        if (cells[y][x].HasMine())
        {
            i--;
            continue;
        }
        cells[y][x] = Cell(true);
    }
}

Field::~Field()
{
}

int Field::GetWidth()
{
    return width;
}

int Field::GetHeight()
{
    return height;
}

void Field::Init()
{
    // count neighbours
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cells[i][j].SetNeighbors(CountNeighbors(j, i));
        }
    }
}

void Field::OpenCell(int x, int y)
{
    cells[y][x].Open();
}

bool Field::IsCellFlagged(int x, int y) const
{
    return cells[y][x].GetState() == State::Flagged;
}

bool Field::IsCellOpened(int x, int y) const
{
    return cells[y][x].GetState() == State::Opened;
}

void Field::ToggleFlag(int x, int y)
{
    cells[y][x].ToggleFlag();
}

Cell Field::GetCell(int x, int y) const
{
    return cells[y][x];
}

int Field::CountNeighbors(int x, int y)
{
    int count = 0;
    for (int i = y - 1; i <= y + 1; i++)
    {
        for (int j = x - 1; j <= x + 1; j++)
        {
            if (i >= 0 && i < height && j >= 0 && j < width)
            {
                count += cells[i][j].HasMine();
            }
        }
    }
    return count;
}

int Field::GetNeighbors(int x, int y) const
{
    return cells[y][x].GetNeighbors();
}

void Field::OpenNeighbors(int x, int y)
{
    for (int i = y - 1; i <= y + 1; i++)
    {
        for (int j = x - 1; j <= x + 1; j++)
        {
            if (i >= 0 && i < height && j >= 0 && j < width)
            {
                if (!cells[i][j].HasMine() && !IsCellOpened(j, i))
                {
                    OpenCell(j, i);
                    if (cells[i][j].GetNeighbors() == 0)
                    {
                        OpenNeighbors(j, i);
                    }
                }
            }
        }
    }
}

bool Field::IsOpened() const
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // if cell is not opened and it is not a mine
            if (!IsCellOpened(j, i) && !cells[i][j].HasMine())
            {
                return false;
            }
        }
    }
    return true;
}