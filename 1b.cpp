#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;


int main()
{
    auto cin = ifstream("input.txt", ios::in);
    vector<int> a;
    map<int, int> b;

    int x, y;
    while (cin >> x >> y)
    {
        a.push_back(x);

        b[y]++;
    }

    int similarity = 0;

    for (auto x : a)
        similarity += x * b[x];

    cout << similarity << endl;
}