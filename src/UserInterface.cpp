#include "UserInterface.hpp"

void UserInterface::start(char &PLAYER, Board &BOARD) //Main game menu.
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int choice;
    clearScreen();
    cout << "----------------------------------------------\n"
         << "|         International Checkers Game        |\n"
         << "----------------------------------------------\n"
         << " 1. New game                                  \n"
         << " 2. Load game                                 \n"
         << " 3. Exit                                      \n"
         << "----------------------------------------------\n"
         << "->";
    cin >> choice;
    validInput(choice, 1, 3);
    clearScreen();
    switch (choice)
    {
    case 1:
        Game::start(PLAYER, BOARD);
        break;
    case 2:
        File::read(BOARD, PLAYER);
        clearScreen();
        Game::start(PLAYER, BOARD);
        break;
    default:
        clearScreen();
        break;
    }
}

void UserInterface::validInput(int &input, const int &minrange, const int &maxrange, const string &error) //Takes a variable, checks if it is an integer and within the range given. If not, outputs given or default error message, asks to re-enter variable's value.
{
    while (!cin || input < minrange || input > maxrange)
    {
        cin.clear();
        cin.ignore();
        cout << error;
        cin >> input;
    }
    cin.ignore();
}

void UserInterface::clearScreen() //Clearing screen depending on operating system being used, using preprocessor directives to return operating system type.
{
#ifdef _WIN32
    system("cls");
#elif _WIN64
    system("cls");
#else
    system("clear");
#endif
}

void UserInterface::delayScreen(const double &Seconds) //Delaying screen with optional timing depending on operating system being used, using preprocessor directives to return operating system type.
{
#ifdef _WIN32
    sleep(Seconds * 1000);
#elif _WIN64
    sleep(Seconds * 1000);
#else
    sleep(Seconds);
#endif
}
