#pragma once
#include "Board.hpp"
#include "GameHandling.hpp"
#include "FileManagement.hpp"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;

class UserInterface
{
public:
    static void validInput(int &input, const int &minrange, const int &maxrange, const string &error="Inavlid input, re-enter ->");
    static void clearScreen();
    static void delayScreen(const double &Seconds=1);
    static void start(char &player, Board &board);
};
