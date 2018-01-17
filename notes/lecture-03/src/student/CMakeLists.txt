# CMake configuration file

cmake_minimum_required (VERSION 3.0)
project (StudentMatters)

# Create a list of source files to be compiled
set(SRC
  Student.cpp
  Main.cpp
)

include_directories(./include)

# Build Name class in a separate library
add_library(Name Name.cpp)

# Compile the executable
add_executable(student_service ${SRC})
# Link to the Name library
target_link_libraries(student_service Name)
