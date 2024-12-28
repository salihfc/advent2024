#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <cassert>

using namespace std;
const int RULE_COUNT = 1176;
const int UPDATE_COUNT = 185;

map <int, vector<int>> nexts;

struct
{
    bool operator()(int a, int b) const 
    {
        // If a is in nexts of b, > invalid
        if (find(nexts[b].begin(), nexts[b].end(), a) != nexts[b].end())
            return false;
        return true;
    }
} sort_custom;

bool check_update_order(vector<int> update, map<int, vector<int>> dag)
{
    for (int i = 0; i < update.size(); i++)
        for (int j = i + 1; j < update.size(); j++)
        {
            int a = update[i];
            int b = update[j];

            // If a is in nexts of b, > invalid
            if (find(nexts[b].begin(), nexts[b].end(), a) != nexts[b].end())
                return false;
        }
    return true;
}

vector<int> fix_update_order(vector<int> update, map<int, vector<int>> dag)
{
    sort(update.begin(), update.end(), sort_custom);
    return update;
}

vector<int> parse_update(string update_line)
{
    vector<int> result;
    int i = 0;
    while (i < update_line.size())
    {
        int num = 0;
        while (i < update_line.size() && isdigit(update_line[i]))
        {
            num = num * 10 + (update_line[i] - '0');
            i++;
        }
        result.push_back(num);
        i++;
    }
    return result;
}

int main()
{
    auto cin = ifstream("input5.txt", ios::in);

    for (int i = 0; i < RULE_COUNT; i++)
    {
        int a, b;
        cin >> a >> b;
        if (nexts.find(a) == nexts.end())
            nexts[a] = vector<int>();
        
        nexts[a].push_back(b);
    }

    cin.ignore();
    string s;
    getline(cin, s);

    int answer = 0;

    for (int i = 0; i < UPDATE_COUNT; i++)
    {
        getline(cin, s);
        cout << "Update " << i + 1 << ": " << s << endl;

        vector<int> update = parse_update(s);
        
        cout << "Parsed update: ";
        for (int num : update)
            cout << num << " ";
        cout << endl;

        bool valid = check_update_order(update, nexts);
        if (valid == true)
            cout << "Valid" << endl;
        else
        {
            cout << "Invalid" << endl;
            auto fixed_order = fix_update_order(update, nexts);
            cout << "-------------------" << endl;
            answer += fixed_order[update.size() / 2];
        }
    }

    cout << "Answer: " << answer << endl;
}