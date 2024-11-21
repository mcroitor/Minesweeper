#include "cell.h"

Cell::Cell(bool has_mine) : 
    has_mine(has_mine),
    neighbors(0),
    state(State::Closed)
{
}

Cell::Cell(const Cell &cell) :
    has_mine(cell.has_mine),
    neighbors(cell.neighbors),
    state(cell.state)
{
}

Cell::~Cell()
{
}

int Cell::GetNeighbors() const
{
    return neighbors;
}

void Cell::SetNeighbors(int neighbors)
{
    this->neighbors = neighbors;
}

State Cell::GetState() const
{
    return state;
}

void Cell::Open()
{
    state = State::Opened;
}

void Cell::ToggleFlag()
{
    switch (state)
    {
    case State::Closed:
        state = State::Flagged;
        break;
    case State::Flagged:
        state = State::Closed;
        break;
    default:
        break;
    }
}

std::string Cell::ToString() const
{
    switch (state)
    {
    case State::Closed:
        return "C";
    case State::Opened:
        if (has_mine)
            return "M";
    case State::Flagged:
        return "F";
    }
    return std::to_string(neighbors);
}