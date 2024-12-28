#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

#define int long long

using namespace std;

const int N = 1771;
const int MOD = 16777216;

int mix(int a, int b)
{
    return a ^ b;
}

int prune(int a)
{
    return a % MOD;
}

int next(int a)
{
    a = prune(mix(a, a << 6)); // a * 64
    a = prune(mix(a, a >> 5)); // a / 32
    a = prune(mix(a, a << 11)); // a * 2048
    return a;
}

signed main()
{
    auto cin = ifstream("input22.txt", ios::in);
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        int x, save;
        cin >> x;
        save = x;

        int R = 2000;
        while (R--) x = next(x);
        cout << save << " -> " << x << endl;
        sum += x;
    }

    cout << "Total: " << sum << endl;
}