#include <iostream>

#include "hex.cpp"

bool test_board()
{
    cout << "testing board initialization and print" << endl;
    Board b(7);
    cout << b << endl;
    return true;
}

bool run_game(int size)
{
    cout << "Starting hex game" << endl;
    Hex hex(size);
    int winner = hex.runMatch();
    cout << "Player " << winner << " wins!" << endl;

    return true;
}
int main(int argc, char* argv[])
{
    test_board();
    run_game(4);
}
