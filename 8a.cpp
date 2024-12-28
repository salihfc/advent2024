#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

const int N = 50;
char mp[N][N];
bool anti[N][N];

struct Vector2
{
    int x;
    int y;

    vector<Vector2> antis(Vector2 o)
    {
        vector<Vector2> v;
        // 2a-b
        v.push_back({2*x-o.x, 2*y-o.y});
        // 2b-a
        v.push_back({2*o.x-x, 2*o.y-y});
        return v;
    }
};

map <char, vector<Vector2>> q;

int main()
{
    auto cin = ifstream("input8.txt", ios::in);
    for (int i = 0; i < N; i++)
        cin >> mp[i];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            q[mp[i][j]].push_back({i, j});

    for (auto p: q)
    {
        char c = p.first;
        if (c == '.')
            continue;

        vector<Vector2> v = p.second;
        // cout << "Char: " << c << endl;
        // for (Vector2 x: v)
        //     cout << x.x << " " << x.y << endl;

        for (int i = 0; i < v.size(); i++)
        {
            for (int j = i+1; j < v.size(); j++)
            {
                vector<Vector2> a = v[i].antis(v[j]);
                for (Vector2 x: a)
                {
                    if (x.x >= 0 && x.x < N && x.y >= 0 && x.y < N)
                        anti[x.x][x.y] = true;
                }
            }
        }
    }


    int ct = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            ct += anti[i][j];
    cout << "Count: " << ct << endl;
}