#ifndef _HEX_H
#define _HEX_H

#include <iostream>

#include "board.cpp"
#include "player.cpp"

using namespace std;

class Hex
{
  public:
    Hex()
    {}

    friend ostream& operator<<(ostream& out, Hex hex)
    {
      cout << "Hex game" << endl;
      return out;
    }
};

#endif  // _HEX_H
