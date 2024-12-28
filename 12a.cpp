#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

#define TRACE2(x, y) cout << #x << " = " << x << " " << #y << " = " << y << endl;
#define TRACE(x) cout << #x << " = " << x << endl;

using namespace std;

const int N = 140;
char mp[N][N];
bool visited[N][N];

struct Vector2 {
    int x, y;
    Vector2(int x, int y) : x(x), y(y) {}

    vector<Vector2> neighbours()
    {
        vector<Vector2> result;
        result.push_back(Vector2(x - 1, y));
        result.push_back(Vector2(x + 1, y));
        result.push_back(Vector2(x, y - 1));
        result.push_back(Vector2(x, y + 1));
        return result;
    }
};

bool is_valid(Vector2 pos)
{
    return pos.x >= 0 && pos.x < N && pos.y >= 0 && pos.y < N;
}

int same_neighbour_count(Vector2 pos)
{
    if (is_valid(pos) == false) return 4;
    int count = 0;
    for (auto neighbour : pos.neighbours())
    {
        if (is_valid(neighbour) && mp[neighbour.x][neighbour.y] == mp[pos.x][pos.y])
            count++;
    }
    return count;
}

vector<Vector2> find_area(Vector2 pos)
{
    // TRACE2(pos.x, pos.y);
    vector<Vector2> result;
    // if (is_valid(pos) == false || visited[pos.x][pos.y] == true) return result;
    visited[pos.x][pos.y] = true;
    result.push_back(pos);

    for (auto neighbour : pos.neighbours())
    {
        if (is_valid(neighbour) && mp[neighbour.x][neighbour.y] == mp[pos.x][pos.y] && visited[neighbour.x][neighbour.y] == false)
        {
            vector<Vector2> neighbour_area = find_area(neighbour);
            for (auto n_pos : neighbour_area)
                result.push_back(n_pos);
        }
    }
    return result;
}

int area_cost(vector<Vector2> area)
{
    int area_size = area.size();
    int perim = 0;
    for (auto pos : area)
        perim += 4 - same_neighbour_count(pos);
    return area_size * perim;
}

void print_area(vector<Vector2> area)
{
    cout << "Area with: " << mp[area[0].x][area[0].y] << endl;
    for (auto pos : area)
        cout << "(" << pos.x << ", " << pos.y << ") " << endl;
    cout << "-------------" << endl;
}

int main()
{
    auto cin = ifstream("input12.txt", ios::in);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> mp[i][j];

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << mp[i][j] << " ";
        cout << endl;
    }

    int total_cost = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            if (visited[i][j] == false)
            {
                vector<Vector2> area = find_area(Vector2(i, j));
                print_area(area);
                int cost = area_cost(area);
                total_cost += cost;
            }
        }

    cout << "Total cost: " << total_cost << endl;
}