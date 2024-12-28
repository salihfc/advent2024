#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

#define int long long

using namespace std;

vector<string> patterns;
map<string, int> ct;

bool ends_with(const string &str, const string &suffix)
{
    return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

int check_expression(const string &expression)
{
    if (expression.empty())
        return 1;
    
    if (ct.find(expression) != ct.end())
        return ct[expression];

    int count = 0;

    for (const auto& pattern : patterns)
    {
        if (ends_with(expression, pattern))
        {
            // check the rest of the expression
            count += check_expression(expression.substr(0, expression.size() - pattern.size()));
        }
    }

    return ct[expression] = count;
}

signed main()
{
    auto cin = ifstream("input19.txt", ios::in);
    string line;
    getline(cin, line);
    stringstream ss(line);
    string pattern;
    while (ss >> pattern)
        patterns.push_back(pattern);

    cout << "Patterns: " << patterns.size() << endl;
    for (auto pattern : patterns)
        cout << pattern << endl;
    cout << endl;

    getline(cin, line); // Skip empty line

    int count = 0;
    while (getline(cin, line))
    {
        cout << line << endl;
        count += check_expression(line);
    }

    cout << "Count: " << count << endl;
}   