#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <set>

using namespace std;

ofstream out("output16.txt");

const int CHANGE_DIR_COST_FACTOR = 1000;
const int N = 141;
int best = 1e9;

int best_for_pos[N][N][4];
char mp[N][N];

enum Direction
{
    RIGHT = 0,
    DOWN,
    LEFT,
    UP,
    COUNT
};

string dir_to_str(Direction dir)
{
    switch (dir)
    {
    case RIGHT:
        return "RIGHT";
    case DOWN:
        return "DOWN";
    case LEFT:
        return "LEFT";
    case UP:
        return "UP";
    }
    return "UNKNOWN";
}

int dir_distance(Direction dir, Direction dir2)
{
    return min(abs(dir - dir2), 4 - abs(dir - dir2));
}

struct Vector2
{
    int x, y;

    bool operator==(const Vector2 &v) const
    {
        return x == v.x && y == v.y;
    }

    bool operator<(const Vector2 &v) const
    {
        return x < v.x || (x == v.x && y < v.y);
    }

    Vector2 move(Direction dir)
    {
        switch (dir)
        {
        case UP:
            return {x, y - 1};
        case DOWN:
            return {x, y + 1};
        case LEFT:
            return {x - 1, y};
        case RIGHT:
            return {x + 1, y};
        }

        return {x, y};
    }
};

set<Vector2> visited;
Vector2 start_pos, end_pos;


void dfs(Vector2 pos, Vector2 prev, Direction dir, int cost)
{
    if (cost >= best)
        return;

    if (best_for_pos[pos.x][pos.y][dir] < cost)
        return;

    // cout << "Pos: " << pos.x << ", " << pos.y << " | Dir:" << dir_to_str(dir) << " Cost: " << cost << endl;
    best_for_pos[pos.x][pos.y][dir] = cost;

    if (pos == end_pos)
    {
        best = min(best, cost);
        out << "Path: " << cost << endl;
        // for (auto &p : path)
        //     out << p.x << ", " << p.y << endl;
        // out << "-----------------" << endl;
        return;
    }

    vector<Direction> dirs_to_check = {dir, (Direction)((dir + 1) % COUNT), (Direction)((dir + 3) % COUNT), (Direction)((dir + 2) % COUNT)};

    for (int i = 0; i < dirs_to_check.size(); i++)
    {
        Direction next_dir = dirs_to_check[i];
        Vector2 next = pos.move(next_dir);
        if (next == prev)
            continue;
        // if next is in path > continue
        // if (find(path.begin(), path.end(), next) != path.end())
        //     continue;
        if (visited.find(next) != visited.end())
            continue;

        if (mp[next.x][next.y] == '#')
            continue;

        // auto next_path = path;
        // next_path.push_back(next);
        visited.insert(next);
        // dfs(next, pos, next_dir, (cost + 1) + CHANGE_DIR_COST_FACTOR * dir_distance(next_dir, dir), next_path);
        dfs(next, pos, next_dir, (cost + 1) + CHANGE_DIR_COST_FACTOR * dir_distance(next_dir, dir));
        visited.erase(next);
    }
}

int main()
{
    auto cin = ifstream("input16.txt", ios::in);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            cin >> mp[i][j];

            if (mp[i][j] == 'S')
                start_pos = {i, j};
            if (mp[i][j] == 'E')
                end_pos = {i, j};
        }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << mp[i][j];
        cout << endl;
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < COUNT; k++)
                best_for_pos[i][j][k] = 1e9;

    // dfs(start_pos, start_pos, RIGHT, 0, {start_pos});
    dfs(start_pos, start_pos, RIGHT, 0);

    cout << "Best: " << best-1000 << endl;
}