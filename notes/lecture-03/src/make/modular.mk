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

# Target clean is not a file. Don't check its modification time, always execute
.PHONY : clean

student_service : Main.o Name.o Student.o
	g++ -Wall -Wconversion -Wextra -o student_service Main.o Student.o Name.o

Main.o : Main.cpp Student.hpp
	g++ -Wall -Wconversion -Wextra -c Main.cpp

Student.o : Student.cpp Student.hpp Name.hpp
	g++ -Wall -Wconversion -Wextra -c Student.cpp

Name.o : Name.cpp Name.hpp
	g++ -Wall -Wconversion -Wextra -c Name.cpp

clean:
	rm *.o student_service
