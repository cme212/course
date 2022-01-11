# Simplest possible makefile
#
# Basic component of each makefile looks like this
# <target> : <dependencies>
# (tab) <rule>
#
# The (tab) charcter has special meaning in make. It denotes beginning
# of a rule.
# 
# Break compilation to separate objects. The first rule is executed first.
# Then, make looks for rules to build the dependencies, starting from the
# next rule down. 
#
# Use variables to be able to edit makefile easier.
# The operator $() replaces variable within parenthesis with its assigned
# value. If the variable is not defined, an empty string is replaced.
# The operator $ treats the next character as a variable.
#

CXX = g++
CXXFLAGS = -Wall -Wconversion -Wextra # -g -O0
OBJS = Main.o Name.o Student.o
RM = rm

# Phony describes targets that are not files; interprets them always out of date
.PHONY: clean

student_service : $(OBJS)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o student_service $(OBJS)

Main.o : Main.cpp
	$(CXX) $(CXXFLAGS) -c Main.cpp

Student.o : Student.cpp Student.hpp
	$(CXX) $(CXXFLAGS) -c Student.cpp

Name.o : Name.cpp Name.hpp
	$(CXX) $(CXXFLAGS) -c Name.cpp

clean:  # "-" in front of $(RM) ensures no error returned if files don't exist
	-$(RM) *.o student_service
