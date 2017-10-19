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

#define wMaze 50
#define hMaze 7

double labirinto[hMaze][wMaze] ={
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0},
		{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},

};
//
//double labirinto[hMaze][wMaze]={
//		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//		{0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0},
//		{0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0},
//		{0,1,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,1,0},
//		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
//		{0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0},
//		{0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0},
//		{0,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,0},
//		{1,1,1,1,1,1,1,0,1,0,2,1,1,1,1,0,1,0,1,1,1,1,1,1,0},
//		{0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0},
//		{0,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
//		{0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0},
//		{0,1,1,1,1,0,1,0,1,1,1,1,0,1,1,1,1,0,1,0,1,1,1,1,0},
//		{0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0},
//		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,1,1,1,1,0},
//		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
//};

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
#define ALTURA_PAREDE 2
#define TEAPOT 4
double angPerspective = 45;
double rotX = 0, rotY = 0, rotZ = 0;
double rotateTORUS = 0;
double rotateTEAPOT = 0;

//posicao inicial da camera -- vetor[3] = [x,y,z]
double camera[3] = {0,50,5};

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
         } else {                                         // Modo janela
            glutReshapeWindow(windowWidth, windowHeight); // Troca para modo janela
            glutPositionWindow(windowPosX, windowPosX);   // Posição do topo canto esquerdo
         }
         break;
   }
}

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
	glTranslatef(-10,-10,0);
//	glRotatef(-90,0,1,0);
//	glRotatef(180,0,0,1);


	glTranslatef(0,0,2.5);

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
			camera[Y]--;
			break;
		case '+': //zoom out
			camera[Y]++;

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
			}else if(labirinto[i][j] == 2){
				glPushMatrix();
					glColor3f(0.7,0.6,0.5);
					glTranslatef(i,j,0);
					glutSolidCone(0.5,ALTURA_PAREDE,50,50);
				glPopMatrix();
			}else if(labirinto[i][j] == 3){
				glPushMatrix();
					glColor3f(1,1,0);
					glTranslatef(i,j,0);
					glRotatef(90,0,1,0);
					glScalef(-0.5,-0.5,-0.5);
					glRotatef(rotateTORUS++,1,0,0);
					glutSolidTorus(0.1, 0.7,50,50);
				glPopMatrix();
			}else if(labirinto[i][j] == 4){
				glPushMatrix();
					glColor3f(0.2,0.2,0.2);
					glTranslatef(i,j,0);
					glRotatef(90,1,0,0);
					glRotatef(rotateTEAPOT++,0,1,0);
					glScalef(1,1,ALTURA_PAREDE/2);
//					glRotatef(rotateTORUS++,1,0,0);
					glutSolidTeapot(0.3);
				glPopMatrix();
			}
		}
	}

}
