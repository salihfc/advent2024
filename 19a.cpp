#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

vector<string> patterns;

bool ends_with(const string &str, const string &suffix)
{
    return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

bool check_expression(const string &expression)
{
    if (expression.empty())
        return true;

    for (const auto& pattern : patterns)
    {
        if (ends_with(expression, pattern))
        {
            // check the rest of the expression
            if (check_expression(expression.substr(0, expression.size() - pattern.size())))
                return true;
        }
    }
    return false;
}

int main()
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