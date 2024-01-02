cmake_minimum_required(VERSION 3.23)
project(newWorkPOO)

set(CMAKE_CXX_STANDARD 20)

add_executable(newWorkPOO main.cpp Componente.cpp Componente.h Propriedade.cpp Propriedade.h Zona.cpp Zona.h Habitacao.cpp Habitacao.h Processador.cpp Processador.h Regra.cpp Regra.h Propriedades/Temperatura.cpp Propriedades/Temperatura.h Propriedades/Luz.cpp Propriedades/Luz.h Propriedades/Radiacao.cpp Propriedades/Radiacao.h Propriedades/Vibracao.cpp Propriedades/Vibracao.h Propriedades/Humidade.cpp Propriedades/Humidade.h Propriedades/Fumo.cpp Propriedades/Fumo.h Propriedades/Som.cpp Propriedades/Som.h Sensor.cpp Sensor.h Aparelho.cpp Aparelho.h Regras/IgualA.cpp Regras/IgualA.h Regras/MaiorQue.cpp Regras/MaiorQue.h Regras/MenorQue.cpp Regras/MenorQue.h Regras/Entre.cpp Regras/Entre.h Regras/Fora.cpp Regras/Fora.h Aparelhos/Aquecedor.cpp Aparelhos/Aquecedor.h Aparelhos/Aspersor.cpp Aparelhos/Aspersor.h Aparelhos/Refrigerador.cpp Aparelhos/Refrigerador.h Aparelhos/Lampada.cpp Aparelhos/Lampada.h Terminal.h Terminal.cpp Simulador.cpp Simulador.h)

target_link_libraries(${PROJECT_NAME} "C:/Users/Utilizador/Desktop/PDCurses-3.9/wincon/pdcurses.a")
