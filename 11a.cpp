#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

#define int long long
#define TRACE(x) cout << #x << " = " << x << endl
using namespace std;

const int N = 8;
vector <int> v, w;

void print_vector(vector<int>& v, ostream& out = cout)
{
    for (int i = 0; i < v.size(); i++)
        out << v[i] << " ";
    out << endl;
}

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

void proc(int x, vector<int>& u)
{
    if (x == 0)
    {
        u.push_back(1);
        return;
    }

    int len_x = len(x);
    if (len_x % 2 == 0)
    {
        int mag = magnitude(len_x / 2);
        u.push_back(x / mag);
        u.push_back(x % mag);
        return;
    }

    u.push_back(x * 2024);
}

void update(vector<int>& v, vector<int>& w, bool& backwards)
{
    // backwards=false  v -> w
    // backwards=true   w -> v
    if (backwards)
    {
        v.clear();
        for (auto x : w)
            proc(x, v);
    }
    else
    {
        w.clear();
        for (auto x : v)
            proc(x, w);
    }

    backwards = !backwards;
}

signed main()
{
    auto cin = ifstream("input11.txt", ios::in);
    auto cout = ofstream("output11.txt", ios::out);

    int x;
    for (int i = 0; i < N; i++)
    {
        cin >> x;
        v.push_back(x);
    }
    
    print_vector(v, cout);

    int q = 25;
    bool backwards = false;

    for (int i = 0; i < q; i++)
    {
        std::cout << i << std::endl;
        update(v, w, backwards);
        // print_vector(v, cout);
    }

    TRACE(v.size());

}