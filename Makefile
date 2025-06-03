# Makefile

# compiler
CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

# final exec
EXEC = CantStop

.PHONY: all clean

all: $(EXEC)

# link the object files
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# clean up the object files
clean:
	rm -f $(OBJ) $(EXEC)
