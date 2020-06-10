cmake_minimum_required(VERSION 3.16)
project(Labo_6_indexation C)

set(CMAKE_C_STANDARD 11)

add_executable(Labo_6_indexation main.c book_index.h heading.h list.h list.c heading.c book_index.c)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wconversion -Wextra -pedantic --coverage")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -O1 -fno-omit-frame-pointer detect_leaks=1 -g")