#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;

const int K = 3450;
const int U = 1024;
const int N = 71;

bool mp[N][N];
int dist[N][N];

struct Vector2
{
    int x, y;

    vector<Vector2> neighbours()
    {
        return {
            {x + 1, y},
            {x - 1, y},
            {x, y + 1},
            {x, y - 1}
        };
    }

    bool valid()
    {
        return x >= 0 && x < N && y >= 0 && y < N;
    }
};

vector<Vector2> v;

int shortest_path(Vector2 start, Vector2 end)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            dist[i][j] = 1e9;
    
    dist[start.x][start.y] = 0;
    queue<Vector2> q;
    q.push(start);

    while (!q.empty())
    {
        auto cur = q.front();
        q.pop();

        for (auto next : cur.neighbours())
        {
            if (!next.valid() || mp[next.x][next.y])
                continue;
            
            if (dist[next.x][next.y] > dist[cur.x][cur.y] + 1)
            {
                dist[next.x][next.y] = dist[cur.x][cur.y] + 1;
                q.push(next);
            }
        }
    }

    return dist[end.x][end.y];
}

int main()
{
    auto cin = ifstream("input18.txt", ios::in);
    for (int i = 0; i < K; i++)
    {
        int a, b;
        cin >> a >> b;
        v.push_back({a, b});
    }

    for (int i = 0; i < U; i++)
        mp[v[i].x][v[i].y] = true;

    for (int i = U; i < K; i++)
    {
        cout << "Checking " << i << ": " << v[i].x << " " << v[i].y << endl;
        mp[v[i].x][v[i].y] = true;

        int sp = shortest_path({0, 0}, {N - 1, N - 1});

        if (sp == 1e9)
        {
            cout << v[i].x << " " << v[i].y << endl;
            return 0;
        }
    }
}