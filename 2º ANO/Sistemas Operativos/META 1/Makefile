# This is Makefile

all:
	gcc -o all frontend frontend.c 
	gcc -o all backend backend.c users_lib.o

frontend:
	gcc -o frontend frontend.c
	
backend:
	gcc -o backend backend.c users_lib.o
	
clean:
	rm all
	rm *.o
