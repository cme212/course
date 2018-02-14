
CXX = g++
CXXFLAGS = -Wall -Wconversion -Wextra -pedantic -std=c++11
SRC = usings.cpp
EXE = usings

$(EXE): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

.PHONY: clean

clean:
	-rm $(EXE)
