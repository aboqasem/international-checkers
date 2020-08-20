#pragma once
#include <iostream>
#include <fstream>
#include "UserInterface.hpp"
using namespace std;

class File
{
public:
    static void write(Board &BOARD, const char &PLAYER);
    static void read(Board &BOARD, char &PLAYER);
    static void validName(string &name);
};
