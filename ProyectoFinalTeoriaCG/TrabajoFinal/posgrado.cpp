//Semestre 2019 - 1
//************************************************************//
//************** Alumno (s): *********************************//
//******************** GALVÁN HERNÁNDEZ KARINA ***************//
//******************** HEREDIA CÓRDOVA TANIA ROCÍO ***********//
//******************** TREJO LUNA EVA MARION SHANIK **********//
//************** VISUAL STUDIO 2015 **************************//
//************************************************************//

#include "texture.h"
#include "figuras.h"
#include "Camera.h"
//ST: Voy a agregar nuevas lineas 
#include "Noise.h"
#include "cmodel/CModel.h"
//Solo para Visual Studio 2015
#if (_MSC_VER == 1900)
#   pragma comment( lib, "legacy_stdio_definitions.lib" )
#endif

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
static GLuint ciudad_display_list;	//Display List for the Monito


									//NEW// Keyframes
float posX = 0, posY = 2.5, posZ = -3.5, rotRodIzq = 0;
float giroMonito = 0;
float movBrazoDer = 0.0;
float movManoDer = 0.0;
// Camera

bool isometric = false;
float angle = 0.0f;

float lx = 0.0f, lz = -1.0f;

float x = 0.0f, z = 5.0f;


float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;
float up_view = 0.0f;
float eye_y = 1.8f;
//

#define MAX_FRAMES 9
int i_max_steps = 90;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float rotRodIzq;
	float rotInc;
	float giroMonito;
	float giroMonitoInc;
	float movBrazoDer;
	float movBrazoDerInc;


}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 5;			//introducir datos
bool play = false;
int playIndex = 0;


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 800, h = 800;
int frame = 0, time, timebase = 0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font = (int)GLUT_BITMAP_HELVETICA_18;

//Otras opciones son:
/*GLUT_BITMAP_8_BY_13
GLUT_BITMAP_9_BY_15
GLUT_BITMAP_TIMES_ROMAN_10
GLUT_BITMAP_TIMES_ROMAN_24
GLUT_BITMAP_HELVETICA_10
GLUT_BITMAP_HELVETICA_12
GLUT_BITMAP_HELVETICA_18*/



//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[] = { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = { 18 };

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = { 22 };

CTexture text1; //cielo azul
CTexture text2; //monito
CTexture text3;	//cemento
CTexture text4;	//barda UNAM
CTexture text5;	//Pasto
CTexture text6;	//pared piedra
CTexture text9; //pared blanca
CTexture text10; //pared con ventanas
CTexture text11; //piso azulejo
CTexture textMetal;//METAL DE COLORES<<Justina>>
CTexture tree;

CFiguras fig1; //cielo azul
CFiguras fig2; //
CFiguras fig3; //piso de cemento
CFiguras fig4; //Pasto
CFiguras fig5; //barda UNAM
CFiguras fig6; //pared (puede ser la que incluya ventanas
CFiguras fig7; //Para crear Monito
CFiguras fig8; //pared piedra
CFiguras fig9; //pared blanca
CFiguras fig10; //pared con ventanas
CFiguras fig11; //piso azulejo

				//Figuras de 3D Studio
				//Figuras de 3D Studio

CModel kit;

//Animación del coche
float angRot = 0.0;
float movKitX = 0.0;
float movKitZ = 0.0;
float rotKit = 0.0;
float rotTires = 0.0;
bool g_fanimacion = false;
bool g_avanza = false;

bool circuito = false;
bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = false;
bool recorrido4 = false;
bool recorrido5 = false;


void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
	KeyFrame[FrameIndex].giroMonito = giroMonito;
	KeyFrame[FrameIndex].movBrazoDer = movBrazoDer;

	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotRodIzq = KeyFrame[0].rotRodIzq;
	giroMonito = KeyFrame[0].giroMonito;
	movBrazoDer = KeyFrame[0].movBrazoDer;

}

void interpolation(void)
{
	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;
	KeyFrame[playIndex].giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;
	KeyFrame[playIndex].movBrazoDerInc = (KeyFrame[playIndex + 1].movBrazoDer - KeyFrame[playIndex].movBrazoDer) / i_max_steps;

}

void ciudad()
{
	//COMIENZA EL SUELO
	glPushMatrix();//piso de cemento
	glTranslatef(-19, 0, 12.5);//x,arriba,y
	glScalef(10, 0.01, 15);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig3.prisma2(text3.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//piso de cemento
	glTranslatef(-29, 0, 17.5);//x,arriba,y
	glScalef(10, 0.01, 5);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig3.prisma2(text3.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//piso de cemento
	glTranslatef(-19, 0, -2.5);//x,arriba,y
	glScalef(10, 0.01, 15);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig3.prisma2(text3.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	
	glPushMatrix();//pasto
	glTranslatef(-29, 0, 10);//x,arriba,y
	glScalef(10, 0.01, 10);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig4.prisma2(text5.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//barda UNAM
	glTranslatef(-29, 0.3, 15);//x,arriba,y
	glScalef(10.1, 0.4, 0.8);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig5.prisma2(text4.GLindex, text4.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//barda UNAM
	glTranslatef(-24, 0.3, 10.2);//x,arriba,y
	glScalef(0.8, 0.4, 10.4);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig5.prisma2(text4.GLindex, text4.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//barda UNAM
	glTranslatef(-24, 0.3, -2.5);//x,arriba,y
	glScalef(0.8, 0.4, 15);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig5.prisma2(text4.GLindex, text4.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//pared piedras
	glTranslatef(-29.2, 2.2, 1);//x,arriba,y
	glScalef(9.7, 5, 8);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig8.prisma2(text6.GLindex, text6.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//pared piedras
	glTranslatef(-29.2, 7, 1);//x,arriba,y
	glScalef(9.7, 5, 8);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig8.prisma2(text6.GLindex, text6.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//pared piedras
	glTranslatef(-29.2, 2.2, -7);//x,arriba,y
	glScalef(9.7, 5, 8);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig8.prisma2(text6.GLindex, text6.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//pared piedras
	glTranslatef(-29.2, 7, -7);//x,arriba,y
	glScalef(9.7, 5, 8);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig8.prisma2(text6.GLindex, text6.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//pared piedras
	glTranslatef(-19.2, 2.2, -13);//x,arriba,y
	glScalef(10.3, 5, 6);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig8.prisma2(text6.GLindex, text6.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//pared piedras
	glTranslatef(-19.2, 7, -13);//x,arriba,y
	glScalef(10.3, 5, 6);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig8.prisma2(text6.GLindex, text6.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//piso de cemento
	glTranslatef(-10, 0, -10.5);//x,arriba,y
	glScalef(8, 0.01, 11);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig3.prisma2(text3.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//pared
	glTranslatef(-2.9, 1, -10.5);//x,arriba,y
	glScalef(6, 3, 11);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig9.prisma2(text9.GLindex, text9.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//pared con ventanas
	glTranslatef(-2.9, 5, -10.5);//x,arriba,y
	glScalef(6, 5, 11);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig9.prisma2(text9.GLindex, text9.GLindex);//fig10,text10
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//pared ancha
	glTranslatef(-7, 1.9, 5);//x,arriba,y
	glScalef(14, 5, 20);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig9.prisma2(text9.GLindex, text9.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//pared ancha
	glTranslatef(-7, 1.9, 30);//x,arriba,y
	glScalef(14, 5, 20);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig9.prisma2(text9.GLindex, text9.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//barda UNAM
	glTranslatef(-24, 0.3, 25.2);//x,arriba,y
	glScalef(0.8, 0.4, 10.4);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig5.prisma2(text4.GLindex, text4.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//barda UNAM
	glTranslatef(-28.8, 0.3, 19.8);//x,arriba,y
	glScalef(10.4, 0.4, 0.8);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig5.prisma2(text4.GLindex, text4.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//pasto
	glTranslatef(-29, 0, 25);//x,arriba,y
	glScalef(10, 0.01, 10);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig4.prisma2(text5.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//pasto
	glTranslatef(-29, 0, 35);//x,arriba,y
	glScalef(10, 0.01, 10);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig4.prisma2(text5.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//barda UNAM
	glTranslatef(-24, 0.3, 35.9);//x,arriba,y
	glScalef(0.8, 0.4, 14.4);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig5.prisma2(text4.GLindex, text4.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//piso de cemento
	glTranslatef(-19, 0, 26.5);//x,arriba,y
	glScalef(10, 0.01, 13);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig3.prisma2(text3.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//piso de cemento
	glTranslatef(-19, 0, 36.5);//x,arriba,y
	glScalef(10, 0.01, 13);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig3.prisma2(text3.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//pasto
	glTranslatef(-29, 0, 41.5);//x,arriba,y
	glScalef(10, 0.01, 3);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig4.prisma2(text5.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//piso azulejo
	glTranslatef(19, 0, 26.5);//x,arriba,y
	glScalef(5, 0.01, 5);//largo,grosor,ancho
	glDisable(GL_LIGHTING);
	fig11.prisma2(text11.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();


}


void riel()
{
	glPushMatrix();
	glTranslatef(-10, 0, 30);//x,arriba,y
	glScalef(10, 0.5, 10);//largo,grosor,alto
	glDisable(GL_LIGHTING);
	fig6.prisma2(text3.GLindex, text3.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}


void arbol_alpha()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glBindTexture(GL_TEXTURE_2D, tree.GLindex);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_LIGHTING);

	glPopMatrix();
}

void arbol_blend()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);     // Turn Blending On
							//glDisable(GL_DEPTH_TEST);   // Turn Depth Testing Off
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, tree.GLindex);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);        // Turn Blending Off
								//glEnable(GL_DEPTH_TEST);    // Turn Depth Testing On
	glEnable(GL_LIGHTING);
}
//Todavía no acabo (Justina parte derecha)
void monito()
{
	//glNewList(1, GL_COMPILE);
	glPushMatrix();//Pecho
	glScalef(0.25, 0.25, 0.25); 
	glDisable(GL_LIGHTING);
	fig7.prisma(2.0, 1.5, 1, textMetal.GLindex);
	glEnable(GL_LIGHTING);

	   glPushMatrix();//Cuello
	     glTranslatef(0, 1, 0.0);
	     fig7.cilindro(0.25, 0.25, 15, textMetal.GLindex);
	        glPushMatrix();//Cabeza
	        glTranslatef(0,1, 0);
	        fig7.esfera(0.75, 15, 15, textMetal.GLindex);
	        glPopMatrix();
	   glPopMatrix();

           	glPushMatrix(); //Brazo derecho-->
	        glTranslatef(1, 0.85, 0);
	        fig7.esfera(0.25, 12, 12, textMetal.GLindex);//--->Hombro
	            glPushMatrix();
	                glTranslatef(0.25, 0, 0);
	                glRotatef(movBrazoDer, 0.0, 0.0, 1.0);
	                glRotatef(-45, 0, 1, 0);
	                glTranslatef(0.5, 0, 0);
	                fig7.prisma(0.45, 0.85, 0.45, textMetal.GLindex);//--->Brazo
	            glPopMatrix();
				glPushMatrix();
				   glTranslatef(0.55, 0, 0.25);
				   glRotatef(movBrazoDer, 0.0, 0.0, 1.0);
				   glRotatef(-45, 0, 1, 0);
				   glTranslatef(0.75, 0, 0);
				   fig7.esfera(0.25,12,12, textMetal.GLindex);//--->Codo
				glPopMatrix();
				glPushMatrix();
				   glTranslatef(1.2, 0, 0.78);
				   glRotatef(movBrazoDer, 0.0, 0.0, 1.0);
				   glRotatef(-45, 0, 1, 0);
				   glTranslatef(0.5, 0, 0);
				   fig7.prisma(0.45, 0.85, 0.45, textMetal.GLindex);//--->Antebrazo
				glPopMatrix();
				glPushMatrix();
				   glTranslatef(1.45, 0, 1);
				   glRotatef(movBrazoDer, 0.0, 0.0, 1.0);
				   glRotatef(-45, 0, 1, 0);
				   glTranslatef(0.75, 0, 0);
				   fig7.esfera(0.25, 12, 12, textMetal.GLindex);//--->Muñeca
				glPopMatrix();
	glPushMatrix();
				   glTranslatef(1.7, 0, 1.28);
	
				   glRotatef(movManoDer, 0.0, 0.0, 1.0);
				   glRotatef(-95, 0, 1, 0);
				   glTranslatef(0.5, 0, 0);
				   fig7.prisma(0.45, 0.35, 0.15, textMetal.GLindex);//--->Pinza 1
				glPopMatrix();
				glPushMatrix();
				   glTranslatef(1.7, 0, 1.28);
				   glRotatef(movManoDer, 0.0, 0.0, 1.0);
				   glRotatef(15, 0, 1, 0);
				   glTranslatef(0.5, 0, 0);
				   fig7.prisma(0.45, 0.35, 0.15, textMetal.GLindex);//--->Pinza 2
				glPopMatrix();
	       

	        glPopMatrix();

		glPushMatrix();
			   glTranslatef(-1, 0.85, 0);
			   fig7.esfera(0.25, 12, 12, textMetal.GLindex);//--->Hombro
			   glPushMatrix();
			       glTranslatef(0.05, 0, 0);
			       glRotatef(45, 0, 1, 0);
			       glRotatef(25, 0, 0, 1);
			       glRotatef(25, 1, 0, 0);
			       glTranslatef(-0.75, 0, 0);
			       fig7.prisma(0.45, 0.85, 0.45, textMetal.GLindex);//--->Brazo
			   glPopMatrix();
			   glPushMatrix();
			       glTranslatef(-0.25, -0.15, 0.45);
			       glRotatef(45, 0, 1, 0);
			       glRotatef(25, 0, 0, 1);
			       glRotatef(25, 1, 0, 0);
			       glTranslatef(-0.75, 0, 0);
			       fig7.esfera(0.25, 12, 12, textMetal.GLindex);//--->Brazo
			   glPopMatrix();
			glPopMatrix();

	glPushMatrix();//Cintura
	
	glTranslatef(0, -2, 0);
	glDisable(GL_LIGHTING);
	fig7.prisma(2.0, 0.75, 1, textMetal.GLindex);
	glEnable(GL_LIGHTING);


	glPushMatrix(); //Base
	glTranslatef(0, -1, 0);
	fig7.prisma(0.2, 1.2, 1.5, textMetal.GLindex);
	glPopMatrix();

	
	glPopMatrix();


	glColor3f(1, 1, 1);
	glPopMatrix();
	//glEndList();
}


GLuint createDL()
{
	GLuint ciudadDL;
	//GLuint cieloDL;

	// Create the id for the list
	ciudadDL = glGenLists(1);
	// start list
	glNewList(ciudadDL, GL_COMPILE);
	// call the function that contains 
	// the rendering commands
	ciudad();
	//monito();
	// endList
	glEndList();

	return(ciudadDL);
}
//Para el Mouse
void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;

		// update camera's 
		lx = sin(angle + deltaAngle);

		//lx = 1;
		lz = -cos(angle + deltaAngle);
	}
}

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else {// state = GLUT_DOWN
			xOrigin = x;
		}
	}
}
void InitGL(GLvoid)     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
	//Para construir la figura comentar esto
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Position2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);

	//glEnable ( GL_COLOR_MATERIAL );
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glPolygonMode(GL_BACK, GL_LINE);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/* setup blending */
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE);			// Set The Blending Function For Translucency
	//glColor4f(1.0f, 1.0f, 1.0f, 0.5); 

	text1.LoadBMP("01.bmp"); //ambiente azul con cielo
	text1.BuildGLTexture();
	text1.ReleaseImage();

	text3.LoadTGA("city/cemento.tga"); //piso de cemento
	text3.BuildGLTexture();
	text3.ReleaseImage();

	text4.LoadTGA("city/barda.tga"); //barda amarilla UNAM
	text4.BuildGLTexture();
	text4.ReleaseImage();

	text5.LoadTGA("city/pasto01.tga"); //jardin de pasto
	text5.BuildGLTexture();
	text5.ReleaseImage();

	text6.LoadTGA("city/piedra.tga"); //pared de piedra
	text6.BuildGLTexture();
	text6.ReleaseImage();

	text9.LoadTGA("city/pared.tga"); //pared blanca
	text9.BuildGLTexture();
	text9.ReleaseImage();

	text10.LoadTGA("city/ventanas.tga"); //pared con ventanas
	text10.BuildGLTexture();
	text10.ReleaseImage();

	text11.LoadTGA("city/azulejo.tga"); //piso azulejo
	text11.BuildGLTexture();
	text11.ReleaseImage();
	
	textMetal.LoadTGA("city/metalc.tga");
	textMetal.BuildGLTexture();
	textMetal.ReleaseImage();


	tree.LoadTGA("Tree.tga"); //arbol de escenario
	tree.BuildGLTexture();
	tree.ReleaseImage();

	kit._3dsLoad("kitt.3ds");
	//kit.VertexNormals();


	objCamera.Position_Camera(0, 2.5f, 3, 0, 2.5f, 0, 0, 1, 0);

	//NEW Crear una lista de dibujo
	ciudad_display_list = createDL();

	//NEW Iniciar variables de KeyFrames
	/*for(int i=0; i<MAX_FRAMES; i++)
	{
	KeyFrame[i].posX =0;
	KeyFrame[i].posY =0;
	KeyFrame[i].posZ =0;
	KeyFrame[i].incX =0;
	KeyFrame[i].incY =0;
	KeyFrame[i].incZ =0;
	KeyFrame[i].rotRodIzq =0;
	KeyFrame[i].rotInc =0;
	KeyFrame[i].giroMonito =0;
	KeyFrame[i].giroMonitoInc =0;
	KeyFrame[i].giroBrazo =0;
	KeyFrame[i].giroBrazoInc = 0;

	}*/

	KeyFrame[0].posX = 0;
	KeyFrame[0].posY = 2.5;
	KeyFrame[0].posZ = -3.5;
	KeyFrame[0].rotRodIzq = 0;
	KeyFrame[0].giroMonito = 0;
	KeyFrame[0].movBrazoDer = 0;

	KeyFrame[1].posX = 20;
	KeyFrame[1].posY = 2.5;
	KeyFrame[1].posZ = -3.5;
	KeyFrame[1].rotRodIzq = 60;
	KeyFrame[1].giroMonito = -90.0;
	KeyFrame[1].movBrazoDer = 40;

	KeyFrame[2].posX = 20;
	KeyFrame[2].posY = 2.5;
	KeyFrame[2].posZ = 4.0;
	KeyFrame[2].rotRodIzq = -20.0;
	KeyFrame[2].giroMonito = 0;
	KeyFrame[2].movBrazoDer = 0;

	KeyFrame[3].posX = 20;
	KeyFrame[3].posY = 2.5;
	KeyFrame[3].posZ = 4.0;
	KeyFrame[3].rotRodIzq = 40.0;
	KeyFrame[3].giroMonito = 45;
	KeyFrame[3].movBrazoDer = 90;

	KeyFrame[4].posX = 20;
	KeyFrame[4].posY = 2.5;
	KeyFrame[4].posZ = 4.0;
	KeyFrame[4].rotRodIzq = -40.0;
	KeyFrame[4].giroMonito = -45;
	KeyFrame[4].movBrazoDer = -90;
	//NEW//////////////////NEW//////////////////NEW//////////////////

}

void pintaTexto(float x, float y, float z, void *font, char *string)
{

	char *c;     //Almacena los caracteres a escribir
	glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
							//glWindowPos2i(150,100);
	for (c = string; *c != '\0'; c++) //Condicion de fin de cadena
	{
		glutBitmapCharacter(font, *c); //imprime
	}
}

void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();


	glPushMatrix();

	glRotatef(g_lookupdown, 1.0f, 0, 0);

	gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
		objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
		objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);


	glPushMatrix();
	glPushMatrix(); //Creamos cielo
	glDisable(GL_LIGHTING);
	glTranslatef(0, 60, 0);
	fig1.skybox(130.0, 130.0, 130.0, text1.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1, 1, 1);
	//glScalef(0.5, 0.5, 0.5);
	//monito();
	glCallList(ciudad_display_list);
	glTranslatef(posX, posY, posZ);
	glRotatef(giroMonito, 0, 1, 0);
	//monito();
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glScalef(0.3, 0.3, 0.3);



	glTranslatef(movKitX, 4, movKitZ);
	glRotatef(rotKit, 0, 1, 0);

	
	glPopMatrix();
	

	glPushMatrix();
	//glTranslatef(-30, 0, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-30, 0, 10);
	arbol_alpha();
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);

	glPopMatrix();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 0.0, 0.0);
	pintaTexto(-11, 12.0, -14.0, (void *)font, "PROYECTO FINAL");
	//pintaTexto(-11,10.5,-14,(void *)font,"Listas de Dibujo");
	pintaTexto(-11, 8.5, -14, (void *)font, s);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glutSwapBuffers();

}

void animacion()
{
	fig3.text_izq -= 0.01;
	fig3.text_der -= 0.01;
	if (fig3.text_izq<-1)
		fig3.text_izq = 0;
	if (fig3.text_der<0)
		fig3.text_der = 1;

	//Movimiento del coche
	if (g_fanimacion)
	{
		if (g_avanza)
		{
			movKitZ += 1.0;
			rotTires -= 10;
			if (movKitZ>130)
				g_avanza = false;
		}
		else
		{
			movKitZ -= 1.0;
			rotTires += 10;
			if (movKitZ<0)
				g_avanza = true;
		}
	}

	if (circuito)
	{
		if (recorrido1)
		{
			movKitZ++;
			if (movKitZ>155)
			{
				recorrido1 = false;
				recorrido2 = true;
			}
		}
		if (recorrido2)
		{
			rotKit = 90;
			movKitX++;
			if (movKitX > 125)
			{
				recorrido2 = false;
				recorrido3 = true;

			}
		}
		if (recorrido3)
		{
			rotKit = 180;
			movKitZ--;
			if (movKitZ<-155)
			{
				recorrido3 = false;
				recorrido4 = true;
			}
		}
		if (recorrido4)
		{
			rotKit = 270;
			movKitX--;
			if (movKitX<0)
			{
				recorrido4 = false;
				recorrido5 = true;
			}
		}
		if (recorrido5)
		{
			rotKit = 0;
			movKitZ++;
			if (movKitZ>0)
			{
				recorrido5 = false;
				recorrido1 = true;
			}
		}
	}


	//Movimiento del monito
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex>FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += KeyFrame[playIndex].incX;
			posY += KeyFrame[playIndex].incY;
			posZ += KeyFrame[playIndex].incZ;

			rotRodIzq += KeyFrame[playIndex].rotInc;
			giroMonito += KeyFrame[playIndex].giroMonitoInc;
			movBrazoDer += KeyFrame[playIndex].movBrazoDerInc;

			i_curr_steps++;
		}

	}

	/*frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
	sprintf(s,"FPS:%4.2f",frame*1000.0/(time-timebase));
	timebase = time;
	frame = 0;
	}*/

	glutPostRedisplay();
}

void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista

	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {

	case 'w':   //Movimientos de camara
	case 'W':
		objCamera.Move_Camera(CAMERASPEED + 0.2);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.2));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.4));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.4);
		break;

	case 'O':		//  
	case 'o':
		g_fanimacion ^= true; //Activamos/desactivamos la animacíon
		circuito = false;
		break;

	case 'i':		//  
	case 'I':
		circuito ^= true; //Activamos/desactivamos la animacíon
		g_fanimacion = false;
		break;

	case 'k':		//
	case 'K':
		if (FrameIndex<MAX_FRAMES)
		{
			saveFrame();
		}

		break;

	case 'l':
	case 'L':
		if (play == false && (FrameIndex>1))
		{

			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;

	case 'y':
	case 'Y':
		posZ++;
		//printf("%f \n", posZ);
		break;

	case 'g':
	case 'G':
		posX--;
		//printf("%f \n", posX);
		break;

	case 'h':
	case 'H':
		posZ--;
		//printf("%f \n", posZ);
		break;

	case 'j':
	case 'J':
		posX++;
		//printf("%f \n", posX);
		break;

	case 'b':
		rotRodIzq++;
		//printf("%f \n", rotRodIzq);
		break;

	case 'B':
		rotRodIzq--;
		//printf("%f \n", rotRodIzq);
		break;

	case 'p':
		giroMonito++;
		//printf("%f \n", giroMonito);
		break;

	case 'P':
		giroMonito--;
		//printf("%f \n", giroMonito);
		break;

	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}

	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_PAGE_UP:
		//pos_camY -= 0.5f;
		//pos_cam.y += 0.5f;
		//eye_cam.y += 0.5f;
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		//pos_camY += 0.5f;
		//pos_cam.y -= 0.5f;
		//eye_cam.y -= 0.5f;
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

	case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

	case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View(CAMERASPEED);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void menuKeyFrame(int id)
{
	switch (id)
	{
	case 0:	//Save KeyFrame
		if (FrameIndex<MAX_FRAMES)
		{
			saveFrame();
		}
		break;

	case 1:	//Play animation
		if (play == false && FrameIndex >1)
		{

			resetElements();
			//First Interpolation
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;


	}
}


void menu(int id)
{

}

int main(int argc, char** argv)   // Main Function
{
	int submenu;
//Para musica de fondo
	PlaySound(TEXT("Sound.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize(500, 500);	// Tamaño de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("PROYECTO FINAL"); // Nombre de la Ventana
									 //glutFullScreen     ( );         // Full Screen
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut función de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut función en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut función de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	glutIdleFunc(animacion);

	submenu = glutCreateMenu(menuKeyFrame);
	glutAddMenuEntry("Guardar KeyFrame", 0);
	glutAddMenuEntry("Reproducir Animacion", 1);
	glutCreateMenu(menu);
	glutAddSubMenu("Animacion Monito", submenu);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();          // 

	return 0;
}
