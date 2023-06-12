cmake_minimum_required(VERSION 3.23)
project(workP C)

set(CMAKE_C_STANDARD 99)

add_executable(workP main.c paragem.h paragem.c utils.h linha.c linha.h)
