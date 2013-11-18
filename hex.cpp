#ifndef _HEX_H
#define _HEX_H

#include <iostream>

#include "board.cpp"
#include "player.cpp"

using namespace std;

class Hex
{
public:
    Hex(int size = 11)
    {
        board = new Board(size);
        current = 1;
    }

    int runMatch()
    {
        // set current player
        current = 1;

        while (1)
        {
            refresh();

            // repeat until we have a legal move
            int move = getMove();
            while (!board->checkMove(move))
            {
                refresh("Invalid move");
                move = getMove();
            }

            board->recordMove(current, move);
            if (board->checkWin())
                return current;
                break;

            nextPlayer();
        }

        return current;
    }

    // convert from (i, j) coordinate to 1D array index
    int coordTo1D(int i, int j)
    {
        return i * board->getSize() + j;
    }

    // get move for current player
    int getMove()
    {
        int i, j = 0;
        cout << "(Player " << current << ") Enter i j coordinates: ";
        cin >> i >> j;
        int id = coordTo1D(i, j);
        // cout << endl << "(" << i << "," << j << ") = " << id << endl;
        return id;
    }

    // changes to the next player
    void nextPlayer()
    {
        current = (current % 2) + 1;
    }

    // redraws the board, along with any messages necessary
    void refresh(const char* message = "")
    {
        cout << (*board) << endl;
        if (message != "")
            cout << message << endl;
    }

private:
    Board* board;
    int current;
};

#endif  // _HEX_H
