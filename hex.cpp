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

    Player* runMatch(); // returns winner of the match
    void nextPlayer(); // changes who is the current player
    void refresh(); // redraws the board, along with any messages necessary

    friend ostream& operator<<(ostream& out, Hex hex)
    {
      cout << "Hex game" << endl;
      return out;
    }
  private:
    Board* board;
    Player* current;
    Player* player1;
    Player* player2;
};

#endif  // _HEX_H
