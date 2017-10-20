#Para escrever comentários ##
############################# Makefile ##########################
#Definimos a variável
SRC=src/Trabalho1CG.cpp
all: src/Trabalho1CG
Trabalho1CG: src/Trabalho1CG.o
	g++ -o src/Trabalho1CG src/Trabalho1CG.o -lm -lglut -lGL -lGLU
#-----> Distancia com o botao TAB ### e nao com espaços
Trabalho1CG.o: src/Trabalho1CG.cpp
	g++ -o src/Trabalho1CG.o -c src/Trabalho1CG.cpp -lm -lglut -lGL -lGLU -W -Wall -ansi -pedantic
#
#Coloquei $(SRC) em todos os lugares aonde estava main.c
Trabalho1CG.o: $(SRC)

clean:
	rm -rf *.o
mrproper: clean
	rm -rf src/Trabalho1CG
