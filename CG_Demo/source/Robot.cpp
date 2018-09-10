#include "Robot.h"
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
#include "Cube.h"
#endif
Cube* head;
Cube* neck;
Cube* body1;
Cube* body2;
Cube* body3;
Cube* armL1;
Cube* armL2;
Cube* foreArmL;
Cube* handL;
Cube* armR1;
Cube* armR2;
Cube* foreArmR;
Cube* handR;
Robot::Robot()
{
}
float bobbing = 0.0f;
float bobbingStep = .02f;
void init() // FOR GLUT LOOP
{
	glEnable(GL_DEPTH_TEST);			// Enable check for close and far objects.
	glClearColor(0.8, 0.8, 0.8, 0.0);	// Clear the color state.
	glMatrixMode(GL_MODELVIEW);			// Go to 3D mode.
	glLoadIdentity();					// Reset 3D view matrix.
	/*
	->setColor(169, 169, 169);
	->setScale(2.3f, 1, 1.5f);
	->setPosition(0, 0, 0);
	->setRotation(0, 0, 0);
	*/
	//Head
	head = new Cube();
	head->setColor(30, 144, 255);//Azul
	head->setScale(.8f, .8f, .8f);
	head->setPosition(0, 3.6f, 0);
	head->setRotation(0, 0, 0);
	//Neck
	neck = new Cube();
	neck->setColor(240, 240, 240);
	neck->setScale(.6f, .4f, .6f);
	neck->setPosition(0, 3.2f, 0);
	neck->setRotation(0, 0, 0);
	//Torso
	body1 = new Cube();
	body1->setColor(169, 169, 169);//Gris
	body1->setScale(2.3f, 1, 1.5f);
	body1->setPosition(0, 0, 0);
	body1->setRotation(0, 0, 0);
	body2 = new Cube();
	body2->setColor(240, 240, 240);//Blanco
	body2->setScale(2, 1.2f, 1.2f);
	body2->setPosition(0, 1.1f, 0);
	body2->setRotation(0, 0, 0);
	body3 = new Cube();
	body3->setColor(202, 0, 42);//Rojo
	body3->setScale(2.7f, 1.3f, 1.6f);
	body3->setPosition(0, 2.35f, 0);
	body3->setRotation(0, 0, 0);
	//Left arm
	armL1 = new Cube();
	armL1->setColor(202, 0, 42);//Rojo
	armL1->setScale(.8f, .65f, .8f);
	armL1->setPosition(1.75f, 2.675f, 0);
	armL1->setRotation(0, 0, 0);
	armL2 = new Cube();
	armL2->setColor(240, 240, 240);//Blanco
	armL2->setScale(.6f, .65f, .6f);
	armL2->setPosition(1.75f, 2.025f, 0);
	armL2->setRotation(0, 0, 0);
	foreArmL = new Cube();
	foreArmL->setColor(202, 0, 42);//Rojo
	foreArmL->setScale(.8f, 1.45f, .8f);
	foreArmL->setPosition(1.75f, .975f, 0);
	foreArmL->setRotation(0, 0, 0);
	handL = new Cube();
	handL->setColor(30, 144, 255);//Azul
	handL->setScale(.65f, .65, .65f);
	handL->setPosition(1.75f, -.075f, 0);
	handL->setRotation(0, 0, 0);
	//Right arm
	armR1 = new Cube();
	armR1->setColor(202, 0, 42);//Rojo
	armR1->setScale(.8f, .65f, .8f);
	armR1->setPosition(-1.75f, 2.675f, 0);
	armR1->setRotation(0, 0, 0);
	armR2 = new Cube();
	armR2->setColor(240, 240, 240);//Blanco
	armR2->setScale(.6f, .65f, .6f);
	armR2->setPosition(-1.75f, 2.025f, 0);
	armR2->setRotation(0, 0, 0);
	foreArmR = new Cube();
	foreArmR->setColor(202, 0, 42);//Rojo
	foreArmR->setScale(.8f, 1.45f, .8f);
	foreArmR->setPosition(-1.75f, .975f, 0);
	foreArmR->setRotation(0, 0, 0);
	handR = new Cube();
	handR->setColor(30, 144, 255);//Azul
	handR->setScale(.65f, .65, .65f);
	handR->setPosition(-1.75f, -.075f, 0);
	handR->setRotation(0, 0, 0);
}

void display()							// Called for each frame (about 60 times per second).
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// Clear color and depth buffers.
	glLoadIdentity();												// Reset 3D view matrix.
	gluLookAt(0, 2.6f, 10,										// Where the camera is.
		0, 2.6f, 0.0,										// To where the camera points at.
		0.0, 1.0, 0.0);										// "UP" vector.
	glPointSize(5);
	glPushMatrix();
	{
		glTranslatef(0, bobbing, 0);
		head->draw();
		neck->draw();
		body1->draw();
		body2->draw();
		body3->draw();
		armL1->draw();
		armL2->draw();
		glPushMatrix();
		{
			glRotatef(-3, 0, 0, 1);
			foreArmL->draw();
			handL->draw();
		}
		glPopMatrix();
		armR1->draw();
		armR2->draw();
		glPushMatrix();
		{
			glRotatef(3, 0, 0, 1);
			foreArmR->draw();
			handR->draw();
		}
		glPopMatrix();
	}
	glPopMatrix();
	glutSwapBuffers();												// Swap the hidden and visible buffers.
}

void idle()															// Called when drawing is finished.
{
	bobbing += bobbingStep;
	if (bobbing > .3f || bobbing < -.3f) 
	{
		bobbingStep = -bobbingStep;
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
	gluLookAt(0.0, 13.0, 13.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);
	display();
}

int Robot::run(int argc, char* argv[])
{
	glutInit(&argc, argv);											// Init GLUT with command line parameters.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);		// Use 2 buffers (hidden and visible). Use the depth buffer. Use 3 color channels.
	glutInitWindowSize(800, 600);
	glutCreateWindow("CG TEST");
	init();
	glutReshapeFunc(reshape);										// Reshape CALLBACK function.
	glutDisplayFunc(display);										// Display CALLBACK function.
	glutIdleFunc(idle);												// Idle CALLBACK function.
	glutMainLoop();													// Begin graphics program.
	return 0;														// ANSI C requires a return value.
}
