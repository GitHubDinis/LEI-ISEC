cmake_minimum_required(VERSION 3.23)
project(quinta)

set(CMAKE_CXX_STANDARD 20)

add_executable(quinta main.cpp Pessoa.cpp Pessoa.h RegistoCivil.cpp RegistoCivil.h)
