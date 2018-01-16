# CMake configuration file

cmake_minimum_required (VERSION 3.0)
project (StudentMatters)

set(SRC
  Name.cpp
  Student.cpp
  Main.cpp
)

add_executable(student_service ${SRC})
