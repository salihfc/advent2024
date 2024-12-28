#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

// #define TRACE(x) cout << #x << " = " << x << endl;
#define TRACE(x) ;

using namespace std;

enum class ParseState {
    PREFIX,
    FIRST_NUM,
    SECOND_NUM,
};

bool is_digit(char c)
{
    return '0' <= c && c <= '9';
}

int parse_int(string& str)
{
    int num = 0;

    for (auto c : str)
    {
        if (!is_digit(c))
            return -1;

        num = num * 10 + (c - '0');
    }

    return num;
}

bool match(string expr, string sub, int index)
{
    if (index + sub.size() > expr.size())
        return false;

    for (int i = 0; i < sub.size(); i++)
        if (expr[index + i] != sub[i])
            return false;
    return true;
}

int main()
{
    auto cout = ofstream("output3.txt", ios::out);
    auto cin = ifstream("input3.txt", ios::in);
    string expr;
    char c;
    while(cin.get(c))
        expr += c;
    TRACE(expr.size());
    const string do_expr = "do()";
    const string dont_expr = "don't()";
    const string prefix = "mul(";
    const char separator = ',';
    const char suffix = ')';
    int sum = 0;
    int n = expr.size();
    int index = 0;

    auto state = ParseState::PREFIX;
    int first_num = 0;
    bool active = true;

    TRACE(expr);
    TRACE(n);
    // getc(stdin);

    while (index < n)
    {
        // TRACE(index);        
        switch (state)
        {
            case ParseState::PREFIX:
            {
                int cur = index;
                while(cur < n)
                {
                    // TRACE(cur);
                    int it = 0;
                    while (it < prefix.size() && (cur + it) < n && prefix[it] == expr[cur + it]) it++;
                    if (it == prefix.size())
                    {
                        // Found prefix change state
                        state = ParseState::FIRST_NUM;
                        index = cur + it;

                        cout << "Found prefix at " << cur << endl;
                        break;
                    }
                    // no match
                    // search for do() or don't()
                    if (match(expr, do_expr, cur))
                    {
                        cout << "Found do() at " << cur << endl;
                        active = true;
                        cur += do_expr.size();
                    }
                    else if (match(expr, dont_expr, cur))
                    {
                        cout << "Found don't() at " << cur << endl;
                        active = false;
                        cur += dont_expr.size();
                    }
                    else
                    {
                        // move cur by it 
                        cur = cur + it + (it == 0);
                    }
                }

                if (cur == n)
                    index = n;
                break;
            }

            case ParseState::FIRST_NUM:
            {
                // Parse until separator
                string num_str;
                int cur = index;
                int it = 0;
                while (cur + it < n && expr[cur + it] != separator && is_digit(expr[cur + it]))
                {
                    num_str += expr[cur + it];
                    it++;
                }

                if (cur+it == n || expr[cur+it] != separator)
                {
                    // No separator found
                    state = ParseState::PREFIX;

                    // search for do() or don't()
                    if (match(expr, do_expr, cur))
                    {
                        active = true;
                        cur += do_expr.size();
                    }
                    else if (match(expr, dont_expr, cur))
                    {
                        active = false;
                        cur += dont_expr.size();
                    }
                    else
                        cur += it;

                    index = cur;
                    break;
                }

                int num = parse_int(num_str);
                if (num == -1)
                {
                    // search for do() or don't()
                    if (match(expr, do_expr, cur))
                    {
                        active = true;
                        cur += do_expr.size();
                    }
                    else if (match(expr, dont_expr, cur))
                    {
                        active = false;
                        cur += dont_expr.size();
                    }
                    else
                        cur += it;
                    // move index, reset to prefix state
                    state = ParseState::PREFIX;
                    index = cur;
                    break;
                }

                // first num found and parsed parse second
                state = ParseState::SECOND_NUM;
                index = cur+num_str.size()+1;
                first_num = num;
                cout << "Found first num = " << num << " | new_index: " << index << " [] " 
                    << expr[index-1] << expr[index] << expr[index+1] << endl;
                break;
            }

            case ParseState::SECOND_NUM:
            {
                // Parse until suffix
                string num_str;
                int cur = index;
                int it = 0;
                while (cur + it < n && expr[cur + it] != suffix && is_digit(expr[cur + it]))
                {
                    num_str += expr[cur + it];
                    it++;
                }

                if (cur + it == n || expr[cur + it] != suffix)
                {
                    // search for do() or don't()
                    if (match(expr, do_expr, cur))
                    {
                        active = true;
                        cur += do_expr.size();
                    }
                    else if (match(expr, dont_expr, cur))
                    {
                        active = false;
                        cur += dont_expr.size();
                    }
                    else
                        cur += it;

                    // No suffix found
                    state = ParseState::PREFIX;
                    index = cur;
                    break;
                }

                int num = parse_int(num_str);
                if (num == -1)
                {
                    // search for do() or don't()
                    if (match(expr, do_expr, cur))
                    {
                        active = true;
                        cur += do_expr.size();
                    }
                    else if (match(expr, dont_expr, cur))
                    {
                        active = false;
                        cur += dont_expr.size();
                    }
                    else
                        cur += it;
                    // move index, reset to prefix state
                    state = ParseState::PREFIX;
                    index = cur;
                    break;
                }

                // second num found and parsed
                cout << "Found second num = " << num << endl;
                // move to prefix state
                state = ParseState::PREFIX;
                index = cur+1;

                // add to sum;
                int mul = first_num * num;
                sum += mul * active;
                cout << "Found mul(" << first_num << ", " << num << ") = " << mul << endl;
            }

            default:
                break;
        }
    }

    TRACE(sum);
    cout << "Sum = " << sum << endl;
}