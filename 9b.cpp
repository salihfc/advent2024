#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

#define TRACE(x) cout << #x << " = " << x << endl
#define TRACE2(x, y) cout << #x << " = " << x << " " << #y << " = " << y << endl

#define int long long

using namespace std;

void print_vector(vector<int> &v, ostream &out)
{
    if (v.size() > 15) return; // too long don't print

    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == -1)
            out << ".";
        else
            out << v[i];
    }
    out << endl;
}

// returns the index of the first empty block with size >= size
int find_empty_block_with_min_size(const vector<int>& v, int end, int size)
{
    int it = 0;
    while(it < end)
    {
        if (v[it] == -1)
        {
            int block_size = 1;
            while(v[it + block_size] == -1)
                block_size++;
            if (block_size >= size)
                return it;
            it += block_size;
        }
        else
            it++;
    }
    return -1; // not found
}

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
    
    cout << "Initial state:" << endl;
    print_vector(unrolled, cout);
    cout << "---" << endl;

    int sum = 0;
    int right_it = unrolled.size() - 1;

    while(right_it > 0)
    {
        // find right_it filled block size
        int right_it_block_id = unrolled[right_it];
        int filled_block_size = 1;
        while(unrolled[right_it - filled_block_size] == right_it_block_id)
            filled_block_size++;

        //
        cout << "Step:" << endl;
        print_vector(unrolled, cout);
        TRACE2(right_it_block_id, filled_block_size);

        
        int empty_block_start = find_empty_block_with_min_size(unrolled, right_it, filled_block_size);
        if (empty_block_start == -1)
        {
            // cannot move block
            // move it to the left
            // skip '-1' and 'right_it_block_id' blocks
            while(right_it > 0 && unrolled[right_it] == -1 || unrolled[right_it] == right_it_block_id)
                right_it--;
            continue;
        }

        // fill the empty block by filled block size
        for (int i = 0; i < filled_block_size; i++)
        {
            unrolled[empty_block_start++] = right_it_block_id;
            unrolled[right_it--] = -1;
        }

        print_vector(unrolled, cout);
        cout << "---" << endl;
    }

    // Calc sum
    print_vector(unrolled, cout);
    for (int i = 0; i < unrolled.size(); i++)
    {
        if (unrolled[i] != -1)
            sum += unrolled[i] * i;
    }

    cout << "Sum: " << sum << endl;
    std::cout << ">>Sum: " << sum << std::endl;
}   