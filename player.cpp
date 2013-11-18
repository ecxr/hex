#ifndef _PLAYER_H
#define _PLAYER_H

#include <iostream>
#include <string>

using namespace std;

class Player
{
public:
    Player()
    {
        cout << "initializing player!";
        ID = 0;
    }

    // get move from player - shows prompt for humans
    int getMove()
    {
        int move;
        cout << "Enter your move:  ";
        cin >> move;
        return move;
    }

    // for human players
    string getName()
    {
        return "";
    }

    // sets name for humans
    void setName(const char* newName)
    {
        //  strncpy(name, newName, sizeof(name));
    }

    int getID()
    {
        return ID;
    }

    void setID(int id)
    {
        ID = id;
    }

    friend ostream& operator<<(ostream& out, Player player)
    {
        //out << player.name_ << endl;
        out << "player #" << player.ID << endl;
        return out;
    }

private:
    string name_();
    int ID;
};

#endif // _PLAYER_H
