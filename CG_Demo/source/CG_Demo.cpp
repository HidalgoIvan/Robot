/*
 * Teacher: Sergio Ruiz.
 * Ernesto Iván Ochoa Hidalgo A01651425
 * Ana Karen Campos A01335037
 * Luis Alejandro Peña Montoya A01650535
 * Arturo Fischer Garza A01334880
 * TC3022. Computer Graphics Course.
 * Basic template OpenGL project.
 */

// Please don't change lines 9-22 (It helps me to grade)
#ifdef __APPLE__
	// For XCode only: New C++ terminal project. Build phases->Compile with libraries: add OpenGL and GLUT
	// Import this whole code into a new C++ file (main.cpp, for example). Then run.
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#else
	// For VS only: Download CG_Demo.zip. UNZIP FIRST. Double click on CG_Demo/CG_Demo.sln
	// Run
	#include "glew.h"
	#include "freeglut.h"
	#include <stdio.h>
	#include <math.h>
	#include "hCube.h"
	#include "hPiece.h"
	#include <string>
	#include<iostream>
#endif
#define NOP 1000

#include <vector>
#include "cParticle.h"
Particle* armCollider;
Particle* collidingParticles[NOP];
Vector3* baseColor = new Vector3(((float)rand() / (float)(RAND_MAX)), ((float)rand() / (float)(RAND_MAX)), ((float)rand() / (float)(RAND_MAX)));
using namespace std;

vector<Particle*> LOP; //lots of particles
GLfloat* light0_position;
Piece* base1;
Piece* base2;
Piece* base3;
GLfloat		rotation;
GLfloat*	mat0_specular;
GLfloat*	mat0_diffuse;
GLfloat*	mat0_shininess;
std::string hud;
char toMove = '1';
float up_down[4] = { 0,0,0,0 };
float axis[4] = { 0,0,0,0 };
bool rectify = false;
void drawBitmapText(char *string, float x, float y, float z)
{
	char *c;
	glRasterPos3f(x, y, z);
	glColor3f(1,1,1);
	for (c = string; *c != '*'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}
void MenuHandler(char key) {
	switch (key)
	{
	case '1':
		toMove = '1';
		break;
	case '2':
		toMove = '2';
		break;
	case '3':
		toMove = '3';
		break;
	case '4':
		toMove = '4';
		break;
	case '5':
		rectify = true;
		break;
	case 'w':
		armCollider->forces->z -= 20.0f;
		if (toMove == '1')
		{
			up_down[0] -= 10;
		}
		if (toMove == '2' && up_down[1] > -90.0f)
		{
			up_down[1] -= 10;
		}
		if (toMove == '3' && up_down[2] > -90.0f)
		{
			up_down[2] -= 10;
		}
		if (toMove == '4')
		{
			up_down[3] -= 10;
		}
		break;
	case 's':
		armCollider->forces->z += 20.0f;
		if (toMove == '1')
		{
			up_down[0] += 10;
		}
		if (toMove == '2' && up_down[1] < 90.0f)
		{
			up_down[1] += 10;
		}
		if (toMove == '3' && up_down[2] < 90.0f)
		{
			up_down[2] += 10;
		}
		if (toMove == '4')
		{
			up_down[3] += 10;
		}
		break;
	case 'a':
		armCollider->forces->x -= 20.0f;
		if (toMove == '1')
		{
			axis[0] += 10;
		}
		if (toMove == '2')
		{
			axis[1] += 10;
		}
		if (toMove == '3')
		{
			axis[2] += 10;
		}
		if (toMove == '4')
		{
			axis[3] += 10;
		}
		break;
	case 'd':
		armCollider->forces->x += 20.0f;
		if (toMove == '1')
		{
			axis[0] -= 10;
		}
		if (toMove == '2')
		{
			axis[1] -= 10;
		}
		if (toMove == '3')
		{
			axis[2] -= 10;
		}
		if (toMove == '4')
		{
			axis[3] -= 10;
		}
		break;
	};
}
void keyPressed(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'w': MenuHandler('w'); break;
	case 's': MenuHandler('s'); break;
	case 'a': MenuHandler('a'); break;
	case 'd': MenuHandler('d'); break;
	case 'k': MenuHandler('i'); break;
	case 'i': MenuHandler('k'); break;
	case '1': MenuHandler('1'); break;
	case '2': MenuHandler('2'); break;
	case '3': MenuHandler('3'); break;
	case '4': MenuHandler('4'); break;
	case '5': MenuHandler('5'); break;
	};
}
void init() // FOR GLUT LOOP
{
	for (int x = 0; x < 32; x++)
	{
		Particle* p1 = new Particle(new Vector3(((((float)rand() / (float)(RAND_MAX)) * 5) - 5), 5.0, ((((float)rand() / (float)(RAND_MAX)) * 5.0) - 5.0)), 1.0f);
		LOP.push_back(p1);
	}
	
	armCollider = new Particle(new Vector3(0.0f, 2.0f, 0.0f), 2.0f);
	//armCollider->isStatic = true;
	LOP.push_back(armCollider);
	glShadeModel(GL_SMOOTH);
	light0_position = new GLfloat[4];
	light0_position[0] = 1.0f;
	light0_position[1] = 1.0f;
	light0_position[2] = 1.0f;
	light0_position[3] = 1.0f;
	mat0_specular = new GLfloat[4];
	mat0_specular[0] = 1.0f;
	mat0_specular[1] = 1.0f; 
	mat0_specular[2] = 1.0f; 
	mat0_specular[3] = 1.0f;

	mat0_diffuse = new GLfloat[4];
	mat0_diffuse[0] = 1.0f; 
	mat0_diffuse[1] = 1.0f; 
	mat0_diffuse[2] = 1.0f; 
	mat0_diffuse[3] = 1.0f;

	mat0_shininess = new GLfloat[1];
	mat0_shininess[0] = 1.0f;

	// Posicionar LUZ 0:
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	// Habilitar iluminación:
	glEnable(GL_LIGHTING);
	// Habilitar LUZ 0:
	glEnable(GL_LIGHT0);

	base1 = new Piece("assets/base.obj");
	base2 = new Piece("assets/Pieza2.obj");
	base3 = new Piece("assets/Pieza2.obj");
	base1->isBase = true;
	base1->setSize(2,2,2);
	base2->setTranslation(0, 3.8f, 0);
	base2->setRotation(0, 0, 0);
	base2->setSize(4,4,4);
	base2->setRotationPivot(0,-2.8f,0);
	base1->setSon(base2);
	base3->setTranslation(0, 10.4f, 0);
	base3->setRotation(0, 0, 0);
	base3->setSize(4, 4, 4);
	base3->setRotationPivot(0, -2.8f, 0);
	base2->setSon(base3);
	/*base3 = new Cube();
	base3->setColor(55, 90, 20);//blanco
	base3->setSize(1.0f, 2.0f, 1.0f);
	base3->setTranslation(0, 2.0f, 0);
	base3->setRotation(0, 0, 0);
	base3->setRotationPivot(0, -1.0f, 0);
	base2->setSon(base3);
	base4 = new Cube();
	base4->setColor(155, 0, 120);//blanco
	base4->setSize(1.0f, 2.0f, 1.0f);
	base4->setTranslation(0, 2.0f, 0);
	base4->setRotation(0, 0, 0);
	base4->setRotationPivot(0, -1.0f, 0);
	base3->setSon(base4);*/

	//carga modelo
	
	glutKeyboardFunc(keyPressed);
	glEnable(GL_DEPTH_TEST);			// Enable check for close and far objects.
	glClearColor(0.0, 0.0, 0.0, 0.0);	// Clear the color state.
	glMatrixMode(GL_MODELVIEW);			// Go to 3D mode.
	glLoadIdentity();					// Reset 3D view matrix.
}

void checkCollisions() {
	vector<Particle*>::iterator pIt1;
	vector<Particle*>::iterator pIt2;

	bool pIt1crashed = false;
	Particle* particle1;
	Particle* particle2;
	int collidingIndex = 0;
	for (pIt1 = LOP.begin(); pIt1 != LOP.end(); pIt1++)
	{
		pIt1crashed = false;
		for (pIt2 = pIt1 + 1; pIt2 != LOP.end(); pIt2++)
		{
			if ((*pIt1)->checkCollision(*pIt2))
			{
				(*pIt1)->makeRed();
				(*pIt2)->makeRed();
			}
		}
	}
}
void display()							// Called for each frame (about 60 times per second).
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// Clear color and depth buffers.
	glLoadIdentity();												// Reset 3D view matrix.
	gluLookAt(15.0, 18.0,18.0,										// Where the camera is.
		      0.0, 4.0, 0.0,										// To where the camera points at.
		      0.0, 1.0, 0.0);										// "UP" vector.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	checkCollisions();
	glPushMatrix();
	{
		vector<Particle*>::iterator pIt;
		for (pIt = LOP.begin(); pIt != LOP.end(); pIt++) {
			if ((*pIt)->position->y > -10.0f)
			{
				(*pIt)->update(0.1);
				(*pIt)->draw();
			}
		}
	}
	glPopMatrix();

	// Indicar propiedades del material con el que vamos a dibujar:
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat0_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat0_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat0_shininess);
	base1->draw();
	base1->setRotation(0, axis[0], 0);
	base2->setRotation(up_down[1], 0, 0);
	base3->setRotation(up_down[2], 0, 0);
	//base3->setRotation(base3->rot_x, axis[2], up_down[2]);
	//base4->setRotation(base4->rot_x, axis[3], up_down[3]);
	//drawAxis();
	glColor3f(1, 1, 1);
	glPopMatrix();
	glutSwapBuffers();												// Swap the hidden and visible buffers.
																	// save previous matrix
	
}

void idle()															// Called when drawing is finished.
{
	if (rectify)
	{
		for (int x = 0; x < 4; x++)
		{
			if (axis[x] != 0)
			{
				axis[x] += -axis[x] / fabs(axis[x]);
				if ((int)axis[x] % 360 == 0)
				{
					axis[x] = 0;
				}
			}
			if (up_down[x] != 0)
			{
				up_down[x] += -up_down[x] / fabs(-up_down[x]);
				if ((int)up_down[x] % 360 == 0)
				{
					up_down[x] = 0;
				}
			}
		}
		for (int x = 0; x < 4; x++)
		{
			if (axis[x] != 0 || up_down[x] != 0)
			{
				rectify = true;
				break;
			}
			rectify = false;
		}
	}
	glutPostRedisplay();											// Display again.
}
void reshape(int h, int v)											// Called when the window geometry changes.
{
	glMatrixMode(GL_PROJECTION);									// Go to 2D mode.
	glLoadIdentity();												// Reset the 2D matrix.
	gluPerspective(40.0, (GLdouble)h / (GLdouble)v, 0.5, 50.0);		// Configure the camera lens aperture.
	glMatrixMode(GL_MODELVIEW);										// Go to 3D mode.
	glViewport(0, 0, h, v);											// Configure the camera frame dimensions.
	gluLookAt(0.0, 1.0, 4.0,
		      0.0, 0.0, 0.0,
		      0.0, 1.0, 0.0);
	display();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);											// Init GLUT with command line parameters.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);		// Use 2 buffers (hidden and visible). Use the depth buffer. Use 3 color channels.
	glutInitWindowSize(800, 600);
	glutCreateWindow("CG TEST");
	hud.append("Now controlling piece 1");
	hud.append("*");
	char* toPrint = new char[hud.length() + 1];
	strcpy(toPrint, hud.c_str());
	drawBitmapText(toPrint, 0, 0, 0);
	init();
	glutReshapeFunc(reshape);										// Reshape CALLBACK function.
	glutDisplayFunc(display);										// Display CALLBACK function.
	glutIdleFunc(idle);												// Idle CALLBACK function.
	glutMainLoop();													// Begin graphics program.
	return 0;														// ANSI C requires a return value.
}
