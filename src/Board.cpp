#include "Board.hpp"

/*---------------------------------------------------------------------------------------------------------*/
void Board::printBoard() //Board printer.
{
    ios::sync_with_stdio(false);
    for (int y = 0; y < 10; ++y)
    {
        cout << "   |---+---+---+---+---+---+---+---+---+---|\n"
             << (y < 9 ? " " : "") << y + 1 << " ";
        for (int x = 0; x < 10; ++x)
        {
            cout << "| " << board[y][x] << " ";
        }
        cout << "|" << endl;
    }
    cout << "   |---+---+---+---+---+---+---+---+---+---|\n     a   b   c   d   e   f   g   h   i   j\n";
}

/*---------------------------------------------------------------------------------------------------------*/
char Board::getBoard(const int &x, const int &y) //Board getter.
{
    return board[y][x];
}

void Board::setBoard(const int &x, const int &y, const char &c) //Board setter.
{
    board[y][x] = c;
}
/*---------------------------------------------------------------------------------------------------------*/
