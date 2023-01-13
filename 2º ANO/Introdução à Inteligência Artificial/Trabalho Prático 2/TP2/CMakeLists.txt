cmake_minimum_required(VERSION 3.23)
project(TP2 C)

set(CMAKE_C_STANDARD 11)

include_directories(CodigoTrepaColinas)
include_directories(Evolutivo)
include_directories(Hibrido)

add_executable(TP2
        #[[CodigoTrepaColinas/algoritmo.c
        CodigoTrepaColinas/algoritmo.h
        CodigoTrepaColinas/funcao.c
        CodigoTrepaColinas/funcao.h
        CodigoTrepaColinas/main.c
        CodigoTrepaColinas/utils.c
        CodigoTrepaColinas/utils.h]]
        Evolutivo/algoritmo.c
        Evolutivo/algoritmo.h
        Evolutivo/funcao.c
        Evolutivo/funcao.h
        Evolutivo/main.c
        Evolutivo/utils.c
        Evolutivo/utils.h
        #[[Hibrido/algoritmo.c
        Hibrido/algoritmo.h
        Hibrido/funcao.c
        Hibrido/funcao.h
        Hibrido/main.c
        Hibrido/utils.c
        Hibrido/utils.h]])
