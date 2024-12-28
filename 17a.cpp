#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <sstream>

#define TRACE(x) cout << #x << " = " << x << endl

using namespace std;

int A, B, C;
vector<int> ops;
int op_pointer = 0;
stringstream output;

enum class OP 
{
    ADV = 0, // A = int(A / (2**(combo operand)))
    BXL, // B = B^(literal operand)
    BST, // B = (combo operand) % 8
    JNZ, // if A != 0, jump to (literal operand)
    BXC, // B = B^C
    OUT, // print (combo operand) % 8
    BDV, // B = int(A / (2**(combo operand)))
    CDV, // C = int(A / (2**(combo operand)))
};

int combo_operand(int operand)
{
    if (0 <= operand && operand <= 3)
        return operand;
    else if (operand == 4)
        return A;
    else if (operand == 5)
        return B;
    else if (operand == 6)
        return C;

    assert(false);
}

int pow2(int n)
{
    return 1 << n;
}

void do_op(int op, int operand)
{
    OP _op = static_cast<OP>(op);
    switch (_op)
    {
    case OP::ADV: {
        operand = combo_operand(operand);
        A = int(A / (pow2(operand)));
        break;
    }
    case OP::BXL: {
        B = B ^ operand;
        break;
    }
    case OP::BST: {
        operand = combo_operand(operand);
        B = operand % 8;
        break;
    }
    case OP::JNZ: {
        if (A != 0)
        {
            op_pointer = operand;
            op_pointer -= 2; // to counteract the increment at the end of the loop
        }
        break;
    }
    case OP::BXC: {
        B = B ^ C;
        break;
    }
    case OP::OUT: {
        operand = combo_operand(operand);
        output << operand % 8 << ",";
        break;
    }
    case OP::BDV: {
        operand = combo_operand(operand);
        B = int(A / (pow2(operand)));
        break;
    }
    case OP::CDV: {
        operand = combo_operand(operand);
        C = int(A / (pow2(operand)));
        break;
    }
    default:
        assert(false);
    }
}

int main()
{
    auto cin = ifstream("input17.txt", ios::in);
    cin >> A >> B >> C;
    // parse line to get list of operations
    int op;
    while (cin >> op)
    {
        ops.push_back(op);
    }

    cout << "A: " << A << " B: " << B << " C: " << C << endl;
    cout << "ops: ";
    for (int i = 0; i < ops.size(); i++)
    {
        cout << ops[i] << " ";
    }
    cout << endl;  

    while (op_pointer < ops.size())
    {
        cout << "OP: " << op_pointer << ": " << ops[op_pointer] << ", " << ops[op_pointer+1] << " | " << A << " " << B << " " << C << endl;
        do_op(ops[op_pointer], ops[op_pointer + 1]);
        op_pointer += 2;
    }

    cout << "---------------------------------" << endl;
    cout << "Output: " << endl;
    cout << output.str() << endl;
    cout << "---------------------------------" << endl;
}