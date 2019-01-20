# CME 212: Lecture 03

## Make

As your code becomes more complex, you will need to pay more attention
to organizing code compilation. Make is a tool that will help you
organize and automate code build, installation, and even testing.
Make can be used with practically any compiler or programming
language. We will explain basics of Make, using simple C++
code as the testcase. The test code consists of following files:

* [`Student.cpp`](src/student/Student.cpp)
* [`Student.hpp`](src/student/Student.hpp)
* [`Name.cpp`](src/student/Name.cpp)
* [`Name.hpp`](src/student/Name.hpp)
* [`Main.cpp`](src/student/Main.cpp)

It creates an instance of the `Student` class, and then prints
student's name and ID number. We can build this code with a single
command line instruction like this:
```
g++ Main.cpp Student.cpp Name.cpp
```
Instead of typing this instruction every time we need to build
the code, we can save this compilation instruction in a file, and
then use `make` tool to execute it. The make tool will look for
files named `Makefile` or `makefile` in the same directory where
the make comand is invoked. If you store your build instructions
in a different file, you can use flag `-f` to tell make where
to look, for example:
```
make -f myMakeFile.mk
```
The build instructions in the makefile are written in the following
format:
```make
target ... : dependencies ...
       rule
       ...
```
The target is the object to be created or action to
be taken. The dependencies are the list of targets that
need to be up-to-date in order for the rule to be executed.
The rule is a set of shell commands that will generate the target.
Each line of the rule must be indented with a tab character.
To build our code, we create a simple `Makefile` like this:
```make
# Single rule makefile
student_service : Main.cpp Name.cpp Name.hpp Student.cpp Student.hpp
    g++ -Wall -Wconversion -Wextra -o student_service Main.cpp Student.cpp Name.cpp
```
Here `student_service` is the build target. The dependencies in this case
are the all source files. On the next
line, indented with the tab, is the rule to build the target.
The character `#` denotes comments in the makefile.
Everything between `#` and the end of line is ignored. 
The `make` tool will look for files `Makefile`
or `makefile` in the directory where it is executed.

The `make` tool will check if the modification time of the
target is older than any of its dependencies, and if so,
it will rebuild the target. In this case, if any of the
source files is touched, the binary `student_service`
will be recompiled.

### Step-by-step builds ###

It is obvious that our 2-line `Makefile` is not a
practical for building large codes with of hundreds of files.
If any of the files is modified, the entire source code will have
to be recompiled. Long build times can add significant overhead to
the software development. To avoid this, we can compile
each source file into a binary object first, and then link all
objects into an executable. That way, if we change a single file,
we will need to recompile only that file, and then link all objects again.
The flag `-c` will tell compiler to generate the binary object, but not
link it. We rewrite our `Makefile` in a more modular fashion:

```make
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
```
Here we build main body of the code and classes `Student` and `Name`
as separate binary objects, and then link them into a single
executable `student_service`. The make utility will read
entries from top to bottom. It will execute the rule, if all
the dependencies exist. Otherwise, it will look down the list for
the rules to build dependencies.
Individual targets will be rebuilt only if their dependencies change.
The make utility will check if the target date stamp is older
than the date stamps of its dependencies. If so, the target will
be deemed out-of-date and rebuilt. Otherwise, it will be reused.
```sh
$ make -f modular.mk 
g++ -Wall -Wconversion -Wextra -c Main.cpp
g++ -Wall -Wconversion -Wextra -c Name.cpp
g++ -Wall -Wconversion -Wextra -c Student.cpp
g++ -Wall -Wconversion -Wextra -o student_service Main.o Student.o Name.o
$ touch Main.cpp
Geronimos-Air:student peles$ make -f modular.mk 
g++ -Wall -Wconversion -Wextra -c Main.cpp
g++ -Wall -Wconversion -Wextra -o student_service Main.o Student.o Name.o
$
```
The makefile above will ensure only parts of the code that
are modified will be rebuilt. However, this makefile is
difficult to edit and bug prone. Imagine we need to add
debugging compile flags. We would need to modify rules
for all object and executable file targets.

### Defining variables for `make` ###

Using variables helps create makefiles that are easier to
modify and maintan. We can rewrite our example like this:
```make
CXX = g++
CXXFLAGS = -Wall -Wconversion -Wextra # -g -O0
OBJS = Main.o Name.o Student.o
RM = rm

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
```
The operator `$( )` will replace the variable name with the variable
value. Now, can now add debugging symbols by modifying only one line
in the makefile.


### Phony targets ###

Note that the target `clean` is different from other targets
in our example. Making `clean` will not create a new file, but
will instead invoke shell command to remove all binary files.
Targets like this are called phony targets. The dependency
```make
.PHONY : clean
```
will tell the make utility that `clean` is not
a file. Otherwise, if there is a file named `clean` in the
build directory, the make utility would consider `clean`
to be up-to-date and would not execute the shell command
in the rule. In other words, using `.PHONY` will ensure the
make utility sees `clean` target as always out-of-date.


### Patterns and special macros ###

There are quite a few tricks you can use to make your
makefiles more compact and easier to edit. For example,
building object files in the previous example seems a bit
repetitive. We can rewrite those lines like
```make
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $<
```
This stanza says for any source file with extension `.cpp` build
an object file with the same name and extension `.o`. Special
macro `$<` returns the first dependency from the list (in this
case there is only one dependency). 
We can specify all additional dependencies separately elsewhere
in the makefile:
```make
Main.o    : Student.hpp
Student.o : Student.hpp Name.hpp
Name.o    : Name.hpp
```
The output file name in the linking stanza can be replaced
with the special macro `$@`, which will insert the target
name. The special macro `$^` inserts all the target dependencies
in the rule. The modified linking stanza then looks like this:
```make
student_service : $(OBJS)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $^
```
This way, almost all the repetitive code has been eliminated from the
makefile (see file [`macros.mk`](src/student/macros.mk)). Here
is a short list of helpful special macros:

* `$@` - name of the target
* `$<` - name of the first dependency
* `$?` - names of all dependencies newer than the target
* `$^` - names of all dependencies with duplicates removed
* `$+` - names of all dependencies

### Building libraries ###

When you have code that is used by multiple applications,
it is good idea to compile it as a library. That way,
you build the shared code once, and then link to it 
when building different applications. There are two ways to
link to a library:

* Static linking will link the library together with other
object files into a single binary executable.
* Dynamic linking will make the executable "aware" of the
library. The executable will (try to) load the library and
link to it at runtime.

Let us assume we want to build class `Name` as a library.
To build a static library one simply needs to make an archive
of all object files that make up the library:
```make
libName.a : Name.o
	ar rvs $@ $^
```
The rule uses `ar` tool to package all dependencies into
file libName.a. Flag `r` tells `ar` utilities to add (or replace)
files to the archive, `v` enables verbose mode, and `s`
ensures the object file index is written into the archive.
By convention, static libraries have file extension `.a`
(stands for "archive").

Shared libraries are built in a similar way as executables, but with
an additional flag `-shared`:
```make
libName.so : Name.o
	$(CXX) $(CXXFLAGS) -shared -o $@ $^
```
When building shared libraries, all object files
must be compiled with `-fPIC` flag (PIC stands for position
independent code). This will ensure the executable will work correctly
regardless of the order in which shared libraries are loaded.
By convention, shared libraries have file extension `.so`
(stands for "shared object"). Also by convention, both static
and shared library names start with `lib`.

Take a look at the example [Makefile](src/make_lib/src/libName/Makefile)
that builds library `Name`.


### Linking to libraries ###

Now that we built and installed our library Name,
we can link to it during the compilation. On the link
line, we have to provide path to the directory where
the library is stored and the name of the library. The
linking stanza for the executable in our example
looks like this:
```make
student_service : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -L/opt/lib -lName
```
Flag `-L` tells linker where to look for the library, and
the flag `-l` tells the linker which library to link.
Note that the library name following the `-l` flag is used
without prefix `lib` and without the file extension (`.so` or `.a`).
By default, linker will try to link to a shared library.
If we want to link to a static library, we need to specify that
explicitly by adding flag `-static` to the linking command.

Header files for the library may not be present on the
compiler default search path, so we need to specify explicitly
the location of header files. We can do that by adding `-I` flag
on the compiler flags, for example: `-I/opt/include`.

Take a look at the example in file [`make`](src/make_lib/src/appStudent/Makefile).
We can first create and install static and shared libraries Name:
```sh
$ make -f libs.mk install_lib
g++ -Wall -Wconversion -Wextra -fPIC  -shared -o libName.so Name.o
ar rvs libName.a Name.o
ar: creating archive libName.a
a - Name.o
mv libName.so ./lib
mv libName.a  ./lib
```
Then, we can build the executable `student_service`, which links
to the library Name.
```sh
$ make -f makefile.libs
g++ -Wall -Wconversion -Wextra -fPIC  -I./include -c Main.cpp
g++ -Wall -Wconversion -Wextra -fPIC  -I./include -c Student.cpp
g++ -Wall -Wconversion -Wextra -fPIC  -o student_service Main.o Student.o -L./lib -lName
```

### Further reading ###

[GNU make Manual](https://www.gnu.org/software/make/manual/html_node/index.html)
