#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <string>

#define TRACE(x) cerr << #x << " = " << x << endl

using namespace std;

const string word = "XMAS";
const int rows = 140;
const int cols = 140;

struct Vector2
{
    int x;
    int y;

    bool operator==(const Vector2 &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator<(const Vector2 &other) const
    {
        return x < other.x || (x == other.x && y < other.y);
    }
};

const vector<Vector2> DIRS = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

void search_word(vector<vector<char>> &matrix, int i, int j, int index, Vector2 dir, int &total, vector<Vector2> path)
{
    if (matrix[i][j] != word[index])
        return;

    if (index == (word.size() - 1))
    {
        total++;
        return;
    }

    int new_i = i + dir.x;
    int new_j = j + dir.y;
    if (new_i >= 0 && new_i < rows && new_j >= 0 && new_j < cols)
    {
        vector<Vector2> new_path = path;
        new_path.push_back({new_i, new_j});
        search_word(matrix, new_i, new_j, index + 1, dir, total, new_path);
    }
}

int main()
{
    auto cin = ifstream("input4.txt", ios::in);
    vector<vector<char>> matrix(rows, vector<char>(cols));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            cin >> matrix[i][j];


    int total = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (matrix[i][j] == 'X')
            {
                for (auto dir : DIRS)
                    search_word(matrix, i, j, 0, dir, total, {{i, j}});
            }
    
    cout << "Total: " << total << endl;
}