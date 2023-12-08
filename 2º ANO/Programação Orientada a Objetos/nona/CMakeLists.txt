cmake_minimum_required(VERSION 3.23)
project(nona)

set(CMAKE_CXX_STANDARD 20)

add_executable(nona main.cpp Imovel.cpp Imovel.h Imobiliaria.cpp Imobiliaria.h Loja.cpp Loja.h Apartamento.cpp Apartamento.h RegistoPredial.cpp RegistoPredial.h)
