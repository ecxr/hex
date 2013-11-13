CC=g++
CPPFLAGS= -Wall -g -std=c++0x
INC= -I../graph2

SRC= main.cpp player.cpp hex.cpp board.cpp

OBJ=$(SRC:.cpp=.o)

prog: $(OBJ) $(HDR)
	$(CC) -o hex $(CPPFLAGS) $^ && ./hex

%.o: %.cpp $(HDR)
	$(CC) -c -o $@ $< $(CPPFLAGS)

.PHONY: clean

clean:
	rm -f *.o hex
