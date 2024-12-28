#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <sstream>
#include <set>

#define int long long
#define TRACE(x) cout << #x << " = " << x << endl

using namespace std;

vector<int> ops;

set<int> first_24_bits;

bool run_program(int ra)
{
    int A = ra;
    int B = 0;
    int C = 0;
    int it = 0;

    while (A > 0)
    {
        B = (A&0b111); // B = A % 8
        B = B^2;   // B = B xor 2
        C = (A >> B) & 0b111; // C = (A >> B) % 8
        B = B^7;
        B = B^C;
        A = A >> 3;
        if (B != ops[it])
            return false;
        
        if (it == 6)
        {
            first_24_bits.insert(A);
            return false;
        }
        it++;
    }
    return true;
}

signed main()
{
    auto cin = ifstream("input17.txt", ios::in);
    int A, startB, startC;
    cin >> A >> startB >> startC;
    // parse line to get list of operations
    int op;
    while (cin >> op)
    {
        ops.push_back(op);
    }
    /*
    2993
    3057
    3087
    4081
    */

    int possible_12_bits[4] = {2993, 3057, 3087, 4081}; 
    int left_start = (1LL<<33); // 48-47-46 triple must be at least 1 
    while(left_start < (1LL<<37))
    {
        if (left_start % 10000000 == 0)
            cout << left_start << endl;

        for (int i = 0; i < 4; i++)
        {
            int right_start = possible_12_bits[i];
            int a = (left_start << 12) + right_start;
            if (run_program(a))
            {
                cout << "A: " << a << endl;
                return 0;
            }
        }

        left_start++;
    }
}