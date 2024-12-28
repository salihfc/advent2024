#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

#define int long long

using namespace std;

signed main()
{
    auto cin = ifstream("input9.txt", ios::in);
    auto cout = ofstream("output9.txt", ios::out);

    string line;
    cin >> line;
    vector<int> unrolled;
    for (int i = 0; i < line.size(); i++)
    {
        int x = line[i] - '0';
        if (i % 2 == 0) // even
        {
            for (int j = 0; j < x; j++)
                unrolled.push_back(i/2);
        }
        else
        {
            // push -1 x times
            for (int j = 0; j < x; j++)
                unrolled.push_back(-1);
        }
    }
    cout << "Unrolled: " << unrolled.size() << endl;

    int sum = 0;
    int idx = 0;
    while (idx < unrolled.size())
    {
        if (unrolled[idx] == -1)
        {
            // pop from back to put here
            int back = -1;
            while (back == -1)
            {
                back = unrolled.back();
                unrolled.pop_back();
            }
            unrolled[idx] = back;
        }

        cout << idx << " " << unrolled[idx] << endl;
        sum += idx * unrolled[idx];
        idx++;
    }

    cout << "Sum: " << sum << endl;
}   