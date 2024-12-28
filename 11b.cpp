#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <unordered_map>

#define int long long
#define TRACE(x) cout << #x << " = " << x << endl
using namespace std;

const int N = 8;
const int Q = 75;

unordered_map<int, int> dp[Q + 1];

int len(int x)
{
    int res = 0;
    while (x > 0)
    {
        res++;
        x /= 10;
    }
    return res;
}

int magnitude(int x)
{
    int res = 1;
    for (int i = 0; i < x; i++)
        res *= 10;
    return res;
}

int calc(int x, int iters)
{
    if (iters == 0)
        return 1;

    if (dp[iters].find(x) != dp[iters].end())
        return dp[iters][x];

    if (x == 0)
        return dp[iters][x] = calc(1, iters - 1);
    
    int len_x = len(x);
    if (len_x % 2 == 0)
    {
        int mag = magnitude(len_x / 2);
        return dp[iters][x] = calc(x / mag, iters -1 ) + calc(x % mag, iters - 1);
    }

    return dp[iters][x] = calc(x * 2024, iters - 1);
}


signed main()
{
    auto cin = ifstream("input11.txt", ios::in);
    auto cout = ofstream("output11.txt", ios::out);

    int q = Q;
    int total = 0;
    int x;

    for (int i = 0; i < N; i++)
    {
        cin >> x;
        int res = calc(x, q);
        cout << x << " " << res << endl;
        total += res;
    }
    
    cout << total << endl;
}