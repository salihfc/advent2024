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

// set<int> first_24_bits;

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
        
        // if (it == 6)
        // {
        //     first_24_bits.insert(A);
        //     return false;
        // }
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
    const int COUNT = 49; 
    int possible_24_bits[COUNT] = {
        1063951,
        1129487,
        1391631,
        3161103,
        3226639,
        3357711,
        3488783,
        3619855,
        4209679,
        4275215,
        4361137,
        5258255,
        5323791,
        5585935,
        7355407,
        7420943,
        7552015,
        7683087,
        7814159,
        9452559,
        9518095,
        9583631,
        9780239,
        9845775,
        10042383,
        10107919,
        10111921,
        10304527,
        10370063,
        10828815,
        11549711,
        11615247,
        11746319,
        11877391,
        12008463,
        12139535,
        12401679,
        12598287,
        12663823,
        13646863,
        13712399,
        13974543,
        14498831,
        15744015,
        15809551,
        15940623,
        16071695,
        16202767,
        16595983
    };

    int left_start = (1LL<<(21)); // 48-47-46 triple must be at least 1 
    while(left_start < (1LL<<(21+3)))
    {
        if (left_start % 10000000 == 0)
            cout << left_start << endl;

        for (int i = 0; i < COUNT; i++)
        {
            int right_start = possible_24_bits[i];
            int a = (left_start << 24) + right_start;
            if (run_program(a))
            {
                cout << "A: " << a << endl;
                return 0;
            }
        }

        left_start++;
    }
}