#pragma once
#include <iostream>
#include <vector>
#include "UserInterface.hpp"
using namespace std;
/*---------------------------------------------------------------------------------------------------------*/
class Rules
{
private:
    static vector<pair<int, int>> coordinatestocheck;
    static bool inBoardCoordinates(const int &x1, const int &y1, const int &x2, const int &y2, string &error);
    static bool validSquare(const int &x1, const int &y1, const int &x2, const int &y2, Board &BOARD, string &error);
    static bool fromUnoccupiedSquare(const int &x1, const int &y1, Board BOARD, string &error);
    static bool validPiece(const int &x1, const int &y1, char PLAYER, Board &BOARD, string &error);
    static bool toUnoccupiedSquare(const int &x2, const int &y2, Board BOARD, string &error);

public:
    virtual bool legalMove(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER, Board &BOARD, string &error, const int &onemove, const int &currentx, const int &currenty) = 0;
    virtual bool upRightCapture(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER, Board &BOARD) = 0;
    virtual bool upLeftCapture(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER, Board &BOARD) = 0;
    virtual bool downRightCapture(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER, Board &BOARD) = 0;
    virtual bool downLeftCapture(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER, Board &BOARD) = 0;
    virtual bool captureAvailable(const int &x1, const int &y1, const int &x2, const int &y2, char OTHERPLAYER, Board &BOARD, string &error, const string &previousdirection, const int &checkeverydirection = 0) = 0;
    static bool basicRules(const int &x1, const int &y1, const int &x2, const int &y2, char PLAYER, Board &BOARD, string &error);
    static bool becomeCrown(const int &y2, const char &PLAYER);
    static bool endgame(Board &BOARD);
};
/*---------------------------------------------------------------------------------------------------------*/
class OrdinaryRules : public Rules
{
public:
    bool moveAvailable(const int &x, const int &y, Board &BOARD);
    bool legalMove(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER, Board &BOARD, string &error, const int &onemove, const int &currentx, const int &currenty) override;
    bool upRightCapture(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER, Board &BOARD) override;
    bool upLeftCapture(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER, Board &BOARD) override;
    bool downRightCapture(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER, Board &BOARD) override;
    bool downLeftCapture(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER, Board &BOARD) override;
    bool captureAvailable(const int &x1, const int &y1, const int &x2, const int &y2, char OTHERPLAYER, Board &BOARD, string &error, const string &previousdirection, const int &checkeverydirection = 0) override;
};
/*---------------------------------------------------------------------------------------------------------*/
class CrownRules : public Rules
{
private:
    vector<pair<int, int>> cooordinatesallowed;
    int xnow, ynow;
    bool upRightDirection(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER, Board &BOARD);
    bool upLeftDirection(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER, Board &BOARD);
    bool downRightDirection(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER, Board &BOARD);
    bool downLeftDirection(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER, Board &BOARD);

public:
    bool legalMove(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER, Board &BOARD, string &error, const int &onemove, const int &currentx, const int &currenty) override;
    bool upRightCapture(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER, Board &BOARD) override;
    bool upLeftCapture(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER, Board &BOARD) override;
    bool downRightCapture(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER, Board &BOARD) override;
    bool downLeftCapture(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER, Board &BOARD) override;
    bool captureAvailable(const int &x1, const int &y1, const int &x2, const int &y2, char OTHERPLAYER, Board &BOARD, string &error, const string &previousdirection, const int &checkeverydirection = 0) override;
};
/*---------------------------------------------------------------------------------------------------------*/
