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
    if (sign(current_diff) != move_dir)
        return false;
    if (abs(current_diff) < MIN_CHANGE || MAX_CHANGE < abs(current_diff))
        return false;
    return true;
}

bool check(vector<int>& v, int idx, int last_idx, bool removal_used)
{
    bool result = false;

    if (last_idx == 0)
        result |= check(v, idx+1, idx, false);
    
    return result;
}


bool is_safe(vector<int>& v)
{
    // return check(v);
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

        int x = 0;
        while (ss >> x)
            v.push_back(x);
        
        safe_count += is_safe(v);
    }

    cout << "Total count: " << total_count << endl;
    cout << "Safe count: " << safe_count << endl;
}