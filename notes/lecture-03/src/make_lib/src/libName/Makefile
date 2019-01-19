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
#
# Link to external libraries using flags -L$(LIB_PATH) -l$(LIB)
# -L sets path to where is the library, and -l links to the library
#
# -I specifies a path where to look for header files
#
# -fPIC stands for Position Independent Code; required for shared libs
#
# When running code environment variable PATH must include INSALL_DIR,
# and environment variable LD_LIBRARY_PATH must include LIB_DIR.
# On Mac dynamic library path is DYLD_LIBRARY_PATH
#

CXX = g++
CXXFLAGS = -Wall -Wconversion -Wextra -fPIC # -g -O0
OBJS = Name.o
RM = -rm
MV = -mv
CP = -cp
LIBNAME = libName


ROOT=$(shell pwd)
INCLUDE_DIR = $(ROOT)/../../include
INSTALL_DIR = $(ROOT)/../../lib
LDFLAGS = -dynamiclib -install_name $(INSTALL_DIR)/$(LIBNAME).so


all: libName.so libName.a

$(LIBNAME).so : $(OBJS)  # Shared library is built using flag -shared
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

$(LIBNAME).a : $(OBJS)   # Static library is an archive of object files
	ar rvs $@ $^

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $<

install: all
	$(MV) $(LIBNAME).so $(INSTALL_DIR)
	$(MV) $(LIBNAME).a  $(INSTALL_DIR)
	$(CP) Name.hpp $(INCLUDE_DIR)

clean: 
	$(RM) *.o $(LIBNAME).so $(LIBNAME).a

uninstall:
	$(RM) $(INSTALL_DIR)/$(LIBNAME).a
	$(RM) $(INSTALL_DIR)/$(LIBNAME).so
	$(RM) $(INCLUDE_DIR)/Name.hpp

# Specify dependencies
Name.o    : Name.hpp

# Specify phony targets
.PHONY: uninstall clean


