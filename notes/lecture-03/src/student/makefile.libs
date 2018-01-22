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
OBJS = Main.o Student.o
LIBOBJS = Name.o
RM = rm
MV = mv
LIB_DIR = -L./lib
INCLUDE_DIR = -I./include
LIB = -lName
INSTALL_DIR = ./bin
LIB_INSTALL_DIR = ./lib

.PHONY: install clean

student_service : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LIB_DIR) $(LIB)

install : student_service
	-$(MV) student_service  $(INSTALL_DIR)

clean:  # "-" in front of $(RM) ensures no error returned if files don't exist
	-$(RM) *.o $(INSTALL_DIR)/student_service

## This would typically be built elsewhere
.PHONY: install_lib namelib clean_lib

namelib: libName.so libName.a

libName.so : $(LIBOBJS)   # Shared library is built using flag -shared
	$(CXX) $(CXXFLAGS) -shared -o $@ $^

libName.a : Name.o    # Static library is an archive of object files
	ar rvs $@ $^

install_lib: namelib
	-$(MV) libName.so $(LIB_INSTALL_DIR)
	-$(MV) libName.a  $(LIB_INSTALL_DIR)

clean_lib: 
	-$(RM) $(LIB_INSTALL_DIR)/*.a $(LIB_INSTALL_DIR)/*.so
## End of library builds

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -c $<

# Specify dependencies
Main.o    : Student.hpp
Student.o : Student.hpp Name.hpp
Name.o    : Name.hpp
