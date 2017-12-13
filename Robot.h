#include <GL/glut.h>

#define X 0
#define Y 1
#define Z 2

double rotateRobot = 0;
double rotateArms = 0;
double rotateHead = 0;

void drawRobot(int posRobo[], double angleRotateRobot, double rotateArms, double rotateHead,
                              GLUquadricObj *leg, GLUquadricObj *arm, GLUquadricObj *neck );

void drawRobot(int posRobo[], double angleRotateRobot, double rotateArms, double rotateHead,
                              GLUquadricObj *leg, GLUquadricObj *arm, GLUquadricObj *neck ){
	glPushMatrix();
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
	glPopMatrix();
};
