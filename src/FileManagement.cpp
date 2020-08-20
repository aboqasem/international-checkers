#include "FileManagement.hpp"
/*---------------------------------------------------------------------------------------------------------*/
void File::write(Board &BOARD, const char &PLAYER)
{
    ios::sync_with_stdio(false); cin.tie(NULL);
    ofstream fout; string name;
    UserInterface::clearScreen();
    cout << "----------------------------------------------\n";
    cout << "Name the game file ->"; cin >> name; cin.ignore();
    validName(name);
    fout.open(name+".txt");
    if (!fout)
    {
        UserInterface::clearScreen();
        cout << "Error: [S] Game file couldn't be saved.\n";
    }
    else
    {

        fout << "Next player: " << PLAYER << endl;
        for (int y=0; y<10; ++y)
        {
            for (int x=0; x<10; ++x){fout << BOARD.getBoard(x, y);}
            fout << endl;
        }
        fout.close();
        UserInterface::clearScreen();
        cout << "[S] Game saved successfully!\n";
    }
    UserInterface::delayScreen();
}
/*---------------------------------------------------------------------------------------------------------*/
void File::read(Board &BOARD, char &PLAYER)
{
    ios::sync_with_stdio(false); cin.tie(NULL);
    string temp, name; int y=-1; ifstream fin;
    UserInterface::clearScreen();
    cout << "----------------------------------------------\n";
    cout << "Name of the game file ->"; cin >> name; cin.ignore();
    validName(name);
    fin.open(name+".txt");
    if (!fin)
    {
        UserInterface::clearScreen();
        cout << "Error: [L] Game file doesn't exist.\n";
    }
    else
    {
        while (getline(fin, temp) && y<10)
        {
            if (y==-1){PLAYER=temp[13];}
            else
            {
                for (int x=0; x<10; ++x){BOARD.setBoard(x, y, temp[x]);}
            }
            ++y;
        }
        fin.close();
        UserInterface::clearScreen();
        cout << "[L] Game loaded successfully!\n";
    }
    UserInterface::delayScreen();
}
/*---------------------------------------------------------------------------------------------------------*/
void File::validName(string &name)
{
    for_each(name.begin(), name.end(), [](char &c){c=='.'?c=0:c=c;});
}
/*---------------------------------------------------------------------------------------------------------*/
