cmake_minimum_required(VERSION 3.2)

project(experimeeent)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FUSE REQUIRED fuse3)
pkg_check_modules(LIBZIP REQUIRED libzip)

link_libraries(${FUSE_LIBRARIES})         # -lfuse3 -lpthread
include_directories(${FUSE_INCLUDE_DIRS}) # -I/usr/include/fuse3

link_libraries(${LIBZIP_LIBRARIES})
include_directories(${LIBZIP_INCLUDE_DIRS})

set(SOURCES exper.c)

add_executable(exper ${SOURCES})
