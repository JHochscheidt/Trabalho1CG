GLfloat knots[8] = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0};

//	Variáveis para desenhar os paralelepipedos da mesa
GLfloat pos = 0.5, lar = 20, alt = 15;
GLfloat vertices[8][3] = {
	{-pos - lar, -pos - alt,  pos}, 	{-pos - lar,  pos + alt,  pos},
	{ pos + lar,  pos + alt,  pos}, 	{ pos + lar, -pos - alt,  pos},
	{-pos - lar, -pos - alt, -pos}, 	{-pos - lar,  pos + alt, -pos},
	{ pos + lar,  pos + alt, -pos}, 	{ pos + lar, -pos - alt, -pos}
};

GLfloat vertices2[8][3] = {
	{pos, pos, 0 }, {0,  pos,  0}, { 0, 0, 0}, 	{ pos, 0,  0},
	{pos, pos, alt }, {0,  pos,  alt}, { 0, 0, alt}, 	{ pos, 0,  alt},
};


//	Função para desenhar um retângulo, vértices com a ordem do esquema a cima
void retangulo(int br, int bl, int tl, int tr) {
	glNormal3f(vertices2[br][0], vertices2[br][1], vertices2[br][2]);
	glVertex3fv(vertices2[br]);

	glNormal3f(vertices2[bl][0], vertices2[bl][1], vertices2[bl][2]);
	glVertex3fv(vertices2[bl]);

	glNormal3f(vertices2[tl][0], vertices2[tl][1], vertices2[tl][2]);
	glVertex3fv(vertices2[tl]);

	glNormal3f(vertices2[tr][0], vertices2[tr][1], vertices2[tr][2]);
	glVertex3fv(vertices2[tr]);
}

//	Função para desenhar o paralelepípedo, face por face.
void paralelepipedo() {
	glPushMatrix();
		glBegin(GL_QUADS);
			retangulo(0, 1, 2, 3);
			retangulo(4, 5, 6, 7);
			retangulo(1, 5, 6, 2);
			retangulo(4, 0, 3, 7);
			retangulo(3, 2, 6, 7);
			retangulo(0, 1, 5, 4);
		glEnd();
	glPopMatrix();
}


//  Função que desenha as nurbs. Os pontos de controle devem ser passados já com
//  os valores inicializados.
void desenha(GLfloat knots[8], GLUnurbsObj *theNurb, GLfloat cp[4][4][3])
{
    int i, j;

    glPushMatrix();
        gluBeginSurface(theNurb);
            gluNurbsSurface(theNurb, 8, knots, 8, knots, 4 * 3, 3, &cp[0][0][0], 4, 4, GL_MAP2_VERTEX_3);
        gluEndSurface(theNurb);

        //  Se for mostrar os pontos de controle, desenha eles de amarelo
        // if(showPoints){
        //     glPointSize(5.0);
        //     glDisable(GL_LIGHTING);
        //         glColor3f(1.0, 1.0, 0.0);
        //
        //         glBegin(GL_POINTS);
        //             for(i = 0; i < 4; i++){
        //                 for (j = 0; j < 4; j++){
        //                     glVertex3f(cp[i][j][0], cp[i][j][1], cp[i][j][2]);
        //                 }
        //             }
        //         glEnd();
        //     glEnable(GL_LIGHTING);
        // }
    glPopMatrix();
}
