#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <sstream>
#include <set>
using namespace std;

#define cout fout
#define int long long
#define TRACE(x) cout << #x << " = " << x << endl

auto fout = ofstream("output17.txt", ios::out);


vector<int> ops;

set<int> first_24_bits;

bool run_program(int ra)
{
    if (ra % 100000000 == 0)
        cout << "A: " << ra << endl;
    
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
            first_24_bits.insert(ra & 0xFFFFFF);
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

    // exit(0);
    int a = (1LL << 46);
    int maxa = a + (1LL << (24+8));
    // int a = (1LL << 48);
    // int a = 0;
    while(run_program(a) == false && a < maxa)
    {
        a++;
    }

    assert(a == maxa);
    // cout << "Final A: " << a << endl;

    cout << "Part 1: " << first_24_bits.size() << endl;
    for (auto x : first_24_bits)
        cout << x << endl;
}