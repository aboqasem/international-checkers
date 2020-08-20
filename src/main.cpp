#include "UserInterface.hpp"
char PLAYER = 'a';
Board BOARD;

int main()
{
    ios::sync_with_stdio(false);
    UserInterface::start(PLAYER, BOARD);
    cout << "\nGood bye!\n\n";
    UserInterface::delayScreen();
    return 0;
}