all: motor jogoUI bot

motor: motor.o funcoes.o 
	gcc motor.o funcoes.o -pthread -lncurses -o motor

jogoUI: jogoUI.o funcoes.o 
	gcc jogoUI.o funcoes.o -pthread -lncurses -o jogoUI

bot: bot.o
	gcc bot.o -o bot

motor.o: motor.c funcoes.h structs.h
	gcc -c motor.c

jogoUI.o: jogoUI.c funcoes.h structs.h
	gcc -c jogoUI.c

bot.o: bot.c
	gcc -c bot.c

funcoes.o: funcoes.c funcoes.h structs.h
	gcc -c funcoes.c

clean:
	rm *.o motor jogoUI bot