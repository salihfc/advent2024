#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <string>

// using namespace std;
auto cout = std::ofstream("output6.txt", std::ios::out);

const int N = 130;
const int M = 130;

char grid[N][M];
bool visited[N][M][4];

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

bool is_loop(char grid_map[N][M], Vector2 start_pos, bool write_log)
{
    auto pos_valid = [](Vector2 pos) { return pos.x >= 0 && pos.x < N && pos.y >= 0 && pos.y < M; };
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            for (int k = 0; k < 4; k++)
                visited[i][j][k] = false;
    
    Direction start_dir = Direction::UP;
    Vector2 pos = start_pos;
    Direction dir = start_dir;
    while (pos_valid(pos))
    {
        if (write_log) 
            cout << "pos: " << pos.x << " " << pos.y << std::endl;

        visited[pos.x][pos.y][int(dir)] = true;
        Vector2 next_pos = pos.next_pos(dir);
        while (pos_valid(next_pos) && grid[next_pos.x][next_pos.y] == '#')
        {
            dir = next_dir(dir);
            // Update next_pos with new direction
            next_pos = pos.next_pos(dir);
        }

        pos = next_pos;
        // Passing through a position with same direction
        // guarantees a loop
        if (pos_valid(pos) && visited[pos.x][pos.y][int(dir)])
        {
            if (write_log)
                cout << "Looped at: " << pos.x << " " << pos.y << " with dir: " << int(dir) << std::endl;
            return true;
        }
    }

    return false;
}

void print_grid()
{
    cout << "Cols:  ";
    for (int j = 0; j < M; j++)
        cout << j << " ";
    cout << std::endl;

    for (int i = 0; i < N; i++)
    {
        cout << "Row " << i << ": ";
        for (int j = 0; j < M; j++)
            cout << grid[i][j] << " ";
        cout << std::endl;
    }
}

int main()
{
    auto cin = std::ifstream("input6.txt", std::ios::in);
    Vector2 start;
    Direction dir = Direction::UP;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
        {
            cin >> grid[i][j];
            if (grid[i][j] == '^')
                start = Vector2(i, j);
        }

    int count = 0;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (grid[i][j] == '.')
            {
                grid[i][j] = '#';
                if (is_loop(grid, start, false))
                {
                    std::cout << "Loop found at: " << i << " " << j << std::endl;
                    cout << "Loop found at: " << i << " " << j << std::endl;
                    count++;
                    print_grid();
                    is_loop(grid, start, true);
                }
                grid[i][j] = '.';
                // exit(0);
            }

    cout << "Count: " << count << std::endl;
    std::cout << "Count: " << count << std::endl;
}