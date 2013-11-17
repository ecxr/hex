#ifndef _PLAYER_H
#define _PLAYER_H

#include <iostream>

using namespace std;

class Player
{
  public:
    Player() {
      cout << "initializing player!";
    }

    int getMove(); // get move from player - shows prompt for humans
    const char* getName(); // for human players
    void setName(const char* newName); // for human players
    friend ostream& operator<<(ostream& out, Player player)
    {
      cout << "Player" << endl;
      return out;
    }
};

#endif // _PLAYER_H
