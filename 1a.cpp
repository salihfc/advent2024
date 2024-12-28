#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;


int main()
{
    auto cin = ifstream("input.txt", ios::in);
    vector<int> a,b;

    int x, y;
    while (cin >> x >> y)
    {
        a.push_back(x);
        b.push_back(y);
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int dist = 0;

    for (size_t i = 0; i < a.size(); i++)
    {
        dist += abs(a[i] - b[i]);
    }

    cout << dist << endl;
}