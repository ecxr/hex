#ifndef _PLAYER_H
#define _PLAYER_H

#include <iostream>

using namespace std;

class Player
{
  public:
    Player()
    {
    }

    friend ostream& operator<<(ostream& out, Player player)
    {
      cout << "Player" << endl;
      return out;
    }
};

#endif // _PLAYER_H
