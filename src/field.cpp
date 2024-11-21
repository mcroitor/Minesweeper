#include "field.h"

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
    // TODO: implement this function
    return count;
}

int Field::GetNeighbors(int x, int y) const
{
    return cells[y][x].GetNeighbors();
}