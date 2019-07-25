/*GLint //pegando a parte inteira da bibliot do glglut-open gl --sao numeros inteiros

void init (void) // para trabalhar as cores

void display
//o que vai mostrar na tela
//vai criar uma borda
glBeginWidht // linha da tela

glpoint(15.0);//um ponto -- bolinha que vai ficar mexendo

// -->  teclado (o que esta implementado) //quando clicar uma tecla qualquer vai clicar sai
*/
#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <cmath>
#include <sstream> 

GLint largura = 300;
GLint altura = 100;

GLint moveRaqDir = 0; //move A raquete direita
GLint moveRaqEsq = 0; // move A raquete Esquerda

GLint pos_bola_x = largura/2;
GLint pos_bola_y = altura/2;

// Bola pos
float xBola=300.0;
float yBola=200.0;
float xDir=1;
float yDir=1;
void verificaColisao();

// Pontuação
int player1 = 0;
int player2 = 0;
int vel = 1;

// Iniciar jogo
bool valendo = false;

void init(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glOrtho (0, 600, 0, 400, -1 ,1);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(15.0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(2,2); glVertex2i(599,2);
	glVertex2i(599,399); glVertex2i(2,399);
	glEnd();
	glBegin(GL_LINES);
		glVertex2i(100,moveRaqDir + 190);
		glVertex2i(100,moveRaqDir + 240); 
		glVertex2i(500,moveRaqEsq + 190); 
		glVertex2i(500,moveRaqEsq + 240);
	glEnd();
	//  Pontuacao jogador 1
	char num[10];
	char texto[25];
	glColor3f(1.0, 0, .5); 
	int tam =0;
	glPushMatrix();
		sprintf(num, "%d", player1);
		strcpy(texto,"Player1 ");
		tam = strlen(texto);
		glRasterPos2i(10, 380);			
		for ( int i = 0; i < tam; ++i )
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
		}
		strcpy(texto,"Pontos ");
		tam = strlen(texto);
		glRasterPos2i(10, 360);			
		for ( int i = 0; i < tam; ++i )
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
		}
		strcpy(texto,num);
		tam = strlen(texto);
		glRasterPos2i(10, 345);			
		for ( int i = 0; i < tam; ++i )
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
		}
	glPopMatrix();
	//  Pontuacao jogador 2
	glPushMatrix();
		sprintf(num, "%d", player2);
		strcpy(texto,"Player2 ");
		tam = strlen(texto);
		glRasterPos2i(510, 380);			
		for ( int i = 0; i < tam; ++i )
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
		}
		strcpy(texto,"Pontos ");
		tam = strlen(texto);
		glRasterPos2i(510, 360);			
		for ( int i = 0; i < tam; ++i )
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
		}
		
		strcpy(texto,num);
		tam = strlen(texto);
		glRasterPos2i(510, 345);			
		for ( int i = 0; i < tam; ++i )
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
		}
	glPopMatrix();
	//  Tela de entrada
	if(!valendo)
	{
		glPushMatrix();
			strcpy(texto,"Aperte 'f' para iniciar ");
			tam = strlen(texto);
			glRasterPos2i(230, 280);			
			for ( int i = 0; i < tam; ++i )
			{
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
			}
		glPopMatrix();
	}
	glPointSize(15.0);
	glBegin(GL_POINTS);
	glVertex2i(xBola,yBola);
	verificaColisao();
	glEnd();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{	
	switch (key) {
		// --- [ RAQUETES ] ---
		case 'w': // cima esquerdo
			if(moveRaqDir<= 148) 
			{
				moveRaqDir += 10;
			} 
		break;
		
		case 's': // baixo esquerdo
			if(moveRaqDir> -175) 
			{
				moveRaqDir -= 10;
			} 
		break;
		case 'i': // cima direito
			if(moveRaqEsq<= 148) 
			{
				moveRaqEsq += 10;
			} 
		break;
		case 'k': // baixo direito
			if(moveRaqEsq> -175) 
			{
				moveRaqEsq -= 10;
			} 
		break;
		// --- [ MENU ] ---
		case 'f': // inicia jogo
			valendo=true;
			xBola=300;
			yBola=200;
			xDir*=-1;
			yDir*=-1;
		break;
	}
	glutPostRedisplay();
}


void verificaColisao()
{
	// colisão raquete esquerda
	if ((xBola>=496&&xBola<=502)&&(yBola>=(moveRaqEsq+190)&&yBola<=(moveRaqEsq+240))){
		xDir = -1;
	}
	// colisão com raquete direita
	if ((xBola>=98&&xBola<=104)&&(yBola>=(moveRaqDir+190)&&yBola<=(moveRaqDir+240))){
		xDir = 1;
	}
	// colisão vertical negativo
	if (yBola >= 390)
	{
		yDir = -1; // invertendo eixo
	}
	// colisão vertical positivo
	if (yBola <= 10)
	{
		yDir = 1; // invertendo eixo
	}
	// Pontucação
	if(xBola >= 590) // Colisão com a parede da direita
	{
		if(valendo)
			player1++;
		valendo=false;
	}
	if(xBola <= 10) // Colisão com a parede da esquerda
	{
		if(valendo)
			player2++;
		valendo=false;
	}
}

void bola(int passo)
{	
	if(valendo)
	{
		xBola+=xDir;
		yBola+=yDir;	
	}	
	glutPostRedisplay();
	glutTimerFunc(10,bola, 1);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (600, 400);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Pong");
	init();
	glutDisplayFunc(display);
	glutTimerFunc(10,bola,1);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}