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
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == -1)
            out << ".";
        else
            out << v[i];
    }
    out << endl;
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
    print_vector(unrolled, cout);

    int sum = 0;
    int left_it = 0;
    int right_it = unrolled.size() - 1;
    int empty_block_size = 0;

    while(left_it < right_it)
    {
        TRACE2(left_it, right_it);
        print_vector(unrolled, cout);
        if (empty_block_size == 0)
        {
            // find the next -1 for left_it
            while(unrolled[left_it] != -1)
                left_it++;
            // find empty block size
            while(unrolled[left_it + empty_block_size] == -1)
                empty_block_size++;
        }

        TRACE(empty_block_size);

        // find right_it filled block size
        int right_it_block_id = unrolled[right_it];
        int filled_block_size = 1;

        if (right_it <= left_it)
            break;

        while (true)
        {
            while(unrolled[right_it - filled_block_size] == right_it_block_id)
                filled_block_size++;
            
            TRACE2(right_it_block_id, filled_block_size);

            if (filled_block_size <= empty_block_size)
                break;
            else
            {
                right_it -= filled_block_size;
                filled_block_size = 1;
                // skip -1
                while(unrolled[right_it] == -1)
                    right_it--;
                
                right_it_block_id = unrolled[right_it];
            }
        }

        // fill the empty block by filled block size
        for (int i = 0; i < filled_block_size; i++)
        {
            unrolled[left_it++] = right_it_block_id;
            unrolled[right_it--] = -1;
            empty_block_size--;
        }
        // left_it += filled_block_size;
        // right_it -= filled_block_size;
        // empty_block_size -= filled_block_size;
        // exit(0);
    }

    // Calc sum
    print_vector(unrolled, cout);
    for (int i = 0; i < unrolled.size(); i++)
    {
        if (unrolled[i] != -1)
            sum += unrolled[i] * i;
    }

    cout << "Sum: " << sum << endl;
}   