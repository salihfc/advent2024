#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;

#define cout out

auto out = ofstream("output20.txt", ios::out);

const int N = 141;
bool mp[N][N]; // 0 -> empty, 1 -> wall
int dist[N][N];

map<int, int> cheat; // [cheat_point_gain] = count

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

Vector2 S, E;

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
    auto cin = ifstream("input20.txt", ios::in);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            char c;
            cin >> c;
            mp[i][j] = c == '#';
            
            if (c == 'S')
            {
                S = {i, j};
                mp[i][j] = false;
            }
            else if (c == 'E')
            {
                E = {i, j};
                mp[i][j] = false;
            }
        }
    }

    int sp = shortest_path(S, E);
    cout << sp << endl;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (dist[i][j] == 1e9)
                cout << " \t";
            else
                cout << dist[i][j] << "\t";
        }
        cout << endl;
    }


    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (dist[i][j] == 1e9) continue;
            cout << "Checking cheat point at " << i << " " << j << " > dist: " << dist[i][j] << endl;

            // For each wall around this point
            // Check neighbours of that wall and see if they are higher dist than this point
            // If they are, cheat point gain is (dist[ox][oy] - dist[i][j] - 2)  {2 is the cost of moving through the wall}
            for (auto wall : Vector2{i, j}.neighbours())
            {
                if (!wall.valid() || !mp[wall.x][wall.y]) continue;

                for (auto neighbour : wall.neighbours())
                {
                    if (!neighbour.valid() || mp[neighbour.x][neighbour.y]) continue;

                    if (dist[neighbour.x][neighbour.y] > dist[i][j] + 2)
                    {
                        int cheat_point_gain = dist[neighbour.x][neighbour.y] - dist[i][j] - 2;
                        cout << "Cheat point gain: " << cheat_point_gain << " [wall]: " << "(" << wall.x << "," << wall.y << ")" << " neigh_dist:" << dist[neighbour.x][neighbour.y] << endl;
                        cheat[cheat_point_gain]++;
                    }
                }
            }
        }
    }

    int min_limit = 100;
    int gain_with_min_limit = 0;
    for (auto [gain, count] : cheat)
    {
        cout << "Cheat point gain: " << gain << " Count: " << count << endl;
    
        if (gain >= min_limit)
            gain_with_min_limit += count;
    }

    cout << "Total cheat points with min limit: " << gain_with_min_limit << endl;
}