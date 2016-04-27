cmake_minimum_required(VERSION 3.5)
project(iacnt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES
		src/main.c++
		src/typedefs.h++
		src/option.c++
		src/option.h++
		src/readopts.c++
		src/readopts.h++)

add_executable(iacnt ${SOURCE_FILES})