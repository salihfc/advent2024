#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <set>

using namespace std;

map<string, vector<string>> g;

pair<string, string> split(const string &s, char delim)
{
    auto i = s.find(delim);
    return {s.substr(0, i), s.substr(i + 1)};
}

set<pair<string, string>> edge;

int main()
{
    auto cin = ifstream("input23.txt", ios::in);
    string line;
    while (cin >> line)
    {
        // cout << line;
        auto p = split(line, '-');
        // cout << ": " << p.first << " " << p.second << endl;
        g[p.first].push_back(p.second);
        g[p.second].push_back(p.first);
        edge.insert(p);
        edge.insert({p.second, p.first});
    }

    set<set<string>> triples;

    for (auto &[k, v] : g)
    {
        for (auto &a : v)
        {
            for (auto &b : v)
            {
                if (a == b)
                    continue;
                
                if (edge.count({a, b}))
                {
                    triples.insert({k, a, b});
                }
            }
        }
    }

    int ct = 0;

    cout << "Triples: " << triples.size() << endl;

    for (auto &t : triples)
    {
        bool has_t = false;
        for (auto &s : t)
        {
            if (s[0] == 't')
            {
                has_t = true;
                break;
            }
        }
        if (has_t)
            ct++;
    }

    cout << "Count: " << ct << endl;
}