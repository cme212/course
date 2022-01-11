
CXX = g++
CXXFLAGS = -Wall -Wconversion -Wextra -pedantic -std=c++11
SRC = myfunction.cpp mymain.cpp
HEADERS = myheader.hpp
EXE = inline

$(EXE): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

.PHONY: clean

clean:
	-rm $(EXE)
