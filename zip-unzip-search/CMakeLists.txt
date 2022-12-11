cmake_minimum_required(VERSION 3.22)
project(zip_unzip_search)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRCS)

add_executable(zip_unzip_search main.cpp ${SRCS})
