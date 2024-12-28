#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

const int N = 130;
const int M = 130;

char grid[N][M];
bool visited[N][M];

enum class Direction { UP, RIGHT, DOWN, LEFT };
Direction next_dir(Direction dir)
{
    return static_cast<Direction>((static_cast<int>(dir) + 1) % 4);
}

struct Vector2 {
    int x, y;
    Vector2(int x, int y) : x(x), y(y) {}
    Vector2() : x(0), y(0) {}
    Vector2 operator+(const Vector2& other) const { return Vector2(x + other.x, y + other.y);}
    Vector2 operator-(const Vector2& other) const { return Vector2(x - other.x, y - other.y);}
    Vector2 next_pos(Direction dir) const
    {
        switch (dir)
        {
            case Direction::UP: return Vector2(x - 1, y);
            case Direction::RIGHT: return Vector2(x, y + 1);
            case Direction::DOWN: return Vector2(x + 1, y);
            case Direction::LEFT: return Vector2(x, y - 1);
        };
        return Vector2();
    }
};

int main()
{
    auto cin = ifstream("input6.txt", ios::in);
    Vector2 start;
    Direction dir = Direction::UP;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
        {
            cin >> grid[i][j];
            if (grid[i][j] == '^')
                start = Vector2(i, j);
        }
    
    auto pos_valid = [](Vector2 pos) { return pos.x >= 0 && pos.x < N && pos.y >= 0 && pos.y < M; };
    
    Vector2 pos = start;
    while (pos_valid(pos))
    {
        visited[pos.x][pos.y] = true;
        Vector2 next_pos = pos.next_pos(dir);
        if (pos_valid(next_pos) && grid[next_pos.x][next_pos.y] == '#')
            dir = next_dir(dir);
        else
            pos = next_pos;
    }

    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (visited[i][j])
                count++;

    cout << "Count: " << count << endl;
}