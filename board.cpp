#ifndef _BOARD_H
#define _BOARD_H

#include <iostream>
#include <vector>

#include "graph.h"
#include "ShortestPath.h"

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
        for (int i = 0; i < size; i++)
        {
            board[i].resize(size);
            for (int j = 0; j < size; j++)
            {
                board[i][j] = UNPLAYED;
            }
        }

        connLine.resize(size * 4);
        for (int i = 0; i < size; i++)
        {
            if (i != size - 1)
            {
                connLine += " \\ /";
            }
            else
            {
                connLine += " \\";
            }
        }
        graph1 = new Graph(size * size);
        graph2 = new Graph(size * size);
    }

    int getSize()
    {
        return size;
    }

    // is the proposed move legal?
    bool checkMove(int move)
    {
        if ((move < 0) || (move > (size*size) - 1))
            return false;

        return board[move / size][move % size] == 0;
    }

    // check if latest move makes the last player win
    bool checkWin()
    {
        bool winner = false;
        vector<int> path;

        // Check player 1
        // for each top edge row:
        for (int i = 0; i < size; ++i)
        {
            ShortestPath sp(graph1, i);
            // is there a path to any bottom edged row?
            unsigned int path_size;
            path = sp.pathTo(size*size-1-i);
            path_size = path.size();
            if (path_size >= size && path_size != INFINITY)
            {
                cout << "Shortest Path found from " << i << " to " << size*size-1-i;
                return true;
                break;
            }
        }

        // Check player 2
        // for each edge on the left:
        for (int i = 0; i < size; ++i)
        {
            ShortestPath sp(graph2, i*size);
            // is there a path to any right-edge row?
            unsigned int path_size;
            path = sp.pathTo((i+1)*size - 1);
            path_size = path.size();
            if (path_size >= size && path_size != INFINITY)
            {
                cout << "Shortest Path found from " << i << " to " << size*size-1-i;
                return true;
                break;
            }
        }

        return false;
    }

    // connects edge from u to v if w is also owned by player in g
    void connect(int player, Graph* g, int u, int v)
    {
        // convert 1D to 2D
        int ui = u / size;
        int uj = u % size;
        int vi = v / size;
        int vj = v % size;

        if (board[vi][vj] == player)
        {
            // player owns passed in adjacent square, create an edge in g
            cout << "Creating edge from " << ui << "," << uj << " to " << vi << "," << vj << endl;
            g->addEdge(u, v, 1.0);
        }
    }
    // connects adjacently owned tiles in the graph
    void connectTiles(int player, int move)
    {
        Graph* g;

        // select appropriate graph
        if (player == 1) g = graph1;
        else             g = graph2;

        // convert 1D to i, j
        int i = move / size;
        int j = move % size;

        // find 1D indexes in all directions
        int E  = (i     * size) + (j-1); // or move-1
        int W = (i     * size) + (j+1); // or move+1
        int SE    = ((i+1) * size) + j;
        int SW    = ((i+1) * size) + (j - 1);
        int NW    = ((i-1) * size) + j;
        int NE    = ((i-1) * size) + (j + 1);

        // Are we a upper left corner tile?
        if (i == 0 && j == 0)
        {
            cout << "Top Left Corner" << endl;
            // neighbors are E, SE
            connect(player, g, move, E);
            connect(player, g, move, SE);
        }
        // Are we an upper right corner tile?
        else if (i == 0 && j == size - 1)
        {
            cout << "Top Right Corner" << endl;
            // neighbors are W, SW, SE
            connect(player, g, move, W);
            connect(player, g, move, SW);
            connect(player, g, move, SE);
        }
        // Are we a lower left corner tile?
        else if (i == size - 1 && j == 0)
        {
            cout << "Bottom Left Corner" << endl;
            // neighbors are NW, NE, E
            connect(player, g, move, NW);
            connect(player, g, move, NE);
            connect(player, g, move, E);
        }
        // Are we a lower right corner tile?
        else if (i == size - 1 && j == size - 1)
        {
            cout << "Bottom Right Corner" << endl;
            // neighbors are W, NW
            connect(player, g, move, W);
            connect(player, g, move, NW);
        }
        // Are we top edge tile?
        else if (i == 0)
        {
            cout << "Top Edge Tile" << endl;
            // neighbors are W, E, SW, SE
            connect(player, g, move, E);
            connect(player, g, move, E);
            connect(player, g, move, SW);
            connect(player, g, move, SE);
        }
        // Are we a bottom edge tile
        else if (i == size - 1)
        {
            cout << "Bottom Edge Tile" << endl;
            // neighbors are W, E, NW, NE
            connect(player, g, move, W);
            connect(player, g, move, E);
            connect(player, g, move, NW);
            connect(player, g, move, NE);
        }
        // Are we a left  edge tile?
        else if (j == 0)
        {
            cout << "Left Edge Tile" << endl;
            // neighbors are NW, NE, E, SE
            connect(player, g, move, NW);
            connect(player, g, move, NE);
            connect(player, g, move, E);
            connect(player, g, move, SE);
        }
        // Are we a right edge tile?
        else if (j == size-1)
        {
            cout << "Right Edge Tile" << endl;
            // neighbors are NW, W, SW, SE
            connect(player, g, move, NW);
            connect(player, g, move, W);
            connect(player, g, move, SW);
            connect(player, g, move, SE);
        }
        // Otherwise its a center tile with all 6 degrees of freedom
        else
        {
            cout << "Middle Tile" << endl;
            // neighbors are W, NW, NE, E, SE, SW
            connect(player, g, move, W);
            connect(player, g, move, NW);
            connect(player, g, move, NE);
            connect(player, g, move, E);
            connect(player, g, move, SE);
            connect(player, g, move, SW);
        }
    }

    // saves the move
    void recordMove(int player, int move)
    {
        board[move / size][move % size] = player;

        // connect any adjacently owned tiles in the graph
        connectTiles(player, move);
    }

    friend ostream& operator<<(ostream& out, Board b)
    {
        for (int i = 0; i < b.size; i++)
        {
            // each line is indented a little further than the last
            for (int j = 0; j < 2 * i; j++)
            {
                out << " ";
            }

            // display the cells and their connections
            for (int j = 0; j < b.size; j++)
            {
                out << b.board[i][j];
                if (j != b.size - 1)
                {
                    out << " - ";
                }
                else
                {
                    out << endl;
                }
            }

            // connections between rows
            if (i != b.size - 1)
            {
                for (int j = 0; j < 2 * i; j++)
                {
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
    Graph* graph1;  // player 1
    Graph* graph2;  // player 2
};

#endif // _BOARD_H
