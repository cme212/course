# Simplest possible makefile
#
# Basic component of each makefile looks like this
# <target> : <dependencies>
# (tab) <rule>
#
# The (tab) charcter has special meaning in make. It denotes beginning
# of a rule.
# 

student_service : Main.cpp Name.cpp Name.hpp Student.cpp Student.hpp
	g++ -Wall -Wconversion -Wextra -o student_service Main.cpp Student.cpp Name.cpp

