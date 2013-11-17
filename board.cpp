#ifndef _BOARD_H
#define _BOARD_H

#include <iostream>
#include <vector>

#include "../graph2/graph.h"

using namespace std;

const int UNPLAYED = 0;
const int X_PLAYED = 1;
const int O_PLAYED = 2;

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

      connLine.resize(size * 4);
      for (int i = 0; i < size; i++) {
        if (i != size-1) {
          connLine += " \\ /";
        } else {
          connLine += " \\";
        }
      }
      graph = new Graph(size * size);
      // TODO initialize node values to unplayed
    }

    bool checkMove(int move) { return true; } // is the proposed move legal?
    bool checkWin() { return false; } // check if latest move makes the last player win
    void recordMove(int player, int move) {
      board[move / size][move / size] = player;
    } // saves the move

    friend ostream& operator<<(ostream& out, Board b)
    {
      out << "Board" << endl;
      for (int i = 0; i < b.size; i++) {
        // each line is indented a little further than the last
        for (int j = 0; j < 2 * i; j++) {
          out << " ";
        }
      
      // display the cells and their connections
        for (int j = 0; j < b.size; j++) {
          out << b.board[i][j];
          if (j != b.size - 1) {
            out << " - ";
          } else {
            out << endl;
          }
        }

        // connections between rows
        if (i != b.size - 1) {
          for (int j = 0; j < 2 * i; j++) {
            out << " ";
          }
          out << b.connLine << endl;
        }
      }
      return out;
    }

  private:
    int size;
    string connLine;
    vector<vector<int> > board;
    Graph* graph;
};

#endif // _BOARD_H
