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

int main()
{
    auto cin = ifstream("input2.txt", ios::in);
    int safe_count = 0;
    int total_count = 0;

    string line;
    while (getline(cin, line))
    {
        total_count++;
        cout << line << endl;
        stringstream ss(line);
        int x, y;
        ss >> x >> y;
        int diff = x-y;
        int move = sign(diff);
        bool safe = true;

        do
        {
            diff = x-y;
            if (diff == 0 || sign(diff) != move)
            {
                safe = false;
                break;
            }

            if (abs(diff) < MIN_CHANGE || MAX_CHANGE < abs(diff))
            {
                safe = false;
                break;
            }

            x = y;
        } while (ss >> y); 

        if (safe)
            safe_count++;
    }

    
    cout << "Total count: " << total_count << endl;
    cout << "Safe count: " << safe_count << endl;
}