//============================================================================
// Name        : Trabalho1CG.cpp
// Author      : Jackson Henrique Hochscheidt
//			   		 : Kevin Mitchell Spiller
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <GL/glut.h>

//Declaracao de variaveis globais e defines

#define wMaze 75
#define hMaze 45

//double labirinto[hMaze][wMaze] ={
//		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//		{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
//		{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
//		{0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0},
//		{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
//		{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
//		{0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
//
//};
//
int labirinto[hMaze][wMaze]={
		//Linha 1
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//linha 2
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		//linha 3
		{0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
		{0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
		{0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
		//linha 4
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		//linha 5
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		//linha 6
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		//linha 7
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		//linha 8
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		//posicao inicial do boneco
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		//posicao inicial do boneco
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		//linha 9
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		//linha 10
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		//linha 11
		{0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
		{0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
		{0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
		//linha 12
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		//linha 13
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		//linha 14
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		//linha 15
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0}
};


//rotate no X -- muda objeto deitado
//rotate no Y -- muda objeto pra frente pra tras
//rotate no Z

int windowWidth  = 700;
int windowHeight = 700;
int windowPosX   = 0;
int windowPosY   = 0;
bool fullScreenMode = true;
#define X 0
#define Y 1
#define Z 2
#define CONE 2
#define TORUS 3
#define ALTURA_PAREDE 3
#define TEAPOT 4

double TAM_LEG = 1.5;	 //comprimento das pernas
double TAM_TRONCO = 1.5; //comprimeiro do tronco do boneco
double TAM_PESCOCO = 1.5; //comprimento pescoço
double angPerspective = 45;
double rotX = 0, rotY = 0, rotZ = 0;
double rotateTORUS = 0;
double rotateTEAPOT = 0;

int posRobo[3] = {22,0,0};


#define ROBO 9
//posicao inicial da camera -- vetor[3] = [x,y,z]
double camera[3] = {0,75,75};

//Função para tela cheia
void specialKeys(int key, int x, int y);

#include <GL/glut.h>
#include <stdio.h>


void reshapeWindow(GLsizei w, GLsizei h);

void draw();

void drawRobo();

void drawMaze(double w, double h);

void drawRobot();
void drawLegs();

GLUquadricObj *novaQuadrica();

GLUquadricObj *legs = novaQuadrica();

void teclado(unsigned char key, int x, int y);

//##########################//
//$$$$$$$$$$$$$$$$$$$$$$$$$$//
//			MAIN			//
//$$$$$$$$$$$$$$$$$$$$$$$$$$//
//##########################//
int main(int argc, char **argv) {

	//inicializa GLUT com parametros necessarios

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);


	//cria JANELA DE VISUALIZACAO
	glutInitWindowPosition(windowPosX,windowPosY);
	glutInitWindowSize(windowWidth,windowHeight);
	glutCreateWindow("Labirinto 3D");

	//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//
	//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//
	//$$$$$$$$$$$$$$$$$$$ LIMPAR TELA $$$$$$$$$$$$$$$$$$$//
	//$$$$$$$$# HABILITAR TESTE DE PROFUNDIDADE $$$$$#$$$//
	//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//
	//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//
	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//FUNCOES DE CALLBACK
	glutReshapeFunc(reshapeWindow);
	glutDisplayFunc(draw);
	glutSpecialFunc(specialKeys);
	glutFullScreen();
	glutKeyboardFunc(teclado);

	for(int i = 0; i < hMaze; i++){
		for(int j = 0; j < wMaze; j++){
			printf("%d", labirinto[i][j]);
		}
		printf("\n");
	}

	glutMainLoop();
}

void reshapeWindow(GLsizei w, GLsizei h){
	if(h ==0) h = 1;
	glViewport(0,0,w,h);
	//alteracoes serao feitas na matriz de projecao
	glMatrixMode(GL_PROJECTION);
	//carrega matriz identidade
	glLoadIdentity();
	gluPerspective(45, w/h, 0.1, 300);
}

void draw(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gluLookAt(camera[X],camera[Y], camera[Z], 0,0,0, 0,1,0);

	glColor3f(0.5,0.75,0.25);

	glRotatef(rotX, 1,0,0);
	glRotatef(rotY, 0,1,0);
	glRotatef(rotZ, 0,0,1);

	//CHAO
	glRotatef(-90,1,0,0);
	glTranslatef(-20,-20,0);// para colocar o labirinto mais no centro da dela
	glBegin(GL_QUADS);
		glVertex3f(0,0,0);
		glVertex3f(hMaze,0,0);
		glVertex3f(hMaze,wMaze,0);
		glVertex3f(0,wMaze,0);
	glEnd();

	//LABIRINTO
	glColor3f(1,0,0);
	drawMaze(wMaze, hMaze);
	drawRobot();


	glFlush();
	glutSwapBuffers();

	glutPostRedisplay();
}

GLUquadricObj *novaQuadrica(){
	GLUquadricObj *novaQuadrica = gluNewQuadric();
	gluQuadricDrawStyle(novaQuadrica, GLU_FILL);
	gluQuadricOrientation(novaQuadrica, GLU_OUTSIDE);
	gluQuadricNormals(novaQuadrica, GLU_SMOOTH);
	return novaQuadrica;
}

void teclado(unsigned char key, int x, int y){
	switch(key){
		case 'q':
			exit(0);
			break;
		case 'Q':
			exit(0);
			break;
		case '8': // rotaciona -X
			rotX--;
			break;
		case '2': //rotaciona X
			rotX++;
			break;
		case '4': //rotaciona Z
			rotZ++;
			break;
		case '6': //rotaciona -Z
			rotZ--;
			break;
		case '7': //rotaciona -Y
			rotY--;
			break;
		case '9': //rotaciona Y
			rotY++;
			break;
		case '-': //zoom in
			camera[Y]--;
			break;
		case '+': //zoom out
			camera[Y]++;

	}
	glutPostRedisplay();
}

//Função para tela cheia
void specialKeys(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_F1:    // F1: Para trocar entre tela cheia e janela
			fullScreenMode = !fullScreenMode;         // Estado de troca
			if (fullScreenMode) {                     // Modo tela cheia
				windowPosX   = glutGet(GLUT_WINDOW_X); // Salva os parametros para retornar mais tarde
				windowPosY   = glutGet(GLUT_WINDOW_Y);
				windowWidth  = glutGet(GLUT_WINDOW_WIDTH);
				windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
				glutFullScreen();                      // Muda para tela cheia
			}else{                                         // Modo janela
				glutReshapeWindow(windowWidth, windowHeight); // Troca para modo janela
				glutPositionWindow(windowPosX, windowPosX);   // Posição do topo canto esquerdo
			}
			break;
		case GLUT_KEY_DOWN: //anda pra baixo no mapa
			if(posRobo[X]+2 <= hMaze)
				if(labirinto[posRobo[X]+2][posRobo[Y]] == 1)
					if(labirinto[posRobo[X]+2][posRobo[Y]-1] == 1 && labirinto[posRobo[X]+2][posRobo[Y]+1] == 1 )
						posRobo[X]++;
			break;
		case GLUT_KEY_UP: //anda pra cima no mapa
			if(posRobo[X]-2 >=0)
				if(labirinto[posRobo[X]-2][posRobo[Y]] == 1)
					if(labirinto[posRobo[X]-2][posRobo[Y]-1] == 1 && labirinto[posRobo[X]-2][posRobo[Y]+1] == 1)
						posRobo[X]--;
			break;
		case GLUT_KEY_LEFT: //anda pra esquerda no mapa
			if(posRobo[Y]-2 >= 0)
				if(labirinto[posRobo[X]][posRobo[Y]-2] == 1)
					if(labirinto[posRobo[X]+1][posRobo[Y]-2] == 1 && labirinto[posRobo[X]-1][posRobo[Y]-2] == 1)
						posRobo[Y]--;
			break;
		case GLUT_KEY_RIGHT: //anda pra direita no mapa
			//se tiver mais duas posicoes pra direita no mapa
			if(posRobo[Y]+2 < wMaze)
				if(labirinto[posRobo[X]][posRobo[Y]+2] == 1)
					if(labirinto[posRobo[X]+1][posRobo[Y]+2] == 1 && labirinto[posRobo[X]-1][posRobo[Y]+2] == 1)
						posRobo[Y]++;
			break;
	}
	glutPostRedisplay();
}

void drawMaze( double w, double h){
	glPushMatrix();
	glTranslatef(0,0,1.5);
	//para cada linha da matriz do labirinto
	for(int i = 0; i < h; i++){
		//para cada coluna da matriz do labirinto
		for(int j = 0; j < w; j++){
			//se posicao do labirinto for uma parede
			if(labirinto[i][j] == 0){
				//desenhar parede
				glPushMatrix();
					glColor3f(1,0,0);
					glScalef(1,1,ALTURA_PAREDE);
					glTranslatef(i,j,0);
					glutSolidCube(1);
				glPopMatrix();
			}else if(labirinto[i][j] == CONE){
				glPushMatrix();
					glColor3f(1,0.6,0.5);
					glTranslatef(i,j,-1.5);
					glutSolidCone(1,ALTURA_PAREDE,50,50);
				glPopMatrix();
			}else if(labirinto[i][j] == TORUS){
				glPushMatrix();
					glColor3f(1,1,0);
					glTranslatef(i,j,0);
					glRotatef(90,0,1,0);
					glRotatef(rotateTORUS++,1,0,0);
					glutSolidTorus(0.3, 0.7,50,50);
				glPopMatrix();
			}else if(labirinto[i][j] == TEAPOT){
				glPushMatrix();
					glColor3f(0.2,0.2,0.2);
					glTranslatef(i,j,0);
					glRotatef(90,1,0,0);
					glRotatef(rotateTEAPOT++,0,1,0);
					glutSolidTeapot(0.75);
				glPopMatrix();
			}
		}
	}
	glPopMatrix();
};

void drawRobot(){
//	printf("X=%d, Y=%d, Z=%d\n",posRobo[X],posRobo[Y],posRobo[Z]);

	//Pernas
	glColor3f(0.1f,0.2f,0.3f);
	glPushMatrix();
		glTranslatef(posRobo[X]-0.4, posRobo[Y],posRobo[Z]);
		gluCylinder(legs,0.3,0.3,TAM_LEG,10,10);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(posRobo[X]+0.4, posRobo[Y], posRobo[Z]);
		gluCylinder(legs,0.3,0.3,TAM_LEG,10,10);
	glPopMatrix();

	//TRONCO
	glColor3f(0.2f,0.3f,0.4f);
	glPushMatrix();
		glTranslatef(posRobo[X],posRobo[Y],posRobo[Z]+TAM_LEG+TAM_TRONCO);
		glScalef(1,1,TAM_TRONCO);
		glutSolidCube(2);
	glPopMatrix();


	//"OMBROS
	glColor3f(0.5f,0.5f,0.5f);
	glPushMatrix();
		glTranslatef(posRobo[X]+1,posRobo[Y],posRobo[Z]+TAM_LEG+(TAM_TRONCO*2));
		glutSolidCube(0.5);
	glPopMatrix();

	//PESCOÇO
	glColor3f(0.5f,0.6f,0.7f);
	glPushMatrix();
		glTranslatef(posRobo[X],posRobo[Y],posRobo[Z]+TAM_LEG+(TAM_TRONCO*2)+(TAM_PESCOCO/2));
		glRotatef(180,0,1,0);
		glutSolidCone(1,TAM_PESCOCO, 50,50);
	glPopMatrix();


//	glutPostRedisplay();
};

void drawLegs(){
	glColor3f(0.7f,0.7f,0.7f);
//	glTranslatef(posRobo[X], posRobo[Y],posRobo[Z]);
	gluCylinder(legs,0.3,0.3,2,10,10);
	//glTranslatef(posRobo[X]+1,posRobo[Y],posRobo[Z]);

}
