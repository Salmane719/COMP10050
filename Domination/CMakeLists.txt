cmake_minimum_required(VERSION 3.15)
project(Domination C)

set(CMAKE_C_STANDARD 11)

add_executable(Domination main.c Struct_Definitions.h Linked_List.h Linked_List.c SetBoard.h SetBoard.c Turn.c Turn.h)