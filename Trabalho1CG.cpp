//============================================================================
// Name			: Trabalho1CG.cpp
// Author		: Jackson Henrique Hochscheidt
//			   	: Kevin Mitchell Spiller
// CCR			: Computação Gráfica - 2017.2 - Noturno
//============================================================================

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>


#define wMaze 75
#define hMaze 45
#define X 0
#define Y 1
#define Z 2
#define PAREDE 0
#define MESA 2
#define TORUS 3
#define OBJS 5
#define ALTURA_PAREDE 10
#define TEAPOT 4
#define CAM_PADRAO 2
#define CAM_ROBO 3
#define CAM_MESA_CENTRO 4
#define CAM_TEAPOT 5
#define FRENTE 1
#define TRAS 2
#define ESQUERDA 3
#define DIREITA 4
#define CHAO 1
#define ESCALA 0.5


GLfloat mat_shininess[] = { 50.0 };
GLfloat light_position[] = { 0, 1000.0, 0, 1.0 };
GLfloat light_position2[] = {2100, 1000.0, 2100, 1.0 };
GLfloat luzDifusa[4] = { 0.7,0.7,0.7,1.0 };	   // "cor"
GLfloat luzEspecular[4] = { 0.7,0.7,0.7,1.0 };
GLfloat lmodel_ambient[] = {1,1,1,1.0};


GLuint chaoid,paredeid;



int labirinto[hMaze][wMaze]={
		//Linha 1
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//linha 2
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,0,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,0,0,0,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		//linha 3
		{0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
		{0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
		{0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
		//linha 4
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,0,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		//linha 5
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,3,1,0,0,0,0,0,0,0,0,0,0,0,0,1,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,1,0,0,0,0,0,0,0,0,0,0,0,0,1,3,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		//linha 6
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,0,1,1,1,1,3,1,1,1,1,1,1,1,0,0,0,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,0,0,0,1,1,1,1,1,1,1,3,1,1,1,1,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		//linha 7
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,9,9,9,9,9,9,9,9,1,1,1,9,9,9,9,9,9,9,9,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,9,9,9,9,9,9,9,9,1,1,1,9,9,9,9,9,9,9,9,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		//linha 8
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,9,9,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,9,9,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		//posicao inicial do boneco
		{1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,3,1,0,0,0,1,1,1,0,9,9,1,3,1,1,1,1,1,2,1,1,1,1,1,3,1,9,9,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		//posicao inicial do boneco
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,9,9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9,9,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		//linha 9
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,5,1,0,0,0,0,0,0,0,0,0,1,3,1,0,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,0,1,3,1,0,0,0,0,0,0,0,0,0,1,3,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		//linha 10
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,0,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		//linha 11
		{0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
		{0,0,0,1,3,1,0,0,0,0,0,0,0,0,0,0,0,0,1,3,1,0,0,0,1,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,1,0,0,0,1,3,1,0,0,0,0,0,0,0,0,0,0,0,0,1,3,1,0,0,0},
		{0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
		//linha 12
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,0,1,3,1,1,1,1,1,1,1,1,3,1,0,0,0,1,1,1,0,0,0,1,3,1,1,1,1,1,1,1,1,3,1,0,0,0,1,3,1,1,1,1,1,1,1,1,3,1,0,0,0,1,1,1,0,0,0,1,3,1,1,1,1,1,1,1,1,3,1,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		//linha 13
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		//linha 14
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,0,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,0,0,0,1,3,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,4,1,1,1,1,1,1,1,1,1,1,1,3,1,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		//linha 15
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0}
};




int windowWidth  = 700;
int windowHeight = 700;
int windowPosX   = 0;
int windowPosY   = 0;
bool fullScreenMode = true;
//double TAM_LEG = 1.5;	 //comprimento das pernas
//double TAM_TRONCO = 1.5; //comprimeiro do tronco do boneco
//double TAM_PESCOCO = 1.5; //comprimento pescoço
double angPerspective = 45;
//double rotX = 0, rotY = 0, rotZ = 0;
double rotateTORUS = 0;
double rotateTEAPOT = 0;
double rotateCUBE = 0;
int lastMotion = -1;
double angleRotateRobot = 0;
double rotateRobot = 0;
double rotateArms = 0;
double rotateHead = 0;
int CAM_ATUAL = CAM_PADRAO;
bool ROT_ARM_FRONT = true;
bool ROT_HEAD_RIGHT = true;
int posRobo[3] = {22,0,0};
double camera[3] = {hMaze/2,wMaze/2,100};
double focus[3] = {hMaze/2,wMaze/2,0}; // para onde a camera esta olhando
double rotCamX = 0,  rotCamY = 0, rotCamZ = 0;
/*
GLfloat luzAmbiente[4] = { 0.2,0.2,0.2,1.0 };
GLfloat luzDifusa[4] = { 0.5,0.5,0.5, 1.0 };	   // "cor"
GLfloat luzEspecular[4] = { 0.7,0.7,0.7, 1.0 };// "brilho"
GLfloat posicaoLuz[4] = { 0.0, 50.0, 50.0, 1.0 };
// Capacidade de brilho do material
GLfloat especularidade[4] = { 1.0,1.0,1.0,1.0 };
GLint especMaterial = 10;
*/

GLUquadricObj *novaQuadrica();
void reshapeWindow(GLsizei w, GLsizei h);
void draw();
void animate(int value);
void teclado(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);
void drawMaze( double w, double h);
void drawTable();
void drawRobot();


GLUquadricObj *novaQuadrica(){
	GLUquadricObj *novaQuadrica = gluNewQuadric();
	gluQuadricDrawStyle(novaQuadrica, GLU_FILL);
	gluQuadricOrientation(novaQuadrica, GLU_OUTSIDE);
	gluQuadricNormals(novaQuadrica, GLU_SMOOTH);
	return novaQuadrica;
}

GLUquadricObj *neck = novaQuadrica();
GLUquadricObj *ear = novaQuadrica();
GLUquadricObj *leg = novaQuadrica();
GLUquadricObj *arm = novaQuadrica();
GLUquadricObj *legTable = novaQuadrica();
GLUquadricObj *tampoTable = novaQuadrica();

void swapRB(unsigned char & b, unsigned char & r) {
	unsigned char x;
	x = r;
	r = b;
	b = x;
}

unsigned char *  loadBMP_custom(const char * filename, unsigned int &width, unsigned int &height) {
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	//unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	// Actual RGB data
	unsigned char * data;
	// Open the file
	FILE * file;
	file = fopen( filename, "rb");
	if (!file) { printf("Image could not be opened\n"); return 0; };
	if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return 0;
	}
	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}
	// Read ints from the byte array
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);
	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)    imageSize = width*height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way
	// Create a buffer
	data = new unsigned char[imageSize];
	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);
	for (unsigned int i = 0; i < imageSize; i += 3) swapRB(data[i], data[i + 2]);
	//Everything is in memory now, the file can be closed
	fclose(file);
	return data;
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

GLfloat v_cubo[8][3] = { 
	{-1*ESCALA,-1*ESCALA,-1*ESCALA}, 
	{1*ESCALA,-1*ESCALA,-1*ESCALA}, 
	{1*ESCALA,1*ESCALA,-1*ESCALA}, 
	{-1*ESCALA,1*ESCALA,-1*ESCALA},
	{1*ESCALA,-1*ESCALA,1*ESCALA}, 
	{-1*ESCALA,-1*ESCALA,1*ESCALA},
	{-1*ESCALA,1*ESCALA,1*ESCALA}, 
	{1*ESCALA,1*ESCALA,1*ESCALA}
};

GLfloat v_quadrado[4][3] = { 
	{-1*ESCALA,-1*ESCALA,0}, 
	{1*ESCALA,-1*ESCALA,0}, 
	{1*ESCALA,1*ESCALA,0}, 
	{-1*ESCALA,1*ESCALA,0}
};

GLfloat v_baseDesenho[4][3] = {
	{-10,-10},
	{hMaze + 10, -10},
	{hMaze + 10, wMaze + 10},
	{-10,wMaze + 10}
};




void quadrado(){
	glPushMatrix();
    
    glBegin(GL_QUADS);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lmodel_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, luzEspecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(v_quadrado[0]);
	glTexCoord2f(ESCALA*1.0f, 0.0f);
	glVertex3fv(v_quadrado[1]);
	glTexCoord2f(ESCALA*1.0f,ESCALA*1.0f);
	glVertex3fv(v_quadrado[2]);
	glTexCoord2f(0.0f, ESCALA*1.0f);
	glVertex3fv(v_quadrado[3]);
	glEnd();
	
	glPopMatrix();
}

void cubo(){
    glPushMatrix();
    
    glBegin(GL_QUADS);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lmodel_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, luzEspecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(v_cubo[0]);
	glTexCoord2f(ESCALA*1.0f, 0.0f);
	glVertex3fv(v_cubo[1]);
	glTexCoord2f(ESCALA*1.0f,ESCALA*1.0f);
	glVertex3fv(v_cubo[2]);
	glTexCoord2f(0.0f, ESCALA*1.0f);
	glVertex3fv(v_cubo[3]);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(v_cubo[4]);
	glTexCoord2f(ESCALA*1.0f, 0.0f);
	glVertex3fv(v_cubo[5]);
	glTexCoord2f(ESCALA*1.0f, ESCALA*1.0f);
	glVertex3fv(v_cubo[6]);
	glTexCoord2f(0.0f, ESCALA*1.0f);
	glVertex3fv(v_cubo[7]);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(v_cubo[0]);
	glTexCoord2f(ESCALA*1.0f, 0.0f);
	glVertex3fv(v_cubo[3]);
	glTexCoord2f(ESCALA*1.0f, ESCALA*1.0f);
	glVertex3fv(v_cubo[6]);
	glTexCoord2f(0.0f, ESCALA*1.0f);
	glVertex3fv(v_cubo[5]);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(v_cubo[3]);
	glTexCoord2f(ESCALA*1.0f, 0.0f);
	glVertex3fv(v_cubo[2]);
	glTexCoord2f(ESCALA*1.0f, ESCALA*1.0f);
	glVertex3fv(v_cubo[7]);
	glTexCoord2f(0.0f, ESCALA*1.0f);
	glVertex3fv(v_cubo[6]);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(v_cubo[1]);
	glTexCoord2f(ESCALA*1.0f, 0.0f);
	glVertex3fv(v_cubo[4]);
	glTexCoord2f(ESCALA*1.0f, ESCALA*1.0f);
	glVertex3fv(v_cubo[7]);
	glTexCoord2f(0.0f, ESCALA*1.0f);
	glVertex3fv(v_cubo[2]);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(v_cubo[1]);
	glTexCoord2f(ESCALA*1.0f, 0.0f);
	glVertex3fv(v_cubo[0]);
	glTexCoord2f(ESCALA*1.0f, ESCALA*1.0f);
	glVertex3fv(v_cubo[5]);
	glTexCoord2f(0.0f, ESCALA*1.0f);
	glVertex3fv(v_cubo[4]);
	glEnd();
	
	glPopMatrix();
}

void draw(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Habilita o modelo de colorizacao de Gouraud
	glShadeModel(GL_SMOOTH);
	glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
	// Define a refletencia do material
	//glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	// Define a concentracao do brilho
	//glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	// Ativa o uso da luz ambiente
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	// Define os parametros da luz de numero 0
	/*glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz);*/

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
  glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);


  glLightfv(GL_LIGHT1, GL_POSITION,  light_position2);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa);
  glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular);

	 glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	switch (CAM_ATUAL){
		case CAM_PADRAO: //camera padrao olhando o labirinto de cima
			gluLookAt(camera[X],camera[Y],camera[Z], focus[X], focus[Y], focus[Z], 0,1,0);
			break;
		case CAM_ROBO: //camera que foca o robo
			gluLookAt(posRobo[X], posRobo[Y]-10, posRobo[Z]+30, posRobo[X], posRobo[Y], posRobo[Z], 0,1,0);
			break;
		case CAM_MESA_CENTRO: // camera que foca a mesa central
			gluLookAt(camera[X],camera[Y],camera[Z], focus[X], focus[Y], focus[Z], 0,1,0);
			break;
		case CAM_TEAPOT:
			gluLookAt(camera[X],camera[Y],camera[Z], focus[X], focus[Y], focus[Z], 0,1,0);
			break;
	}
	
	
	
	glColor3f(0.5,0.75,0.25);

	//CHAO
	/*glPushMatrix();
	glScalef(1,1,ALTURA_PAREDE/2);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, chaoid);
		glTranslatef(1,1,1);
		cubo();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glEnd();*/

	//glDisable(GL_LIGHTING);
	//glDisable(GL_LIGHT0);
	//glDisable(GL_LIGHT1);
	//glDisable(GL_NORMALIZE);

	glColor3f(1,0,0);
	drawMaze(wMaze, hMaze);
	drawRobot();
	glutSwapBuffers();

	//MOVIMENTOS DA CABEÇA
	if(ROT_HEAD_RIGHT == true){
		if(rotateHead < 30){ rotateHead = rotateHead + 2;
		}else{ ROT_HEAD_RIGHT = false; }
	}else if(ROT_HEAD_RIGHT == false){
		if(rotateHead > -30){ rotateHead = rotateHead - 2;
		}else{ ROT_HEAD_RIGHT = true; }
	}
	//MOVIMENTOS DOS BRAÇOS
	if(ROT_ARM_FRONT == true){
		if(rotateArms < 15){ rotateArms = rotateArms + 1;
		}else{ ROT_ARM_FRONT = false; }
	}else if(ROT_ARM_FRONT == false){
		if(rotateArms > -15){ rotateArms = rotateArms - 1;
		}else{ ROT_ARM_FRONT = true; }
	}
	//MOVIMENTO DO ROBO COM O TECLADO
	if(angleRotateRobot < rotateRobot){
		angleRotateRobot+=9;
	}else if(angleRotateRobot > rotateRobot){
		angleRotateRobot-=9;
	}
	
	
}

void animate(int value){
	glutPostRedisplay();
	draw();
	glutTimerFunc(60,animate,1);
}

void teclado(unsigned char key, int x, int y){
	switch(key){
		case 'q':
			exit(0);
			break;
		case 'Q':
			exit(0);
			break;
		case '-': //zoom in
			if(CAM_ATUAL == CAM_PADRAO){
				if(camera[Y] > -30){
					camera[Z]-=0.5;
					camera[Y]--;
				}
			}
			break;
		case '+': //zoom out
			if(CAM_ATUAL == CAM_PADRAO){
				if(camera[Z] < 100){
					camera[Z]+=0.5;
					camera[Y]++;
				}
			}
			break;
	}
}

void specialKeys(int key, int x, int y){
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
		case GLUT_KEY_F2: //camera atras do robo e mostrando todo o labirinto
			CAM_ATUAL = CAM_PADRAO;
			camera[X] = hMaze/2;
			camera[Y] = wMaze/2;
			camera[Z] = 100;
			focus[X] = hMaze/2;
			focus[Y] = wMaze/2;
			focus[Z] = 0;
			break;
		case GLUT_KEY_F3: //camera atras do robo estatica olhando o labirinto
			CAM_ATUAL = CAM_ROBO; //camera atras do robo
			break;
		case GLUT_KEY_F4: // camera sobre a mesa central com o bule
			CAM_ATUAL = CAM_MESA_CENTRO;
			camera[X] = hMaze/2;
			camera[Y] = wMaze/2;
			camera[Z] = 25;	
			//posicao em que esta o objeto
			focus[X] = hMaze/2;
			focus[Y] = wMaze/2;
			focus[Z] = 0;
			break;
			
		case GLUT_KEY_F5: //camera em cima da teapot
			CAM_ATUAL = CAM_TEAPOT;
			camera[X] = hMaze-5;
			camera[Y] = wMaze-16;
			camera[Z] = 25;	
			//posicao em que esta o objeto
			focus[X] = hMaze-5;
			focus[Y] = wMaze-16;
			focus[Z] = 0;
			break;
		
		case GLUT_KEY_UP: //anda pra frente
			if(posRobo[Y]+2 < wMaze){
				if(labirinto[posRobo[X]][posRobo[Y]+2] == 1){
					if(labirinto[posRobo[X]-1][posRobo[Y]+2] == 1 && labirinto[posRobo[X]+1][posRobo[Y]+2] == 1){
						//se ele pode andar pra frente
						if(lastMotion != FRENTE){
							rotateRobot = 0;
						}else{
							posRobo[Y]++;
						}
						lastMotion = FRENTE;
					}
				}else if(labirinto[posRobo[X]][posRobo[Y]+2] == TORUS){
					labirinto[posRobo[X]][posRobo[Y]+2] = 1;
					posRobo[Y]++;
					lastMotion = FRENTE;
				}
			}
			break;
		case GLUT_KEY_DOWN: //anda pra tras
			if(posRobo[Y]-2 > 0){
				if(labirinto[posRobo[X]][posRobo[Y]-2] == 1){
					if(labirinto[posRobo[X]-1][posRobo[Y]-2] == 1 && labirinto[posRobo[X]+1][posRobo[Y]-2] == 1){
						// pode andar pra tras
						if(lastMotion != TRAS){
							if(lastMotion == DIREITA){
								rotateRobot = -180;
							}else{
								rotateRobot = 180;
							}
						}else{
							posRobo[Y]--;
						}
						lastMotion = TRAS;
					}
				}else if(labirinto[posRobo[X]][posRobo[Y]-2] == TORUS){
					labirinto[posRobo[X]][posRobo[Y]-2] = 1;
					posRobo[Y]--;
					lastMotion = TRAS;
				}
			}
			break;
		case GLUT_KEY_LEFT: //anda pra esquerda
			if(posRobo[X]-2 > 0){
				if(labirinto[posRobo[X]-2][posRobo[Y]] == 1){
					if(labirinto[posRobo[X]-2][posRobo[Y]-1] == 1 && labirinto[posRobo[X]-2][posRobo[Y]+1] == 1){
						//pode andar pra esquerda
						if(lastMotion != ESQUERDA){
							if(angleRotateRobot == -180)
								angleRotateRobot = 180;
							rotateRobot = 90;
						}else{
							posRobo[X]--;
						}
						lastMotion = ESQUERDA;
					}
				}else if(labirinto[posRobo[X]-2][posRobo[Y]] == TORUS){
					labirinto[posRobo[X]-2][posRobo[Y]] = 1;
					posRobo[X]--;
					lastMotion = ESQUERDA;
				}
			}
			break;
		case GLUT_KEY_RIGHT: //anda pra direita
			if(posRobo[X]+2 < hMaze){
				if(labirinto[posRobo[X]+2][posRobo[Y]] == 1 ){
					if(labirinto[posRobo[X]+2][posRobo[Y]-1] == 1 && labirinto[posRobo[X]+2][posRobo[Y]+1] == 1){
						//pode andar pra direita
						if(lastMotion != DIREITA){
							if(angleRotateRobot == 180)
								angleRotateRobot = -180;
							rotateRobot = -90;
						}else{
							posRobo[X]++;
						}
						lastMotion = DIREITA;
					}
				}else if(labirinto[posRobo[X]+2][posRobo[Y]] == TORUS){
					labirinto[posRobo[X]+2][posRobo[Y]] = 1;
					posRobo[X]++;
					lastMotion = DIREITA;
				}
			}
			break;
	}
//	glutPostRedisplay();
}


void drawMaze( double w, double h){
	
	//desenhar base fora do labirinto
	glPushMatrix();
		glTranslatef(0,0,-1);
		glColor3f(0.3,1,0.3);
		glBegin(GL_QUADS);
		glVertex3fv(v_baseDesenho[0]);	
		glVertex3fv(v_baseDesenho[1]);
		glVertex3fv(v_baseDesenho[2]);
		glVertex3fv(v_baseDesenho[3]);
		glEnd();
	glPopMatrix();
	glPushMatrix();
	//glTranslatef(0,0,1.5);
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			if(labirinto[i][j] == PAREDE){ //se posicao do labirinto for uma parede
				glPushMatrix();
					glColor3f(1.0f, 1.0f, 1.0f);
					glScalef(1,1,ALTURA_PAREDE);
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, paredeid);
					glTranslatef(i,j,ESCALA);
					cubo();
					glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}else{
				glPushMatrix();
				glColor3f(1.0f, 1.0f, 1.0f);
					glScalef(1,1,0);
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, chaoid);
					glTranslatef(i,j,ESCALA);
					quadrado();
					glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}
			/*if(labirinto[i][j] == CHAO){
				glPushMatrix();
				glColor3f(1.0f, 1.0f, 1.0f);
					glScalef(1,1,0);
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, chaoid);
					glTranslatef(i,j,ESCALA);
					quadrado();
					glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}else */
			if(labirinto[i][j] == MESA){ //se for objeto CONE
				glPushMatrix();
					glColor3f(1,0.75,0.25);
					glTranslatef(i,j,1.5);
					drawTable();
					glPushMatrix();
						glColor3f(0.2,0.2,0.2);
						glTranslatef(0,0,ALTURA_PAREDE/3);
						glRotatef(90,1,0,0);
						glRotatef(-45,0,0,1);
						glutSolidTeapot(0.4);
					glPopMatrix();
				glPopMatrix();
			}else if(labirinto[i][j] == TORUS){ //se for objeto TORUS
				glPushMatrix();
					glColor3f(1,1,0);
					glTranslatef(i,j,1);
					glRotatef(90,0,1,0);
					glRotatef(rotateTORUS+=0.125,1,0,0);
					glutSolidTorus(0.3, 0.7,50,50);
				glPopMatrix();
			}else if(labirinto[i][j] == TEAPOT){ //se for objeto CHALEIRA
				glPushMatrix();
					glColor3f(0.2,0.2,0.2);
					glTranslatef(i,j,1.5);
					glRotatef(90,1,0,0);
					glRotatef(rotateTEAPOT++,0,1,0);
					glutSolidTeapot(0.75);
				glPopMatrix();
			}else if(labirinto[i][j] == OBJS){
				//desenhar um cubo com uma bola em cima
				glPushMatrix();
					glColor3f(0.625,0.625,0.625);
					glTranslatef(i,j,1.5);
					glRotatef(45,0,0,1);
					glRotatef(rotateCUBE++,0,0,1);
					glutSolidCube(2);
					glColor3f(0.625,0.125,0.625);
					glTranslatef(0,0,2);
					glutSolidCone(0.75,3,50,50);
					glColor3f(0.625,0.625,0.125);
					glTranslatef(0,0,3);
					glutSolidSphere(0.5, 50,50);
				glPopMatrix();
			}
		}
	}
	glPopMatrix();

	//transparencia
	glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


};

void drawTable(){
	//PERNAS
		glPushMatrix();
			glTranslatef(-1,1,0);
			gluCylinder(legTable,0.25,0.25,ALTURA_PAREDE/2,50,50);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1,1,0);
			gluCylinder(legTable,0.25,0.25,ALTURA_PAREDE/2,50,50);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1,-1,0);
			gluCylinder(legTable,0.25,0.25,ALTURA_PAREDE/2,50,50);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-1,-1,0);
			gluCylinder(legTable,0.25,0.25,ALTURA_PAREDE/2,50,50);
		glPopMatrix();
		//TAMPO DA MESA
		glPushMatrix();
			glTranslatef(0,0,ALTURA_PAREDE/2);
			gluDisk(tampoTable, 0,2,50,50);
		glPopMatrix();
	glPopMatrix();
};

void drawRobot(){
//	glPushMatrix();
		glTranslatef(posRobo[X],posRobo[Y],posRobo[Z]);
		glRotatef(angleRotateRobot,0,0,1);
		//PERNAS
		glColor3f(0.4f,0.4f,0.4f);
		glPushMatrix();
			glTranslatef(0.4,0,2);
			glRotatef(-rotateArms,1,0,0);
			glRotatef(-180,1,0,0);
			gluCylinder(leg, 0.15, 0.15, 2, 50,50);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.4,0,2);
			glRotatef(rotateArms,1,0,0);
			glRotatef(-180,1,0,0);
			gluCylinder(leg, 0.15, 0.15, 2, 50,50);
		glPopMatrix();
		//TRONCO
		glColor3f(0.7f,0.3f,0.3f);
		glPushMatrix();
			glTranslatef(0, 0, 0.25*13);
			glScalef(2,1,3);
			glutSolidCube(1);
		glPopMatrix();
		//BRAÇOS
		glColor3f(0.2f,0.2f,0.2f);
		//BRAÇO DIREITO
		glPushMatrix();
			glTranslatef(1.125, 0, 0.25*16);
			glutSolidSphere(0.25,50,50);
			glRotatef(-4.5,0,1,0);
			glRotatef(rotateArms, 1,0,0);
			glRotatef(-180,1,0,0);
			gluCylinder(arm,0.15,0.15, 2.5, 50,50);
		glPopMatrix();
		//BRAÇO ESQUERDO
		glPushMatrix();
			glTranslatef(-1.125, 0, 0.25*16);
			glutSolidSphere(0.25,50,50);
			glRotatef(+4.5,0,1,0);
			glRotatef(-rotateArms, 1,0,0);
			glRotatef(-180,1,0,0);
			gluCylinder(arm,0.15,0.15, 2.5, 50,50);
		glPopMatrix();
		//PESCOÇO
		glColor3f(0.25f,0.25f,0.25f);
		glPushMatrix();
			glTranslatef(0, 0, 0.25*19);
			gluCylinder(neck,0.55,0.33,1.25,40,40);
		glPopMatrix();
		//CABEÇA
		glPushMatrix();
			glRotatef(rotateHead,0,0,1);
			glColor3f(0.65f,0.55f,0.44f);
			glPushMatrix();
				glTranslatef(0, 0, 0.25*24);
				glutSolidSphere(0.75,50,50);
			glPopMatrix();
			//ORELHA
			glColor3f(0.25f,0.25f,0.25f);
			//ORELHA DIREITA
			glPushMatrix();
				glTranslatef(0.5, 0, 0.25*26);
				glRotatef(90,1,0,0);
				glScalef(0.75,0.75,0.75);
				glutSolidTorus(0.25,0.5,50,50);
			glPopMatrix();
			//ORELHA ESQUERDA
			glPushMatrix();
				glTranslatef(-0.5, 0, 0.25*26);
				glRotatef(90,1,0,0);
				glScalef(0.75,0.75,0.75);
				glutSolidTorus(0.25,0.5,50,50);
			glPopMatrix();
			//OLHOS
			glColor3f(1,1,1);
			//OLHO DIREITO
			glPushMatrix();
				glTranslatef(0.25, 0.45, 0.25*24.75);
				glutSolidSphere(0.25,50,50);
			glPopMatrix();
			//OLHO ESQUERDO
			glPushMatrix();
				glTranslatef(-0.25, 0.45, 0.25*24.75);
				glutSolidSphere(0.25,50,50);
			glPopMatrix();
		glPopMatrix();
//	glPopMatrix();
};

GLuint loadTex(unsigned char *Imagem,unsigned int ih,unsigned int iw){
    GLuint textureId;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &textureId);
	glBindTexture (GL_TEXTURE_2D,textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iw, ih, 0,GL_RGB, GL_UNSIGNED_BYTE, Imagem);
	gluBuild2DMipmaps(textureId, GL_RGB, iw, ih, GL_RGB, GL_UNSIGNED_BYTE, Imagem);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	return textureId;
}

void drawTexture(void){
	unsigned int ih=0, iw=0;
	unsigned char * imagem = NULL;
	glShadeModel(GL_SMOOTH);

    imagem = loadBMP_custom("floor2.bmp", iw, ih);
      chaoid = loadTex(imagem,ih,iw);

  	imagem = loadBMP_custom("wall3.bmp", iw, ih);
      paredeid = loadTex(imagem,ih,iw);

      /*imagem = loadBMP_custom("mad.bmp", iw, ih);
      madid = loadTex(imagem,ih,iw);

	imagem = loadBMP_custom("areia.bmp", iw, ih);
      areiaid = loadTex(imagem,ih,iw);*/


    delete imagem;
}

//##########################//
//			MAIN			//
//##########################//
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(windowPosX,windowPosY);
	glutInitWindowSize(windowWidth,windowHeight);
	glutCreateWindow("Computação Gráfica - Trabalho 1 - Labirinto 3D");
	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de numero 0
	glEnable(GL_LIGHT1);


	//FUNCOES DE CALLBACK
	glutReshapeFunc(reshapeWindow);
	glutTimerFunc(60, animate, 1);
	drawTexture();
	glutDisplayFunc(draw);
	glutSpecialFunc(specialKeys);
	glutFullScreen();
	glutKeyboardFunc(teclado);
	glutMainLoop();
}
