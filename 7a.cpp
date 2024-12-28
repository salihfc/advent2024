#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

#define int long long
using namespace std;

int read_int(string line)
{
    int x = 0;
    for (char c : line)
    {
        if (c < '0' || c > '9')
            return x;
        x = x * 10 + c - '0';
    }
    return x;
}

vector<string> tokenize(string line, char delim)
{
    vector<string> tokens;
    string token;
    for (char c : line)
    {
        if (c == delim)
        {
            tokens.push_back(token);
            token = "";
        }
        else
        {
            token += c;
        }
    }

    tokens.push_back(token);
    return tokens;
}

enum class OP
{
    ADD = 1,
    MUL = 2,
};

bool rec(int idx, int v, OP op, const vector<int> &params, int target)
{
    int next_v = op == OP::ADD ? v + params[idx] : v * params[idx];

    if (idx+1 == params.size())
    {
        // cout << "v: " << next_v << endl;
        return next_v == target;
    }

    if (next_v > target)
        return false;

    return rec(idx + 1, next_v, OP::ADD, params, target) ||
           rec(idx + 1, next_v, OP::MUL, params, target);
}

bool check(int res, vector<int> params)
{
    return rec(1, params[0], OP::ADD, params, res) ||
           rec(1, params[0], OP::MUL, params, res);
}

signed main()
{
    auto cin = ifstream("input7.txt", ios::in);
    string line;
    int total = 0;
    while (getline(cin, line))
    {
        vector<string> tokens = tokenize(line, ' ');
        int res = read_int(tokens[0]);
        vector<int> params;
        for (int i = 1; i < tokens.size(); i++)
        {
            params.push_back(read_int(tokens[i]));
        }

        // cout << "res: " << res << endl;
        if (check(res, params))
            total += res;
    }

    cout << "Total: " << total << endl;
}