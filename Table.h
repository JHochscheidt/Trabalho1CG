#include <GL/glut.h>



void drawTable(GLUquadricObj *legTable, GLUquadricObj *tampoTable, int ALTURA_PAREDE);
void drawTable(GLUquadricObj *legTable, GLUquadricObj *tampoTable, int ALTURA_PAREDE){
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
