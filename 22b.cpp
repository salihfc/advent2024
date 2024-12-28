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

vector<int> secret(int a, int r)
{
    vector<int> v;
    while (r--)
    {
        v.push_back(a % 10);
        a = next(a);
    }
    v.push_back(a % 10);
    return v;
}

struct Seq {
    int d[4];

    bool operator<(const Seq &s) const
    {
        for (int i = 0; i < 4; i++)
        {
            if (d[i] < s.d[i]) return true;
            if (d[i] > s.d[i]) return false;
        }
        return false;
    }
};

map<Seq, int> seq_gain(vector<int> v)
{
    map<Seq, int> m;
    for (int i = 0; i + 4 < v.size(); i++)
    {
        Seq s;
        for (int j = 0; j < 4; j++)
        {
            s.d[j] = v[i + j + 1] - v[i + j];
        }

        // if s is already in m skip
        if (m.find(s) != m.end()) continue;
        m[s] = v[i + 4];
    }
    return m;
}

void merge(map<Seq, int> &a, map<Seq, int> &b)
{
    for (auto [k, v] : b)
    {
        if (a.find(k) == a.end()) a[k] = v;
        else a[k] = a[k] + v;
    }
}

signed main()
{
    auto cin = ifstream("input22.txt", ios::in);
    int sum = 0;
    map<Seq, int> m;
    for (int i = 0; i < N; i++)
    {
        int x;
        cin >> x;
        vector<int> v = secret(x, 2000);
        map<Seq, int> n = seq_gain(v);
        merge(m, n);
    }

    // find best sequence
    int best = 0;
    Seq best_seq;
    for (auto [k, v] : m)
    {
        if (v > best)
        {
            best = v;
            best_seq = k;
        }
    }

    cout << "Best sequence: ";
    for (int i = 0; i < 4; i++)
    {
        cout << best_seq.d[i] << " ";
    }

    cout << "Gain: " << best << endl;

    // Output:
    // Best sequence: 0 1 -1 1 Gain: 1710
}