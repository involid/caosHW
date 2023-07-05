cmake_minimum_required(VERSION 3.2)
project(pymatrixdot)

set(CMAKE_C_STANDARD 11)

find_package(PythonLibs REQUIRED)

include_directories(${PYTHON_INCLUDE_DIRS})

python_add_module(matrix inf-II-12-0.c)
