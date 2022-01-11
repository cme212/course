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
# To write makefile in a more compact form use special macros
#
# $@ - name of the target
# $< - name of the first dependency
# $? - names of all dependencies newer than the target
# $^ - names of all dependencies with duplicates removed
# $+ - names of all dependencies

CXX = g++
CXXFLAGS = -Wall -Wconversion -Wextra # -g -O0
OBJS = Main.o Name.o Student.o
RM = rm

student_service : $(OBJS)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $^

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Specify dependencies
Main.o    : Student.hpp
Student.o : Student.hpp Name.hpp
Name.o    : Name.hpp

clean:  # "-" in front of $(RM) ensures no error returned if files don't exist
	-$(RM) *.o student_service
