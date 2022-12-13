#include "includes.hpp"

struct Vector2
{
    int x = 0;
    int y = 0;
};

const int knobsCount = 10;
Vector2 Head, Tail;
vector<Vector2> visited;
Vector2 rope[knobsCount];
 
bool vector2Compare(const Vector2& a, const Vector2& b)
{
    return a.x == b.x && a.y == b.y; 
}

void increaseL(Vector2& L, const Vector2& R)
{
    L.x += R.x;
    L.y += R.y;
}

void evalNextKnob(const Vector2& a, Vector2& b)
{
    Vector2 aTob;
    aTob.x = a.x - b.x;
    aTob.y = a.y - b.y;

    if (abs(aTob.x) + abs(aTob.y) > 2)
    {
        if (abs(aTob.x) > 1)
            aTob.x /= 2;
        if (abs(aTob.y) > 1) 
            aTob.y /= 2;
    }
    else 
    {
        aTob.x /= 2;
        aTob.y /= 2;
    }

    increaseL(b, aTob);
}

void addVisited()
{
    for (Vector2 place : visited)
    {
        if (vector2Compare(place, rope[knobsCount - 1]))
            return;
    }

    visited.push_back(rope[knobsCount - 1]);
}

void moveRope(const char& dir, const int& mv)
{
    Vector2 move;
    if (dir == 'U')
        move.y = 1;
    else if (dir == 'R')
        move.x = 1;
    else if (dir == 'D')
        move.y = -1;
    else
        move.x = -1;

    for (int i = 0; i < mv; i++)
    {
        increaseL(rope[0], move);
        for (int knob = 1; knob < knobsCount; knob++)
        {
            if (vector2Compare(rope[knob - 1], rope[knob]))
                break;
            evalNextKnob(rope[knob - 1], rope[knob]);
        }
        addVisited();
    }
}

int main()
{
    char direction;
    int move;
    ifstream input("input9.txt", std::ios::in);

    if (input.good())
    {
        while (!input.eof())
        {
            input >> direction >> move;

            moveRope(direction, move);
        }
        input.close();
    }

    cout << visited.size() << endl;
    return 0;
}