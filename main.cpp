#include <iostream>

#include "hex.cpp"

int main(int argc, char* argv[])
{
  cout << "Starting hex game" << endl;
  Hex hex;
  hex.runMatch();

  cout << "testing board initialization and print" << endl;
  Board b(7);
  cout << b << endl;
  return 0;
}
