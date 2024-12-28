#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <cassert>

using namespace std;

const int N = 90;
map<string, bool> wires;

struct Gate
{
    string op;
    string in1, in2;
    string out;

    bool execute()
    {
        if (op == "AND")
            return wires[in1] & wires[in2];
        else if (op == "OR")
            return wires[in1] | wires[in2];
        else if (op == "XOR")
            return wires[in1] ^ wires[in2];
        
        assert(false);
        return false;
    }
};

vector<Gate> gates;

int main()
{
    auto cin = ifstream("input24.txt", ios::in);
    // Read initial state of wires
    string w;
    bool b;

    int n = N;
    while (n--)
    {
        cin >> w >> b;
        wires[w] = b;
    }

    // getline(cin, w); // Read the newline

    Gate gate;
    while (cin >> gate.in1 >> gate.op >> gate.in2 >> gate.out)
        gates.push_back(gate);


    // Output initial state of wires
    for (auto &w : wires)
        cout << w.first << " " << w.second << endl;

    // Output the gates
    for (auto &g : gates)
        cout << g.in1 << " " << g.op << " " << g.in2 << " " << g.out << endl;
    

    while (gates.size())
    {
        vector<Gate> new_gates;
        for (auto& gate : gates)
        {
            // If both inputs are in 'wires' 
            // calculate the output, remove the gate and update the wires
            if (wires.find(gate.in1) != wires.end() && wires.find(gate.in2) != wires.end())
                wires[gate.out] = gate.execute();
            else
                new_gates.push_back(gate);
        }
        gates = new_gates;
    }

    // Output final state of wires
    for (auto &w : wires)
        cout << w.first << " " << w.second << endl;

    long long int t = 0;
    long long int f = 1;
    for (auto &w : wires)
    {
        if (w.first[0] == 'z')
        {
            t += w.second * f;
            f *= 2;
        }
    }

    cout << "Output: " << t << endl;
}