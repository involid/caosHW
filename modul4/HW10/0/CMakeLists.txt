cmake_minimum_required(VERSION 3.2)

project(simplefs)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FUSE REQUIRED fuse3)

link_libraries(${FUSE_LIBRARIES})         # -lfuse3 -lpthread
include_directories(${FUSE_INCLUDE_DIRS}) # -I/usr/include/fuse3

set(SOURCES inf-II-10-0.c)

add_executable(simplefs ${SOURCES})

