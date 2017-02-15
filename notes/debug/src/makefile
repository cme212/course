CXX := g++
CXXFLAGS := -g -O0 -std=c++14

EXE := print
EXE += debug_macro
EXE += assert_1
EXE += assert_2
EXE += pause
EXE += hello_gdb
EXE += sequence_gdb
EXE += containers_gdb

.PHONY: all
all : $(EXE)

% : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) $(EXE)
