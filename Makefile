CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`

SRC = chip8.cpp platform.cpp
OUT = chip8_app

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT)

