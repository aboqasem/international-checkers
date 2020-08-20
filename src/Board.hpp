#pragma once

#include <iostream>

using namespace std;

class Board {
private:
    char board[10][10] = {
            {' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b'},
            {'b', ' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b', ' '},
            {' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b'},
            {'b', ' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b', ' '},
            {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
            {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' '},
            {' ', 'a', ' ', 'a', ' ', 'a', ' ', 'a', ' ', 'a'},
            {'a', ' ', 'a', ' ', 'a', ' ', 'a', ' ', 'a', ' '},
            {' ', 'a', ' ', 'a', ' ', 'a', ' ', 'a', ' ', 'a'},
            {'a', ' ', 'a', ' ', 'a', ' ', 'a', ' ', 'a', ' '},
    };

public:

    void printBoard();

    char getBoard(const int &x, const int &y);

    void setBoard(const int &x, const int &y, const char &c);
};