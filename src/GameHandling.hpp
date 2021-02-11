#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "Rules.hpp"
using namespace std;

class Game
{
private:
    static map<char, int> Y;
    static map<char, int> X;

public:
    static void setCoordinates(const string &y1x1, const string &y2x2, int &x1, int &y1, int &x2, int &y2);
    static void start(char &PLAYER, Board &BOARD);
};
