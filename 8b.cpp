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

    Vector2 operator+(Vector2 o)
    {
        return {x+o.x, y+o.y};
    }

    Vector2 operator-(Vector2 o)
    {
        return {x-o.x, y-o.y};
    }

    Vector2 operator*(int t)
    {
        return {x*t, y*t};
    }

    vector<Vector2> antis(Vector2 b)
    {
        Vector2 a = *this;
        vector<Vector2> v;
        // a + t * (a - b)
        int t = 1;
        while (true)
        {
            Vector2 x = a + (a - b) * t;
            if (x.x < 0 || x.x >= N || x.y < 0 || x.y >= N)
                break;
            v.push_back(x);
            t++;
        }
        // b + t * (b - a)
        t = 1;
        while (true)
        {
            Vector2 x = b + (b - a) * t;
            if (x.x < 0 || x.x >= N || x.y < 0 || x.y >= N)
                break;
            v.push_back(x);
            t++;
        }
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
    {
        for (int j = 0; j < N; j++)
        {
            if (mp[i][j] != '.')
            {
                // cout << mp[i][j];
                ct++;
            }
            else
            {
                ct += anti[i][j];
                // cout << (anti[i][j] ? '#' : '.');
            }
        }

        // cout << endl;
    }
    cout << "Count: " << ct << endl;
}