cmake_minimum_required(VERSION 3.10)

project(zip-search)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRCS)

add_executable(zip-search main.cpp ${SRCS} main.cpp)