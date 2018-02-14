
CXX = g++
CXXFLAGS = -Wall -Wconversion -Wextra -pedantic -std=c++11
SRC = myfunction.cpp mymain.cpp
HEADERS = myheader.hpp

inline: $(SRC) $(HEADERS)
	$(CXX) -o $@ $(SRC)

.PHONY: clean

clean:
	-rm inline
