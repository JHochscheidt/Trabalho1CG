//============================================================================
// Name			: Trabalho1CG.cpp
// Author		: Jackson Henrique Hochscheidt
//			   	: Kevin Mitchell Spiller
// CCR			: Computação Gráfica - 2017.2 - Noturno
//============================================================================

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "Labirinto.h"
#include "Table.h"
#include "Robot.h"
#include "Textura.h"



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
#define CAM_CUBO_CONE_ESFERA 6
#define CAM_JANELA_LATERAL 7
#define FRENTE 1
#define TRAS 2
#define ESQUERDA 3
#define DIREITA 4
#define CHAO 1
#define ESCALA 0.5
#define MAXTEXTURES 1
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


int windowWidth  = 700;
int windowHeight = 700;
int windowPosX   = 0;
int windowPosY   = 0;
bool fullScreenMode = true;
double angPerspective = 45;
double rotateTORUS = 0;
double rotateTEAPOT = 0;
double rotateCUBE = 0;
int lastMotion = -1;
double angleRotateRobot = 0;

int CAM_ATUAL = CAM_PADRAO;
bool ROT_ARM_FRONT = true;
bool ROT_HEAD_RIGHT = true;
int posRobo[3] = {22,0,0};
double camera[3] = {hMaze/2,wMaze/2,100};
double focus[3] = {hMaze/2,wMaze/2,0}; // para onde a camera esta olhando
double rotCamX = 0,  rotCamY = 0, rotCamZ = 0;

GLuint texnum[MAXTEXTURES]; // [0]-> Walls, [1] -> Water



GLUquadricObj *novaQuadrica();
void reshapeWindow(GLsizei w, GLsizei h);
void draw();
void animate(int value);
void teclado(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);
void drawMaze( double w, double h);


void iluminacao(){

	// primeira luz
	GLfloat luzDifusa1[] = { 0.8f,0.8f,0.8f, 1.0 };	// "cor"
	GLfloat luzEspecular1[] = {1,1,1, 1.0 };// "brilho"
	GLfloat light_position1[] = {hMaze*5 , wMaze*5, ALTURA_PAREDE*2, 1.0f };
	GLfloat lightSpotDirection1[] = {0, -1, 0};


	glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular1);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightSpotDirection1);

	// segunda luz
	GLfloat luzDifusa2[] = { 0.8f,0.5f,0.5f, 1.0 };	// "cor"
	GLfloat luzEspecular2[] = {1,1,1, 1.0 };// "brilho"
	GLfloat light_position2[] = {10.0f, 60.0f, ALTURA_PAREDE*2, 1.0f };
	GLfloat lightSpotDirection2[] = {0, -1, 0};

  glLightfv(GL_LIGHT2, GL_DIFFUSE, luzDifusa2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, luzEspecular2);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lightSpotDirection2);

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


void drawBox(GLfloat size, GLenum type){
  static GLfloat n[6][3] =
  {
    {-1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, -1.0}
  };
  static GLint faces[6][4] =
  {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {5, 6, 2, 1},
    {7, 4, 0, 3}
  };
  GLfloat v[8][3];
  GLint i;

  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

  glColor3f(0.4, 0.4, 0.4);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, paredeid);
  for (i = 5; i >= 0; i--) {
    glBegin(type);
        glNormal3fv(&n[i][0]);
        glTexCoord2f(1, 0);
        glVertex3fv(&v[faces[i][0]][0]);
        glTexCoord2f(1, 1);
        glVertex3fv(&v[faces[i][1]][0]);
        glTexCoord2f(0, 1);
        glVertex3fv(&v[faces[i][2]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
  }
  glDisable(GL_TEXTURE_2D);
}

void drawWall(float size) {
    size = size / 2;


    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, paredeid);

    glBegin(GL_QUADS);
        // TRASEIRA
        glTexCoord2f(1, 0);
        glVertex3f(size, -size, size);
        glTexCoord2f(1, 1);
        glVertex3f(size,  size, size);
        glTexCoord2f(0, 1);
        glVertex3f(-size,  size, size);
        glTexCoord2f(0, 0);
        glVertex3f(-size, -size, size);

        // FRENTE
        glTexCoord2f(1, 0);
        glVertex3f(size, -size, -size);
        glTexCoord2f(1, 1);
        glVertex3f(size, size, -size);
        glTexCoord2f(0, 1);
        glVertex3f(-size, size, -size);
        glTexCoord2f(0, 0);
        glVertex3f(-size, -size, -size);

        // DIREITA
        glTexCoord2f(1, 0);
        glVertex3f(size, -size, -size);
        glTexCoord2f(1, 1);
        glVertex3f(size, size, -size);
        glTexCoord2f(0, 1);
        glVertex3f(size, size, size);
        glTexCoord2f(0, 0);
        glVertex3f(size, -size, size);

        // ESQUERDA
        glTexCoord2f(1, 0);
        glVertex3f(-size, -size, size);
        glTexCoord2f(1, 1);
        glVertex3f(-size, size, size);
        glTexCoord2f(0, 1);
        glVertex3f(-size, size, -size);
        glTexCoord2f(0, 0);
        glVertex3f(-size, -size, -size);

        // TOPO
        glTexCoord2f(1, 0);
        glVertex3f(size, size, size);
        glTexCoord2f(1, 1);
        glVertex3f(size, size, -size);
        glTexCoord2f(0, 1);
        glVertex3f(-size, size, -size);
        glTexCoord2f(0, 0);
        glVertex3f(-size, size, size);

        // BASE
        glTexCoord2f(1, 0);
        glVertex3f(size, -size, -size);
        glTexCoord2f(1, 1);
        glVertex3f(size, -size, size);
        glTexCoord2f(0, 1);
        glVertex3f(-size, -size, size);
        glTexCoord2f(0, 0);
        glVertex3f(-size, -size, -size);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_AUTO_NORMAL);
}

void drawCube(float size) {
    glColor3f(0.48, 0.80, 0.12);
    glutSolidCube(size);
}














void cubo(){
    glPushMatrix();
		glBegin(GL_QUADS);

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

void drawWindow1() {

	  //desenhando molduras
    //cima
    glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,windowid);
			glTranslatef(4, 4, 5);
			glScalef(1,5,2);
      cubo();
			glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //baixo
    glPushMatrix();
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,windowid);
				glTranslatef(4, 4, -3);
        glScalef(1,5,2);
        cubo();
				glDisable(GL_TEXTURE_2D);
    glPopMatrix();

		glPushMatrix();
      glTranslatef(4, 4, 1);
			glScalef(1,5,6);
			glColor4f(1.0f, 0.5f, 0.3f, 0.15f);
      cubo();
    glPopMatrix();

}

void draw(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();



	switch (CAM_ATUAL){
		case CAM_PADRAO: //camera padrao olhando o labirinto de cima
			gluLookAt(camera[X],camera[Y],camera[Z], focus[X], focus[Y], focus[Z], 0,1,0);
			break;
		case CAM_ROBO: //camera que foca o robo
			gluLookAt(posRobo[X], posRobo[Y]-10, posRobo[Z]+30, posRobo[X], posRobo[Y], posRobo[Z], 0,0,1);
			break;
		case CAM_MESA_CENTRO: // camera que foca a mesa central
			gluLookAt(camera[X],camera[Y],camera[Z], focus[X], focus[Y], focus[Z], 0,0,1);
			break;
		case CAM_TEAPOT:
			gluLookAt(camera[X],camera[Y],camera[Z], focus[X], focus[Y], focus[Z], 0,0,1);
			break;
		case CAM_CUBO_CONE_ESFERA:
			gluLookAt(camera[X],camera[Y],camera[Z], focus[X], focus[Y], focus[Z], 0,0,1);
			break;
		case CAM_JANELA_LATERAL:
			gluLookAt(camera[X],camera[Y],camera[Z], focus[X], focus[Y], focus[Z], 0,0,1);
			break;
	}


	iluminacao();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glColor3f(0.5,0.75,0.25);


	glColor3f(1,0,0);
	drawMaze(wMaze, hMaze);



	drawRobot(posRobo, angleRotateRobot, rotateArms, rotateHead, leg, arm, neck);


	//Draw windowed wall after objects otherwise they don't show up beside the glass
    glPushMatrix();
      glTranslatef(26,43,4);
      glRotatef(90,0,0,1);
      drawWindow1();
    glPopMatrix();


		glPushMatrix();
			glTranslatef(26,70,4);
			glRotatef(90,0,0,1);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			drawWindow1();
		glPopMatrix();

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
	glutSwapBuffers();



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
			camera[X] = 22;
			camera[Y] = 25;
			camera[Z] = 20;
			//posicao em que esta o objeto
			focus[X] = 22;
			focus[Y] = 37;
			focus[Z] = 10;
			break;

		case GLUT_KEY_F5: //camera em cima da teapot
			CAM_ATUAL = CAM_TEAPOT;
			camera[X] = hMaze-5;
			camera[Y] = wMaze-30;
			camera[Z] = 10;
			//posicao em que esta o objeto
			focus[X] = hMaze-5;
			focus[Y] = wMaze-16;
			focus[Z] = 2.5;
			break;
		case GLUT_KEY_F6: // camera sobre os 3 objetos [CUBO/CONE/ESFERA]
			CAM_ATUAL = CAM_CUBO_CONE_ESFERA;
			camera[X] = 15;
			camera[Y] = 13;
			camera[Z] = 1;
			//posicao em que esta o objeto
			focus[X] = 26;
			focus[Y] = 13;
			focus[Z] = 2.5;
			break;

		case GLUT_KEY_F7: // camera que olha pela janela lateral
			CAM_ATUAL = CAM_JANELA_LATERAL;
			camera[X] = 22;
			camera[Y] = 60;
			camera[Z] = 15;
			//posicao em que esta o objeto
			focus[X] = 22;
			focus[Y] = 70;
			focus[Z] = 5;
			break;



			//40,39,4

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
}


void drawMaze( double w, double h){

	//desenhar base fora do labirinto
	 glPushMatrix();
	 	glTranslatef(0,0,-0.1);
	 	glColor3f(0.3,1,0.3);
	 	glBegin(GL_QUADS);
	 	glVertex3fv(v_baseDesenho[0]);
	 	glVertex3fv(v_baseDesenho[1]);
	 	glVertex3fv(v_baseDesenho[2]);
	 	glVertex3fv(v_baseDesenho[3]);
	 	glEnd();
	 glPopMatrix();
	 static GLfloat normal[] = {0.0, 1.0, 0.0};

	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			if(labirinto[i][j] == PAREDE){ //se posicao do labirinto for uma parede
				glPushMatrix();
					glColor3f(0.1f, 0.1f, 0.1f);
					glScalef(1,1,ALTURA_PAREDE);
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, paredeid);
					glTranslatef(i,j,ESCALA);
					drawBox(1, GL_QUADS);
					glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}else{
				glPushMatrix();

				glColor3f(0.5f, 0.5f, 0.5f);
					glScalef(1,1,0);
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, chaoid);
					glTranslatef(i,j,ESCALA);
					quadrado();
					glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}

			if(labirinto[i][j] == MESA){ //se for objeto MESA
				glPushMatrix();
					glColor3f(1,0.75,0.25);
					glTranslatef(i,j,0);
					drawTable(legTable, tampoTable, ALTURA_PAREDE);
					glPushMatrix();
						glColor3f(0.1,0.2,0.3);
						glTranslatef(i,j,6);
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
					glTranslatef(i,j,0.6);
					glRotatef(90,1,0,0);
					glRotatef(rotateTEAPOT++,0,1,0);
					glutSolidTeapot(0.8);
				glPopMatrix();
			}else if(labirinto[i][j] == OBJS){
				//desenha um cubo com um cone em cima, e uma esfera sobre o cone
				glPushMatrix();
					glColor3f(0.625,0.625,0.625);
					glTranslatef(i,j,1);
					glRotatef(45,0,0,1);
					glRotatef(rotateCUBE++,0,0,1);
					glutSolidCube(2);
					glColor3f(0.625,0.125,0.625);
					glTranslatef(0,0,1);
					glutSolidCone(0.75,3,50,50);
					glColor3f(0.625,0.625,0.125);
					glTranslatef(0,0,3);
					glutSolidSphere(0.5, 50,50);
				glPopMatrix();
			}
		}
	}
	glPopMatrix();



};


void init(){

	// configs iluminacao
	GLfloat luzAmbiente[] = {1.0f,1.0f,1.0f,1.0f};
	GLfloat especularidade[] = {1.0f,1.0f,1.0f,1.0f};
	GLint especMaterial = 50;
	//Lfloat mat_shininess[] = { 50.0 };


	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de numero 0
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);

  	glEnable(GL_NORMALIZE);


    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especularidade);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, especMaterial);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);


    // Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

//##########################//
//			MAIN			//
//##########################//
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(windowPosX,windowPosY);
	glutInitWindowSize(windowWidth,windowHeight);
	glutCreateWindow("Computação Gráfica - Trabalho 2 - Labirinto 3D");


	//FUNCOES DE CALLBACK
	glutReshapeFunc(reshapeWindow);
	glutTimerFunc(60, animate, 1);
	drawTexture();
	glutDisplayFunc(draw);
	glutSpecialFunc(specialKeys);
	glutFullScreen();
	glutKeyboardFunc(teclado);
	init();
	glutMainLoop();
}
