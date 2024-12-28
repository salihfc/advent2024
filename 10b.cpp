#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <set>

#define TRACE(x) cout << #x << " = " << x << endl

using namespace std;

const int N = 50;

char mp[N][N];

struct Vector2
{
    int x, y;

    bool operator<(const Vector2 &other) const
    {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }

    vector<Vector2> neighbors()
    {
        vector<Vector2> res;
        if (x > 0)      res.push_back({x - 1, y});
        if (x < N - 1)  res.push_back({x + 1, y});
        if (y > 0)      res.push_back({x, y - 1});
        if (y < N - 1)  res.push_back({x, y + 1});
        return res;
    }
};


int main()
{
    auto cin = ifstream("input10.txt", ios::in);
    auto cout = ofstream("output10.txt", ios::out);

    for (int i = 0; i < N; i++)
        cin >> mp[i];
    
    vector<Vector2> by_height[10];
    map<Vector2, int> acc;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            by_height[mp[i][j] - '0'].push_back({i, j});
            if (mp[i][j] == '0')
                acc[{i, j}] = 1;
        }

    for (int i = 0; i <= 8; i++)
    {   
        cout << "At height " << i << ":\n";
        for (auto &v : by_height[i])
        {
            cout << v.x << " " << v.y << endl;
        }
        cout << "-----------------\n";

        for (auto &v : by_height[i])
        {
            // propagate
            for (auto &n : v.neighbors())
            {
                if ((mp[n.x][n.y]-'0') == i + 1)
                    acc[n] += acc[v];
            }
        }
    }

    // count sizes of by_height[9]
    int count = 0;
    for (auto &v : by_height[9])
    {
        count += acc[v];
        cout << "At " << v.x << " " << v.y << ": " << acc[v] << "\n";
    }

    TRACE(count);
    std::cout << count << std::endl;
}