cmake_minimum_required(VERSION 3.23)
project(work)

set(CMAKE_CXX_STANDARD 17)

add_executable(work main.cpp animais.h animais.cpp alimentos.h alimentos.cpp interface.h interface.cpp reserva.h "reserva.cpp")

target_link_libraries(${PROJECT_NAME} C:/Users/Utilizador/PDCurses-3.9/wincon/pdcurses.a)