cmake_minimum_required(VERSION 3.2)

project(http2_GET)

find_package(CURL REQUIRED)

set(SOURCES problem2.c)

add_executable(problem2 ${SOURCES})

target_include_directories(problem2 PUBLIC ${CURL_INCLUDE_DIRECTORIES})

target_link_libraries(problem2 ${CURL_LIBRARIES})
