#include "GameHandling.hpp"
/*------------------------------------------------------------------------------------------------*/
void Game::start(char &PLAYER, Board &BOARD) //Handling and applying rules to the game.
{
    ios::sync_with_stdio(false); cin.tie(NULL);
    string y1x1, y2x2, error, previousdirection; int x1=-1, y1=-1, x2=-1, y2=-1, xnow=-1, ynow=-1, previousx=10, previousy=10, currentx=10, currenty=10, onemove=1; char OTHERPLAYER; vector<pair<int, int>> coordinatestocapture;
    Rules *Ordinary = new OrdinaryRules; Rules *Crown = new CrownRules;
    do {
        previousdirection="";
        cout << "----------------------------------------------\n"
             << "Enter from-to indices:       -      (->7b 6c).\n"
             << "To save the game enter S:    -      (->S    ).\n"
             << "To load a game enter L:      -      (->L    ).\n"
             << "To exit enter 0:             -      (->0    ).\n"
             << "----------------------------------------------\n"; BOARD.printBoard(); if(Rules::endgame(BOARD)){break;};
        PLAYER % 2 != 0 ? PLAYER = 'a' : PLAYER = 'b'; PLAYER == 'a' ? OTHERPLAYER = 'b' : OTHERPLAYER = 'a';
        cout << endl << error << endl; error=""; cout << "\n# Player [" << PLAYER << "] turn ->";
        cin >> y1x1; for_each(y1x1.begin(), y1x1.end(), [](char &c){c=tolower(c);});
        if(y1x1[0] != '0' && y1x1[0] != 's' && y1x1[0] != 'l'){ cin >> y2x2; for_each(y2x2.begin(), y2x2.end(), [](char &c){c=tolower(c);});}
        /*-------------------------------------------------------------------------------------------------*/
        if (y1x1[0] != '0' && y1x1[0] != 's' && y1x1[0] != 'l')
        {
            setCoordinates(y1x1, y2x2, x1, y1, x2, y2);
            if (previousx==x2 && previousy==y2)
            {
                error="Case: You cannot go back to your place.";
            }
            else if (Rules::basicRules(x1, y1, x2, y2, PLAYER, BOARD, error))
            {
                if (BOARD.getBoard(x1, y1)==PLAYER && Ordinary->legalMove(x1, y1, x2, y2, OTHERPLAYER, BOARD, error, onemove, currentx, currenty))
                {
                    previousx=previousy=10;
                    currentx=currenty=10;
                    BOARD.setBoard(x1, y1, '#');
                    if (Ordinary->captureAvailable(x1, y1, x2, y2, OTHERPLAYER, BOARD, error, previousdirection))
                    {
                        if (Ordinary->upRightCapture(x1, y1, x2, y2, OTHERPLAYER, BOARD))
                        {
                            coordinatestocapture.push_back({x1+1, y1-1});
                            previousdirection = "ur";
                        }
                        else if (Ordinary->upLeftCapture(x1, y1, x2, y2, OTHERPLAYER, BOARD))
                        {
                            coordinatestocapture.push_back({x1-1, y1-1});
                            previousdirection = "ul";
                        }
                        else if (Ordinary->downRightCapture(x1, y1, x2, y2, OTHERPLAYER, BOARD))
                        {
                            coordinatestocapture.push_back({x1+1, y1+1});
                            previousdirection = "dr";
                        }
                        else if (Ordinary->downLeftCapture(x1, y1, x2, y2, OTHERPLAYER, BOARD))
                        {
                            coordinatestocapture.push_back({x1-1, y1+1});
                            previousdirection = "dl";
                        }
                    }
                    BOARD.setBoard(x2, y2, PLAYER);
                    if (Ordinary->captureAvailable(0, 0, x2, y2, OTHERPLAYER, BOARD, error, previousdirection, 1))
                    {
                        onemove=0;
                        previousx=x1; previousy=y1;
                        currentx=x2; currenty=y2;
                    }
                    else
                    {
                        onemove=1;
                        for (int i=0; i<coordinatestocapture.size(); ++i)
                        {
                            BOARD.setBoard(coordinatestocapture[i].first, coordinatestocapture[i].second, '#');
                        }
                        coordinatestocapture.clear();
                        if (Rules::becomeCrown(y2, PLAYER)){BOARD.setBoard(x2, y2, toupper(PLAYER));};
                        ++PLAYER;
                    }
                }
                else if (BOARD.getBoard(x1, y1)==toupper(PLAYER) && Crown->legalMove(x1, y1, x2, y2, OTHERPLAYER, BOARD, error, onemove, currentx, currenty))
                {
                    previousx=previousy=10;
                    currentx=currenty=10;
                    BOARD.setBoard(x1, y1, '#');
                    if (Crown->captureAvailable(x1, y1, x2, y2, OTHERPLAYER, BOARD, error, previousdirection))
                    {
                        if (Crown->upRightCapture(x1, y1, x2, y2, OTHERPLAYER, BOARD))
                        {
                            xnow=x1; ynow=y1;
                            while (xnow<x2 && ynow>y2)
                            {
                                ++xnow; --ynow;
                                if (BOARD.getBoard(xnow, ynow)==OTHERPLAYER)
                                {
                                    coordinatestocapture.push_back({xnow, ynow});
                                }
                            }
                            previousdirection = "ur";
                        }
                        else if (Crown->upLeftCapture(x1, y1, x2, y2, OTHERPLAYER, BOARD))
                        {
                            xnow=x1; ynow=y1;
                            while (xnow>x2 && ynow>y2)
                            {
                                --xnow; --ynow;
                                if (BOARD.getBoard(xnow, ynow)==OTHERPLAYER)
                                {
                                    coordinatestocapture.push_back({xnow, ynow});
                                }
                            }
                            previousdirection = "ul";
                        }
                        else if (Crown->downRightCapture(x1, y1, x2, y2, OTHERPLAYER, BOARD))
                        {
                            xnow=x1; ynow=y1;
                            while (xnow<x2 && ynow<y2)
                            {
                                ++xnow; ++ynow;
                                if (BOARD.getBoard(xnow, ynow)==OTHERPLAYER)
                                {
                                    coordinatestocapture.push_back({xnow, ynow});
                                }
                            }
                            previousdirection = "dr";
                        }
                        else if (Crown->downRightCapture(x1, y1, x2, y2, OTHERPLAYER, BOARD))
                        {
                            xnow=x1; ynow=y1;
                            while (xnow>x2 && ynow<y2)
                            {
                                --xnow; ++ynow;
                                if (BOARD.getBoard(xnow, ynow)==OTHERPLAYER)
                                {
                                    coordinatestocapture.push_back({xnow, ynow});
                                }
                            }
                            previousdirection = "dl";
                        }
                    }
                    BOARD.setBoard(x2, y2, toupper(PLAYER));
                    if (Crown->captureAvailable(0, 0, x2, y2, OTHERPLAYER, BOARD, error, previousdirection, 1))
                    {
                        onemove=0;
                        previousx=x1; previousy=y1;
                        currentx=x2; currenty=y2;
                    }
                    else
                    {
                        onemove=1;
                        for (int i=0; i<coordinatestocapture.size(); ++i)
                        {
                            BOARD.setBoard(coordinatestocapture[i].first, coordinatestocapture[i].second, '#');
                        }
                        coordinatestocapture.clear();
                        ++PLAYER;
                    }
                }
            }
        }
        /*------------------------------------------------------------------------------------------------*/
        else if (y1x1[0] == 's')
        {
            error="";
            File::write(BOARD, PLAYER);
        }
        /*-------------------------------------------------------------------------------------------------*/
        else if (y1x1[0] == 'l')
        {
            error="";
            File::read(BOARD, PLAYER);
        }
        /*-------------------------------------------------------------------------------------------------*/
        else if (y1x1[0] == '0')
        {
            UserInterface::clearScreen();
            break;
        }
        /*-------------------------------------------------------------------------------------------------*/
        UserInterface::clearScreen();
    } while (1);
}
/*------------------------------------------------------------------------------------------------*/
map<char, int> Game::Y = {{'1',0}, {'2',1}, {'3',2}, {'4',3}, {'5',4}, {'6',5}, {'7',6}, {'8',7}, {'9',8}};
map<char, int> Game::X = {{'a',0}, {'b',1}, {'c',2}, {'d',3}, {'e',4}, {'f',5}, {'g',6}, {'h',7}, {'i',8}, {'j',9}};
void Game::setCoordinates(const string &y1x1, const string &y2x2, int &x1, int &y1, int &x2, int &y2) //Converting user input to coordiinates.
{
    if (y1x1[0]=='1'&&y1x1[1]=='0'&&y1x1[2]>='a'&&y1x1[2]<='j')
    {
        y1 = 9; x1 = X[y1x1[2]];
    }
    else if (y1x1[0]>='1'&&y1x1[0]<='9'&&y1x1[1]>='a'&&y1x1[1]<='j')
    {
        y1 = Y[y1x1[0]]; x1 = X[y1x1[1]];
    }
    else
    {
        y1=-1; x1=-1;
    }
    if (y2x2[0]=='1'&&y2x2[1]=='0'&&y2x2[2]>='a'&&y2x2[2]<='j')
    {
        y2 = 9; x2 = X[y2x2[2]];
    }
    else if (y2x2[0]>='1'&&y2x2[0]<='9'&&y2x2[1]>='a'&&y2x2[1]<='j')
    {
        y2 = Y[y2x2[0]]; x2 = X[y2x2[1]];
    }
    else
    {
        y2=-1; x2=-1;
    }
}
/*------------------------------------------------------------------------------------------------*/
