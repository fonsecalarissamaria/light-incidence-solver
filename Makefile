CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SRC = $(shell find src -name "*.cpp")
OBJ = $(SRC:.cpp=.o)

all: luminosidade

luminosidade: $(OBJ)
	$(CXX) $(CXXFLAGS) -o luminosidade $(OBJ)

clean:
	rm -f $(OBJ) luminosidade
