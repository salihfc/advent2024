#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <cassert>

using namespace std;
const int RULE_COUNT = 1176;
const int UPDATE_COUNT = 185;

struct Node {
    int value;
    Node(int value) : value(value) {}
    vector<Node*> next;
};

int parent[100000];
int subtree_size[100000];

// Need dsu to keep track of graph clusters
void make_set(int v) {
    parent[v] = v;
    subtree_size[v] = 1;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (subtree_size[a] < subtree_size[b])
            swap(a, b);
        parent[b] = a;
        subtree_size[a] += subtree_size[b];
    }
}

struct Dag {
    map<int, Node*> nodes;

    void add_edge(int a, int b)
    {
        union_sets(a, b);
        if (nodes.find(a) == nodes.end())
            nodes[a] = new Node{a};
        if (nodes.find(b) == nodes.end())
            nodes[b] = new Node{b};

        Node* node_a = nodes[a];
        Node* node_b = nodes[b];

        node_a->next.push_back(node_b);
    }

    bool in_same_cluster(int a, int b)
    {
        assert(nodes.find(a) != nodes.end());
        assert(nodes.find(b) != nodes.end());
        return find_set(a) == find_set(b);
    }

    bool search(Node* cur, Node* target)
    {
        if (cur == target)
            return true;
        for (Node* next : cur->next)
            if (search(next, target))
                return true;
        return false;
    }

    bool can_reach(int a, int b)
    {
        assert(nodes.find(a) != nodes.end());
        assert(nodes.find(b) != nodes.end());
        assert(in_same_cluster(a, b));
        return search(nodes[a], nodes[b]);
    }

    bool valid_order(int a, int b)
    {
        if (!in_same_cluster(a, b))
            return true;
        return can_reach(a, b);
    }
};

vector<int> parse_update(string update_line)
{
    vector<int> result;
    int i = 0;
    while (i < update_line.size())
    {
        int num = 0;
        while (i < update_line.size() && isdigit(update_line[i]))
        {
            num = num * 10 + (update_line[i] - '0');
            i++;
        }
        result.push_back(num);
        i++;
    }
    return result;
}

bool check_update_order(vector<int> update, Dag& dag)
{
    for (int i = 0; i < update.size(); i++)
        for (int j = i + 1; j < update.size(); j++)
            if (!dag.valid_order(update[i], update[j]))
                return false;
    return true;
}

int main()
{
    auto cin = ifstream("input5.txt", ios::in);

    for (int i = 0; i < 100000; i++)
        make_set(i);
    

    Dag dag;
    for (int i = 0; i < RULE_COUNT; i++)
    {
        int a, b;
        cin >> a >> b;
        dag.add_edge(a, b);

        cout << "Rule " << i + 1 << ": " << a << " " << b << endl;
    }

    cin.ignore();
    string s;
    getline(cin, s);

    int answer = 0;

    for (int i = 0; i < UPDATE_COUNT; i++)
    {
        getline(cin, s);
        cout << "Update " << i + 1 << ": " << s << endl;

        vector<int> update = parse_update(s);
        
        cout << "Parsed update: ";
        for (int num : update)
            cout << num << " ";
        cout << endl;

        bool valid = check_update_order(update, dag);
        if (valid == true)
            cout << "Valid" << endl;
        else
            cout << "Invalid" << endl;
        
        cout << "-------------------" << endl;
        answer += valid * update[update.size() / 2];
    }

    cout << "Answer: " << answer << endl;
}