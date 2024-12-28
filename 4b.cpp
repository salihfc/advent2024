#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <string>

#define TRACE(x) cerr << #x << " = " << x << endl

using namespace std;

const int rows = 140;
const int cols = 140;

struct Vector2 {
    int x;
    int y;
};

const Vector2 top_left = {-1, -1};
const Vector2 top_right = {-1, 1};
const Vector2 bottom_left = {1, -1};
const Vector2 bottom_right = {1, 1};

Vector2 offset(const Vector2 &v, const Vector2 &dir) {
    return {v.x + dir.x, v.y + dir.y};
}

char at_pos(const vector<vector<char>> &matrix, const Vector2 &pos) {
    return matrix[pos.x][pos.y];
}

/*
4 possiblities:
M M   
 A
S S

M S
 A
M S

S S
 A
M M

S M
 A
S M

*/

bool check_xmas(vector<vector<char>> &matrix, int i, int j)
{
    Vector2 pos = {i, j};
    Vector2 top_left_pos = offset(pos, top_left);
    Vector2 top_right_pos = offset(pos, top_right);
    Vector2 bottom_left_pos = offset(pos, bottom_left);
    Vector2 bottom_right_pos = offset(pos, bottom_right);
    // Check bounds
    if (i - 1 < 0 || i + 1 >= rows || j - 1 < 0 || j + 1 >= cols)
        return false;

    /*
        M M   
         A
        S S
    */
    if (
        at_pos(matrix, top_left_pos) == 'M' 
        && at_pos(matrix, top_right_pos) == 'M' 
        && at_pos(matrix, bottom_left_pos) == 'S'
        && at_pos(matrix, bottom_right_pos) == 'S')
        return true;
    
    /*
        M S
         A
        M S
    */
    if (
        at_pos(matrix, top_left_pos) == 'M' 
        && at_pos(matrix, top_right_pos) == 'S' 
        && at_pos(matrix, bottom_left_pos) == 'M'
        && at_pos(matrix, bottom_right_pos) == 'S')
        return true;

    /*
        S S
         A
        M M
    */
    if (
        at_pos(matrix, top_left_pos) == 'S' 
        && at_pos(matrix, top_right_pos) == 'S' 
        && at_pos(matrix, bottom_left_pos) == 'M'
        && at_pos(matrix, bottom_right_pos) == 'M')
        return true;
    
    /*
        S M
         A
        S M
    */

    if (
        at_pos(matrix, top_left_pos) == 'S' 
        && at_pos(matrix, top_right_pos) == 'M' 
        && at_pos(matrix, bottom_left_pos) == 'S'
        && at_pos(matrix, bottom_right_pos) == 'M')
        return true;
    return false;
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
            if (matrix[i][j] == 'A')
            {
                bool found = check_xmas(matrix, i, j);
                total += found;
            }

    TRACE(total);    
}