#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const int MIN_CHANGE = 1;
const int MAX_CHANGE = 3;

int sign(int x)
{
    if (x == 0)
        return 0;
    return x/abs(x);
}

bool violates_rules(int current_diff, int move_dir)
{
    if (sign(current_diff) != sign(move_dir))
        return true;
    if (abs(current_diff) < MIN_CHANGE || MAX_CHANGE < abs(current_diff))
        return true;
    return false;
}

// bool check(vector<int>& v, int idx, int last_idx, bool removal_used)
// {
//     bool result = false;

//     if (last_idx == 0)
//         result |= check(v, idx+1, idx, false);
    
//     return result;
// }

bool check_linear(vector<int> v, int skip_idx)
{
    if (skip_idx > -1)
        v.erase(v.begin() + skip_idx);

    int move_dir = sign(v[0] - v[1]);
    if (move_dir == 0)
        return false;

    if (violates_rules(v[0] - v[1], move_dir))
        return false;

    for (size_t i = 1; i+1 < v.size(); i++)
    {
        int cur_diff = v[i] - v[i+1];
        if (violates_rules(cur_diff, move_dir))
            return false;
    }
    return true;
}

bool is_safe(vector<int> v)
{
    if (check_linear(v, -1))
        return true;

    for (int i = 0; i < v.size(); i++)
        if (check_linear(v, i))
            return true;
    return false;
}

int main()
{
    auto cin = ifstream("input2.txt", ios::in);
    int safe_count = 0;
    int total_count = 0;

    string line;
    while (getline(cin, line))
    {
        total_count++;
        stringstream ss(line);
        vector<int> v;

        int x;
        while (ss >> x)
            v.push_back(x);
        
        safe_count += is_safe(v);
    }

    cout << "Total count: " << total_count << endl;
    cout << "Safe count: " << safe_count << endl;
}