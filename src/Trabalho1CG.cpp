//============================================================================
// Name        : Trabalho1CG.cpp
// Author      : Jackson Henrique Hochscheidt
//			   : Kevin Spiller
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <GL/glut.h>

//Declaracao de variaveis globais e defines

#define wMaze 25
#define hMaze 15

double labirinto[hMaze][wMaze]={
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,1,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0},
		{0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0},
		{0,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,0},
		{1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1},
		{0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0},
		{0,1,1,1,1,0,1,0,1,1,1,1,0,1,1,1,1,0,1,0,1,1,1,1,0},
		{0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

#define X 0
#define Y 1
#define Z 2
#define ALTURA_PAREDE 1
double angPerspective = 45;
double rotX = 0, rotY = 0, rotZ = 0;

//posicao inicial da camera -- vetor[3] = [x,y,z]
double camera[3] = {0,50,20};


#include <GL/glut.h>
#include <stdio.h>


void reshapeWindow(GLsizei w, GLsizei h);

void draw();

void drawMaze(double w, double h);

GLUquadricObj *novaQuadrica();

GLUquadricObj *chao = novaQuadrica();

void teclado(unsigned char key, int x, int y);

int main(int argc, char **argv) {

	//inicializa GLUT com parametros necessarios

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);


	//cria JANELA DE VISUALIZACAO
	glutInitWindowPosition(0,0);
	glutInitWindowSize(700,700);
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
	glutKeyboardFunc(teclado);

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
	glRotatef(-90,0,0,1);
	glRotatef(-90,0,1,0);

	glBegin(GL_QUADS);
		glVertex3f(0,0,0);
		glVertex3f(hMaze,0,0);
		glVertex3f(hMaze,wMaze,0);
		glVertex3f(0,wMaze,0);
	glEnd();

	glTranslatef(0,0,ALTURA_PAREDE/2);
	//glColor3f(1,0,0);


	//glutSolidCube(1);
	drawMaze(wMaze, hMaze);



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
			camera[Z]--;
			break;
		case '+': //zoom out
			camera[Z]++;

	}
}

void drawMaze( double w, double h){
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
			}
		}
	}

}
