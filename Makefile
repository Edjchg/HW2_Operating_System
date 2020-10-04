.PHONY: clean
CC = gcc
APP = analizador2
SRC = $(APP).c
FLAGS = -Wall
$(APP) : $(SRC)
		$(CC) -o $(APP) $(FLAGS) $(SRC)
 
clean: 
		rm $(APP)
