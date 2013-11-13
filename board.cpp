#ifndef _BOARD_H
#define _BOARD_H

#include <iostream>
#include <vector>

#include "../graph2/graph.h"

using namespace std;

class Board
{
  public:
    Board(int sizeIn)
    {
      size = sizeIn;
      board.resize(size);
      for (int i = 0; i < size; i++) {
        board[i].resize(size);
        for (int j = 0; j < size; j++) {
          board[i][j] = UNPLAYED;
        }
      }
      graph = new Graph(size * size);
      // TODO initialize node values to unplayed
    }

    friend ostream& operator<<(ostream& out, Board board)
    {
      out << "Board" << endl;
      return out;
    }

  private:
    const int UNPLAYED = 0;
    const int X_PLAYED = 1;
    const int O_PLAYED = 2;
    int size;
    vector<vector<int> > board;
    Graph* graph;
};

#endif // _BOARD_H
