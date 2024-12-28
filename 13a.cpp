#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
using namespace std;

#define TRACE(x) cout << #x << " = " << x << endl

const int N = 320;
const int MAX_TOKEN = 100;

struct Game {
    int adx, ady;
    int bdx, bdy;
    int tx, ty;
};

int cost(Game game)
{
    int min_cost = 1e9;

    for (int i = 0; i <= MAX_TOKEN; i++)
    {
        for (int j = 0; j <= MAX_TOKEN; j++) 
        {
            int cost = i*3 + j;
            if (cost >= min_cost)
                continue;
            int x = game.adx * i + game.bdx * j;
            int y = game.ady * i + game.bdy * j;
            if (x == game.tx && y == game.ty) 
            {
                min_cost = min(min_cost, i*3 + j);
            }
        }
    }


    if (min_cost != 1e9)
        return min_cost;
    return -1;
}

int main()
{
    auto cin = ifstream("input13.txt", ios::in);
    int total_cost = 0;

    for (int i = 0; i < N; i++) 
    {
        Game game;
        cin >> game.adx >> game.ady;
        cin >> game.bdx >> game.bdy;
        cin >> game.tx >> game.ty;

        int c = cost(game);
        if (c != -1)
            total_cost += c;
    }

    TRACE(total_cost);
}