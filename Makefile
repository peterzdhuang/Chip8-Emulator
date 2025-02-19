CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`

SRC = main.cpp
OUT = chip8

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT)
