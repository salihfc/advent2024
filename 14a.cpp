#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <thread>
#include <sstream>


using namespace std;

auto in = ifstream("input14.txt", ios::in);
auto out = ofstream("output14.txt", ios::out);
// ostream& out = std::cout;
// #define out std::cout

const int N = 500;
const int X = 101;
const int Y = 103;
const int TURNS = 10000;
int PREMOVE = 2200;
int WAIT_MS = 300;

int mp[Y][X];

struct Vector2 
{
    int x, y; 
};

struct Robot {
    Vector2 pos;
    Vector2 vel;

    void move() {
        pos.x += vel.x;
        pos.y += vel.y;

        pos.x = (pos.x + X) % X;
        pos.y = (pos.y + Y) % Y;
    }
};

void clean_map() {
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            mp[i][j] = 0;
        }
    }
}

void print_map() {
    stringstream ss;
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            if (mp[i][j] == 0) {
                ss << " ";
                continue;
            }
            else {
                ss << "#";
            }
            // out << mp[i][j];
        }
        ss << "\n";
    }

    out << ss.str() << endl;
    // std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_MS));
}

int main()
{

    vector<Robot> robots(N);
    for (int i = 0; i < N; i++) {
        in >> robots[i].pos.x >> robots[i].pos.y >> robots[i].vel.x >> robots[i].vel.y;
    }

    for (int i = 0; i < PREMOVE; i++)
        for (auto& robot : robots)
            robot.move();

    for (int i = 0; i < TURNS; i++) {
        for (auto& robot : robots) {
            robot.move();
        }

        clean_map();
        for (auto& robot : robots) {
            mp[robot.pos.y][robot.pos.x]++;
        }

        int first_column_robot_count = 0;
        int last_column_robot_count = 0;
        for (int i = 0; i < Y; i++) {
            first_column_robot_count += mp[i][0];
            last_column_robot_count += mp[i][X - 1];
        }

        if (first_column_robot_count <5 && last_column_robot_count < 5)
        {
            out << "----------------------------------------------------------------"  << endl;
            out << "Turn: " << PREMOVE + i << endl;
            print_map();
            out << "----------------------------------------------------------------"  << endl;
        }
    }

    int topleft_quadrant = 0;
    int topright_quadrant = 0;
    int bottomleft_quadrant = 0;
    int bottomright_quadrant = 0;

    for (int i = 0; i < Y / 2; i++)
        for (int j = 0; j < X / 2; j++)
            topleft_quadrant += mp[i][j];
    
    for (int i = 0; i < Y / 2; i++)
        for (int j = X / 2 + 1; j < X; j++)
            topright_quadrant += mp[i][j];

    for (int i = Y / 2 + 1; i < Y; i++)
        for (int j = 0; j < X / 2; j++)
            bottomleft_quadrant += mp[i][j];

    for (int i = Y / 2 + 1; i < Y; i++)
        for (int j = X / 2 + 1; j < X; j++)
            bottomright_quadrant += mp[i][j];
    
    out << "Top left quadrant: " << topleft_quadrant << endl;
    out << "Top right quadrant: " << topright_quadrant << endl;
    out << "Bottom left quadrant: " << bottomleft_quadrant << endl;
    out << "Bottom right quadrant: " << bottomright_quadrant << endl;
    // answer is multiplication of all quadrants
    int answer = topleft_quadrant * topright_quadrant * bottomleft_quadrant * bottomright_quadrant;
    out << "Answer: " << answer << endl;
}