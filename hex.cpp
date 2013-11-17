#ifndef _HEX_H
#define _HEX_H

#include <iostream>

#include "board.cpp"
#include "player.cpp"

using namespace std;

class Hex
{
  public:
    Hex(int size = 11) {
      board = new Board(size);

      player1 = new Player();
      player2 = new Player();
      //player1->getName();
      //player2->getName();
    }

    Player* runMatch() {
      current = player1;
      while (1) {
        refresh();
        int move;
        // repeat until we have a legal move
        while (!board->checkMove(move = current->getMove()))
            ;

        board->recordMove(current->getID(), move);
        if (board->checkWin())
          // winner, break while (1)
          break; 
        
        nextPlayer();
      }

      return current;
    }

    // changes who is the current player
    void nextPlayer() {
      if (current == player1) current = player2;
      else                    current = player1;
    }

    void refresh() {
      cout << (*board) << endl;
    } // redraws the board, along with any messages necessary

    friend ostream& operator<<(ostream& out, Hex hex)
    {
      cout << "Hex game" << endl;
      return out;
    }
  private:
    string message;
    Board* board;
    Player* current;
    Player* player1;
    Player* player2;
};

#endif  // _HEX_H
