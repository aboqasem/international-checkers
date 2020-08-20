#include "Rules.hpp"

/*---------------------------------------------------------------------------------------------------------*/
bool Rules::inBoardCoordinates(const int &x1, const int &y1, const int &x2, const int &y2, string &error) {
    if (y1 == -1 || y2 == -1 || x1 == -1 || x2 == -1) {
        error = "Case: Out of range coordinates.";
        return false;
    }
    return true;
}

bool Rules::validSquare(const int &x1, const int &y1, const int &x2, const int &y2, Board &BOARD, string &error) //
{
    if (BOARD.getBoard(x1, y1) == ' ' || BOARD.getBoard(x2, y2) == ' ') {
        error = "Case: Not allowed to move from or to light squares.";
        return false;
    }
    return true;
}

bool Rules::fromUnoccupiedSquare(const int &x1, const int &y1, Board BOARD, string &error) {
    if (BOARD.getBoard(x1, y1) == '#') {
        error = "Case: This square does not contain a piece of yours.";
        return true;
    }
    return false;
}

bool Rules::validPiece(const int &x1, const int &y1, char PLAYER, Board &BOARD, string &error) {
    if (tolower(BOARD.getBoard(x1, y1)) != PLAYER) {
        error = "Case: This piece belongs to the opposite player.";
        return false;
    }
    return true;
}

bool Rules::toUnoccupiedSquare(const int &x2, const int &y2, Board BOARD, string &error) {
    if (BOARD.getBoard(x2, y2) != '#') {
        error = "Case: Not allowed to move to an occupied square.";
        return false;
    }
    return true;
}

bool Rules::becomeCrown(const int &y2, const char &PLAYER) {
    switch (PLAYER) {
        case 'a':
            return y2 == 0 ? true : false;
            break;
        case 'b':
            return y2 == 9 ? true : false;
            break;
        default:
            return false;
    }
}

bool Rules::basicRules(const int &x1, const int &y1, const int &x2, const int &y2, char PLAYER, Board &BOARD,
                       string &error) {
    if (!inBoardCoordinates(x1, y1, x2, y2, error) ||
        !validSquare(x1, y1, x2, y2, BOARD, error) ||
        fromUnoccupiedSquare(x1, y1, BOARD, error) ||
        !validPiece(x1, y1, PLAYER, BOARD, error) ||
        !toUnoccupiedSquare(x2, y2, BOARD, error)) { return false; }
    return true;
}

/*---------------------------------------------------------------------------------------------------------*/
bool OrdinaryRules::legalMove(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER,
                              Board &BOARD, string &error, const int &onemove, const int &currentx,
                              const int &currenty) {
    if (onemove == 0 && currentx != x1 && currenty != y1) {
        error = "Case: Not an allowed move for an ordinary piece.";
        return false;
    }
    if (((x1 == x2) || (y1 == y2)) ||
        ((x1 > x2 && y1 < y2) && (x2 < x1 - 2 || y2 > y1 + 2)) ||
        ((x1 > x2 && y1 > y2) && (x2 < x1 - 2 || y2 < y1 - 2)) ||
        ((x1 < x2 && y1 < y2) && (x2 > x1 + 2 || y2 > y1 + 2)) ||
        ((x1 < x2 && y1 > y2) && (x2 > x1 + 2 || y2 < y1 - 2)) ||
        (((x1 > x2 && y1 < y2) && (x2 < x1 - 1 && y2 > y1 + 1)) &&
         (tolower(BOARD.getBoard(x2 + 1, y2 - 1)) != OTHERPLAYER)) ||
        (((x1 > x2 && y1 > y2) && (x2 < x1 - 1 && y2 < y1 - 1)) &&
         (tolower(BOARD.getBoard(x2 + 1, y2 + 1)) != OTHERPLAYER)) ||
        (((x1 < x2 && y1 < y2) && (x2 > x1 + 1 && y2 > y1 + 1)) &&
         (tolower(BOARD.getBoard(x2 - 1, y2 - 1)) != OTHERPLAYER)) ||
        (((x1 < x2 && y1 > y2) && (x2 > x1 + 1 && y2 < y1 - 1)) &&
         (tolower(BOARD.getBoard(x2 - 1, y2 + 1)) != OTHERPLAYER)) ||
        (onemove == 0 && (y2 == y1 - 1 || y2 == y1 + 1))) {
        error = "Case: Not an allowed move for an ordinary piece.";
        return false;
    }
    return true;
}

bool OrdinaryRules::upRightCapture(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER,
                                   Board &BOARD) {
    if ((x2 > x1 && y2 < y1) && (x2 == x1 + 2 && y2 == y1 - 2) && BOARD.getBoard(x2, y2) == '#' &&
        tolower(BOARD.getBoard(x1 + 1, y1 - 1)) == OTHERPLAYER) {
        return true;
    }
    return false;
}

bool OrdinaryRules::upLeftCapture(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER,
                                  Board &BOARD) {
    if ((x2 < x1 && y2 < y1) && (x2 == x1 - 2 && y2 == y1 - 2) && BOARD.getBoard(x2, y2) == '#' &&
        tolower(BOARD.getBoard(x1 - 1, y1 - 1)) == OTHERPLAYER) {
        return true;
    }
    return false;
}

bool
OrdinaryRules::downRightCapture(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER,
                                Board &BOARD) {
    if ((x2 > x1 && y2 > y1) && (x2 == x1 + 2 && y2 == y1 + 2) && BOARD.getBoard(x2, y2) == '#' &&
        tolower(BOARD.getBoard(x1 + 1, y1 + 1)) == OTHERPLAYER) {
        return true;
    }
    return false;
}

bool OrdinaryRules::downLeftCapture(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER,
                                    Board &BOARD) {
    if ((x2 < x1 && y2 > y1) && (x2 == x1 - 2 && y2 == y1 + 2) && BOARD.getBoard(x2, y2) == '#' &&
        tolower(BOARD.getBoard(x1 - 1, y1 + 1)) == OTHERPLAYER) {
        return true;
    }
    return false;
}

bool OrdinaryRules::captureAvailable(const int &x1, const int &y1, const int &x2, const int &y2, char OTHERPLAYER,
                                     Board &BOARD, string &error, const string &previousdirection,
                                     const int &checkeverydirection) {
    if (checkeverydirection == 0) {
        if (upRightCapture(x1, y1, x2, y2, OTHERPLAYER, BOARD) ||
            upLeftCapture(x1, y1, x2, y2, OTHERPLAYER, BOARD) ||
            downRightCapture(x1, y1, x2, y2, OTHERPLAYER, BOARD) ||
            downLeftCapture(x1, y1, x2, y2, OTHERPLAYER, BOARD)) {
            return true;
        }
    } else if (checkeverydirection == 1) {
        if (previousdirection == "ur") {
            if (upRightCapture(x2, y2, x2 + 2, y2 - 2, OTHERPLAYER, BOARD) ||
                upLeftCapture(x2, y2, x2 - 2, y2 - 2, OTHERPLAYER, BOARD) ||
                downRightCapture(x2, y2, x2 + 2, y2 + 2, OTHERPLAYER, BOARD)) {
                error = "Case: There is at least one more compulsory capture.";
                return true;
            }
        } else if (previousdirection == "ul") {
            if (upRightCapture(x2, y2, x2 + 2, y2 - 2, OTHERPLAYER, BOARD) ||
                upLeftCapture(x2, y2, x2 - 2, y2 - 2, OTHERPLAYER, BOARD) ||
                downLeftCapture(x2, y2, x2 - 2, y2 + 2, OTHERPLAYER, BOARD)) {
                error = "Case: There is at least one more compulsory capture.";
                return true;
            }
        } else if (previousdirection == "dr") {
            if (upRightCapture(x2, y2, x2 + 2, y2 - 2, OTHERPLAYER, BOARD) ||
                downRightCapture(x2, y2, x2 + 2, y2 + 2, OTHERPLAYER, BOARD) ||
                downLeftCapture(x2, y2, x2 - 2, y2 + 2, OTHERPLAYER, BOARD)) {
                error = "Case: There is at least one more compulsory capture.";
                return true;
            }
        } else if (previousdirection == "dl") {
            if (upLeftCapture(x2, y2, x2 - 2, y2 - 2, OTHERPLAYER, BOARD) ||
                downRightCapture(x2, y2, x2 + 2, y2 + 2, OTHERPLAYER, BOARD) ||
                downLeftCapture(x2, y2, x2 - 2, y2 + 2, OTHERPLAYER, BOARD)) {
                error = "Case: There is at least one more compulsory capture.";
                return true;
            }
        }
    }
    return false;
}

bool OrdinaryRules::moveAvailable(const int &x, const int &y, Board &BOARD) {
    if (BOARD.getBoard(x + 1, y - 1) == '#' ||
        BOARD.getBoard(x + 1, y + 1) == '#' ||
        BOARD.getBoard(x - 1, y - 1) == '#' ||
        BOARD.getBoard(x - 1, y + 1) == '#') {
        return true;
    }
    return false;
}

/*---------------------------------------------------------------------------------------------------------*/
bool CrownRules::upRightDirection(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER,
                                  Board &BOARD) {
    xnow = x1;
    ynow = y1;
    if (x2 > x1 && y2 < y1) {
        while (xnow < x2 && ynow > y2) {
            ++xnow;
            --ynow;
            cooordinatesallowed.push_back({xnow, ynow});
        }
        for (int i = 0; i < cooordinatesallowed.size(); ++i) {
            if (tolower(BOARD.getBoard(cooordinatesallowed[i].first, cooordinatesallowed[i].second)) == OTHERPLAYER) {
                if (BOARD.getBoard(cooordinatesallowed[i].first + 1, cooordinatesallowed[i].second - 1) == '#') {
                    cooordinatesallowed.clear();
                    return true;
                }
            }
        }
        cooordinatesallowed.clear();
    }
    return false;
}

bool CrownRules::upLeftDirection(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER,
                                 Board &BOARD) {
    xnow = x1;
    ynow = y1;
    if (x2 < x1 && y2 < y1) {
        while (xnow > x2 && ynow > y2) {
            --xnow;
            --ynow;
            cooordinatesallowed.push_back({xnow, ynow});
        }
        for (int i = 0; i < cooordinatesallowed.size(); ++i) {
            if (tolower(BOARD.getBoard(cooordinatesallowed[i].first, cooordinatesallowed[i].second)) == OTHERPLAYER) {
                if (BOARD.getBoard(cooordinatesallowed[i].first - 1, cooordinatesallowed[i].second - 1) == '#') {
                    cooordinatesallowed.clear();
                    return true;
                }
            }
        }
        cooordinatesallowed.clear();
    }
    return false;
}

bool CrownRules::downRightDirection(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER,
                                    Board &BOARD) {
    xnow = x1;
    ynow = y1;
    if (x2 > x1 && y2 > y1) {
        while (xnow < x2 && ynow < y2) {
            ++xnow;
            ++ynow;
            cooordinatesallowed.push_back({xnow, ynow});
        }
        for (int i = 0; i < cooordinatesallowed.size(); ++i) {
            if (tolower(BOARD.getBoard(cooordinatesallowed[i].first, cooordinatesallowed[i].second)) == OTHERPLAYER) {
                if (BOARD.getBoard(cooordinatesallowed[i].first + 1, cooordinatesallowed[i].second + 1) == '#') {
                    cooordinatesallowed.clear();
                    return true;
                }
            }
        }
        cooordinatesallowed.clear();
    }
    return false;
}

bool CrownRules::downLeftDirection(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER,
                                   Board &BOARD) {
    xnow = x1;
    ynow = y1;
    if (x2 < x1 && y2 > y1) {
        while (xnow > x2 && ynow < y2) {
            --xnow;
            ++ynow;
            cooordinatesallowed.push_back({xnow, ynow});
        }
        for (int i = 0; i < cooordinatesallowed.size(); ++i) {
            if (tolower(BOARD.getBoard(cooordinatesallowed[i].first, cooordinatesallowed[i].second)) == OTHERPLAYER) {
                if (BOARD.getBoard(cooordinatesallowed[i].first + 1, cooordinatesallowed[i].second + 1) == '#') {
                    cooordinatesallowed.clear();
                    return true;
                }
            }
        }
        cooordinatesallowed.clear();
    }
    return false;
}

bool
CrownRules::legalMove(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER, Board &BOARD,
                      string &error, const int &onemove, const int &currentx, const int &currenty) {
    if (onemove == 0 &&
        ((currentx != x1 && currenty != y1) ||
         (!upRightCapture(x1, y1, x2, y2, OTHERPLAYER, BOARD) &&
          !upLeftCapture(x1, y1, x2, y2, OTHERPLAYER, BOARD) &&
          !downRightCapture(x1, y1, x2, y2, OTHERPLAYER, BOARD) &&
          !downLeftCapture(x1, y1, x2, y2, OTHERPLAYER, BOARD)))) {
        error = "Case: Not an allowed move for a crown piece.";
        return false;
    }
    if (upRightDirection(x1, y1, x2, y2, OTHERPLAYER, BOARD)) {
        xnow = x1;
        ynow = y1;
        while (xnow < 9 && ynow > 0) {
            ++xnow;
            --ynow;
            cooordinatesallowed.push_back({xnow, ynow});
        }
        for (int i = 0; i < cooordinatesallowed.size(); ++i) {
            if (x2 == cooordinatesallowed[i].first && y2 == cooordinatesallowed[i].second) {
                cooordinatesallowed.clear();
                return true;
            }
        }
        cooordinatesallowed.clear();
    } else if (upLeftDirection(x1, y1, x2, y2, OTHERPLAYER, BOARD)) {
        xnow = x1;
        ynow = y1;
        while (xnow > 0 && ynow > 0) {
            --xnow;
            --ynow;
            cooordinatesallowed.push_back({xnow, ynow});
        }
        for (int i = 0; i < cooordinatesallowed.size(); ++i) {
            if (x2 == cooordinatesallowed[i].first && y2 == cooordinatesallowed[i].second) {
                cooordinatesallowed.clear();
                return true;
            }
        }
        cooordinatesallowed.clear();
    } else if (downRightDirection(x1, y1, x2, y2, OTHERPLAYER, BOARD)) {
        xnow = x1;
        ynow = y1;
        while (xnow < 9 && ynow < 9) {
            ++xnow;
            ++ynow;
            cooordinatesallowed.push_back({xnow, ynow});
        }
        for (int i = 0; i < cooordinatesallowed.size(); ++i) {
            if (x2 == cooordinatesallowed[i].first && y2 == cooordinatesallowed[i].second) {
                cooordinatesallowed.clear();
                return true;
            }
        }
        cooordinatesallowed.clear();
    } else if (downLeftDirection(x1, y1, x2, y2, OTHERPLAYER, BOARD)) {
        xnow = x1;
        ynow = y1;
        while (xnow > 0 && ynow < 9) {
            --xnow;
            ++ynow;
            cooordinatesallowed.push_back({xnow, ynow});
        }
        for (int i = 0; i < cooordinatesallowed.size(); ++i) {
            if (x2 == cooordinatesallowed[i].first && y2 == cooordinatesallowed[i].second) {
                cooordinatesallowed.clear();
                return true;
            }
        }
        cooordinatesallowed.clear();
    }
    error = "Case: Not an allowed move for a crown piece.";
    return false;
}

bool CrownRules::upRightCapture(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER,
                                Board &BOARD) {
    if (upRightDirection(x1, y1, x2, y2, OTHERPLAYER, BOARD)) {
        xnow = x1;
        ynow = y1;
        while (xnow < x2 && ynow > y2) {
            ++xnow;
            --ynow;
            cooordinatesallowed.push_back({xnow, ynow});
        }
        for (int i = 0; i < cooordinatesallowed.size(); ++i) {
            if (tolower(BOARD.getBoard(cooordinatesallowed[i].first, cooordinatesallowed[i].second)) == OTHERPLAYER) {
                cooordinatesallowed.clear();
                return true;
            }
        }
        cooordinatesallowed.clear();
    }
    return false;
}

bool CrownRules::upLeftCapture(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER,
                               Board &BOARD) {
    if (upLeftDirection(x1, y1, x2, y2, OTHERPLAYER, BOARD)) {
        xnow = x1;
        ynow = y1;
        while (xnow > x2 && ynow > y2) {
            --xnow;
            --ynow;
            cooordinatesallowed.push_back({xnow, ynow});
        }
        for (int i = 0; i < cooordinatesallowed.size(); ++i) {
            if (tolower(BOARD.getBoard(cooordinatesallowed[i].first, cooordinatesallowed[i].second)) == OTHERPLAYER) {
                cooordinatesallowed.clear();
                return true;
            }
        }
        cooordinatesallowed.clear();
    }
    return false;
}

bool CrownRules::downRightCapture(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER,
                                  Board &BOARD) {
    if (downRightDirection(x1, y1, x2, y2, OTHERPLAYER, BOARD)) {
        xnow = x1;
        ynow = y1;
        while (xnow < x2 && ynow < y2) {
            ++xnow;
            ++ynow;
            cooordinatesallowed.push_back({xnow, ynow});
        }
        for (int i = 0; i < cooordinatesallowed.size(); ++i) {
            if (tolower(BOARD.getBoard(cooordinatesallowed[i].first, cooordinatesallowed[i].second)) == OTHERPLAYER) {
                cooordinatesallowed.clear();
                return true;
            }
        }
        cooordinatesallowed.clear();
    }
    return false;
}

bool CrownRules::downLeftCapture(const int &x1, const int &y1, const int &x2, const int &y2, const char &OTHERPLAYER,
                                 Board &BOARD) {
    if (downLeftDirection(x1, y1, x2, y2, OTHERPLAYER, BOARD)) {
        xnow = x1;
        ynow = y1;
        while (xnow > x2 && ynow < y2) {
            --xnow;
            ++ynow;
            cooordinatesallowed.push_back({xnow, ynow});
        }
        for (int i = 0; i < cooordinatesallowed.size(); ++i) {
            if (tolower(BOARD.getBoard(cooordinatesallowed[i].first, cooordinatesallowed[i].second)) == OTHERPLAYER) {
                cooordinatesallowed.clear();
                return true;
            }
        }
        cooordinatesallowed.clear();
    }
    return false;
}

bool
CrownRules::captureAvailable(const int &x1, const int &y1, const int &x2, const int &y2, char OTHERPLAYER, Board &BOARD,
                             string &error, const string &previousdirection, const int &checkeverydirection) {
    if (checkeverydirection == 0) {
        if (upRightCapture(x1, y1, x2, y2, OTHERPLAYER, BOARD) ||
            upLeftCapture(x1, y1, x2, y2, OTHERPLAYER, BOARD) ||
            downRightCapture(x1, y1, x2, y2, OTHERPLAYER, BOARD) ||
            downLeftCapture(x1, y1, x2, y2, OTHERPLAYER, BOARD)) {
            return true;
        }
    } else if (checkeverydirection == 1) {
        if (previousdirection == "ur") {
            if (upRightCapture(x2, y2, 9, 0, OTHERPLAYER, BOARD) ||
                upLeftCapture(x2, y2, 0, 0, OTHERPLAYER, BOARD) ||
                downRightCapture(x2, y2, 9, 9, OTHERPLAYER, BOARD)) {
                error = "Case: There is at least one more compulsory capture.";
                return true;
            }
        } else if (previousdirection == "ul") {
            if (upRightCapture(x2, y2, 9, 0, OTHERPLAYER, BOARD) ||
                upLeftCapture(x2, y2, 0, 0, OTHERPLAYER, BOARD) ||
                downLeftCapture(x2, y2, 0, 9, OTHERPLAYER, BOARD)) {
                error = "Case: There is at least one more compulsory capture.";
                return true;
            }
        } else if (previousdirection == "dr") {
            if (upRightCapture(x2, y2, 9, 0, OTHERPLAYER, BOARD) ||
                downRightCapture(x2, y2, 9, 9, OTHERPLAYER, BOARD) ||
                downLeftCapture(x2, y2, 0, 9, OTHERPLAYER, BOARD)) {
                error = "Case: There is at least one more compulsory capture.";
                return true;
            }
        } else if (previousdirection == "dl") {
            if (upLeftCapture(x2, y2, 0, 0, OTHERPLAYER, BOARD) ||
                downRightCapture(x2, y2, 9, 9, OTHERPLAYER, BOARD) ||
                downLeftCapture(x2, y2, 0, 9, OTHERPLAYER, BOARD)) {
                error = "Case: There is at least one more compulsory capture.";
                return true;
            }
        }
    }
    return false;
}

/*---------------------------------------------------------------------------------------------------------*/
vector<pair<int, int>> Rules::coordinatestocheck;

//Lose for someone who has 0 moves.
//Draw if none of them have any moves, or if both players have a crown.
bool Rules::endgame(Board &BOARD) {
    OrdinaryRules Ordinary;
    int apossiblemoves = 0, bpossiblemoves = 0, acrowns = 0, bcrowns = 0;
    string nth;
    auto coordinatesToCheck = [&](int x, int y) {
        vector<pair<int, int>> a;
        a.push_back({x - 1, y + 1});
        a.push_back({x - 1, y - 1});
        a.push_back({x + 1, y + 1});
        a.push_back({x + 1, y - 1});
        a.push_back({x - 2, y + 2});
        a.push_back({x - 2, y - 2});
        a.push_back({x + 2, y + 2});
        a.push_back({x + 2, y - 2});
        return a;
    };
    /*---------------------------------------------------------------------------------------------------------*/
    for (int y = 0; y < 10; ++y) {
        for (int x = 0; x < 10; ++x) {
            BOARD.getBoard(x, y) == 'A' ? ++acrowns : (BOARD.getBoard(x, y) == 'B' ? ++bcrowns : 0);
        }
    }
    if (acrowns > 0 && bcrowns > 0) {
        cout << "\n\nYou drew the game, great job!!\n";
        UserInterface::delayScreen();
        return true;
    }
    acrowns > 0 ? ++apossiblemoves : (bcrowns > 0 ? ++bpossiblemoves : 0);
    for (int y = 0; y < 10; ++y) {
        for (int x = 0; x < 10; ++x) {
            coordinatestocheck = coordinatesToCheck(x, y);
            if (BOARD.getBoard(x, y) == 'a') {
                for (short i = 0; i < coordinatestocheck.size(); ++i) {
                    if (Rules::basicRules(x, y, coordinatestocheck[i].first, coordinatestocheck[i].second, 'a', BOARD,
                                          nth) &&
                        Ordinary.legalMove(x, y, coordinatestocheck[i].first, coordinatestocheck[i].second, 'b', BOARD,
                                           nth, 1, 1, 1) &&
                        (Ordinary.moveAvailable(x, y, BOARD) ||
                         Ordinary.captureAvailable(x, y, coordinatestocheck[i].first, coordinatestocheck[i].second, 'b',
                                                   BOARD, nth, nth))) {
                        apossiblemoves++;
                    }
                }
            } else if (BOARD.getBoard(x, y) == 'b') {
                for (short i = 0; i < coordinatestocheck.size(); ++i) {
                    if (Rules::basicRules(x, y, coordinatestocheck[i].first, coordinatestocheck[i].second, 'b', BOARD,
                                          nth) &&
                        Ordinary.legalMove(x, y, coordinatestocheck[i].first, coordinatestocheck[i].second, 'a', BOARD,
                                           nth, 1, 1, 1) &&
                        (Ordinary.moveAvailable(x, y, BOARD) ||
                         Ordinary.captureAvailable(x, y, coordinatestocheck[i].first, coordinatestocheck[i].second, 'a',
                                                   BOARD, nth, nth))) {
                        bpossiblemoves++;
                    }
                }
            }
        }
    }
    /*---------------------------------------------------------------------------------------------------------*/
    if (apossiblemoves == 0 && bpossiblemoves == 0) {
        cout << "\n\nYou drew the game, great job!!\n";
        UserInterface::delayScreen();
        return true;
    } else if (apossiblemoves == 0 && acrowns == 0) {
        cout << "\n\nPlayer [b] Wins, great job!!\n";
        UserInterface::delayScreen();
        return true;
    } else if (bpossiblemoves == 0 && bcrowns == 0) {
        cout << "\n\nPlayer [a] Wins, great job!!\n";
        UserInterface::delayScreen();
        return true;
    }
    return false;
}
/*---------------------------------------------------------------------------------------------------------*/
