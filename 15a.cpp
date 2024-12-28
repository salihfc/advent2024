#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <sstream>
using namespace std;

auto in = ifstream("input15.txt", ios::in);
auto out = ofstream("output15.txt", ios::out);
// #define out cout

const int N = 50;
const int COM_LINES = 20;

char mp[N][N];
string coms;

struct Vector2 
{
    int x, y;

    bool operator==(const Vector2& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vector2& other) const
    {
        return !(*this == other);
    }

    Vector2 move(char c)
    {
        switch (c)
        {
            case '^': return {x - 1, y};
            case 'v': return {x + 1, y};
            case '<': return {x, y - 1};
            case '>': return {x, y + 1};

            default: assert(false);
        }
    }
};

bool is_wall(Vector2 v)
{
    assert(0 <= v.x && v.x < N);
    assert(0 <= v.y && v.y < N);
    return mp[v.x][v.y] == '#';
}

bool is_cell_empty(Vector2 v)
{
    assert(0 <= v.x && v.x < N);
    assert(0 <= v.y && v.y < N);
    return mp[v.x][v.y] == '.';
}

bool is_box(Vector2 v)
{
    assert(0 <= v.x && v.x < N);
    assert(0 <= v.y && v.y < N);
    return mp[v.x][v.y] == 'O';
}

void print_map()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            out << mp[i][j];
        out << endl;
    }
}

int main()
{
    Vector2 robot;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            in >> mp[i][j];
            if (mp[i][j] == '@')
            {
                robot.x = i;
                robot.y = j;
            }
        }
    stringstream ss;
    for (int i = 0; i < COM_LINES; i++)
    {
        string line;
        in >> line;
        ss << line;
    }
    coms = ss.str();
    print_map();
    out << coms << endl;

    for (auto c : coms)
    {
        out << "--------------------------------------------------------" << endl;
        out << "Robot: " << robot.x << " " << robot.y << endl;
        out << "Command: " << c << endl;

        Vector2 next = robot.move(c);
        if (is_wall(next))
        {
            print_map();
            continue;
        }
        
        if (is_cell_empty(next))
        {
            mp[robot.x][robot.y] = '.';
            mp[next.x][next.y] = '@';
            robot = next;
            print_map();
            continue;
        }

        // next is box
        Vector2 next_next = next.move(c);
        while (is_box(next_next))
            next_next = next_next.move(c);
        
        // if next_next is empty
        // move everything using 'c'
        // else do nothing     
        if (is_cell_empty(next_next))
        {
            // robot -> empty
            // next -> robot
            // next+1..next_next -> box
            mp[robot.x][robot.y] = '.';
            mp[next.x][next.y] = '@';
            Vector2 box = next.move(c);
            while (box != next_next)
            {
                mp[box.x][box.y] = 'O';
                box = box.move(c);
            }
            // also make next_next box
            mp[next_next.x][next_next.y] = 'O';
            robot = next;

            print_map();
            continue;
        }
    }

    int ROW_FACTOR = 100;
    int cnt = 0;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (mp[i][j] == 'O')
                cnt += i * ROW_FACTOR + j;
            
    out << "Result: " << cnt << endl;
}