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
Cube* legL;
Cube* pantL;
Cube* footL;
Cube* legR;
Cube* pantR;
Cube* footR;
Cube* plane;
Robot::Robot()
{
}
float bobbing = 0.0f;
float bobbingStep = .02f;
float rotationGlobal = 0.0f;
float rotationStep = 1.7f;
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
	//Top spotlight
	glShadeModel(GL_SMOOTH);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 0.0, 5.0, 0.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	//Front-ish spotlight
	glEnable(GL_LIGHT1);
	GLfloat light_position2[] = { 1.0, 1.0, 7.0, 0.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
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
	armL2->setPosition(1.75f, 3.325f, 0);
	armL2->setRotation(0, 0, 0);
	foreArmL = new Cube();
	foreArmL->setColor(202, 0, 42);//Rojo
	foreArmL->setScale(.8f, 1.45f, .8f);
	foreArmL->setPosition(1.75f, 4.375f, 0);
	foreArmL->setRotation(0, 0, 0);
	handL = new Cube();
	handL->setColor(30, 144, 255);//Azul
	handL->setScale(.65f, .65f, .65f);
	handL->setPosition(1.75f, 5.425f, 0);
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
	foreArmR->setPosition(-1.75f, 1.1f, 0);
	foreArmR->setRotation(0, 0, 0);
	handR = new Cube();
	handR->setColor(30, 144, 255);//Azul
	handR->setScale(.65f, .65, .65f);
	handR->setPosition(-1.75f, 0.075f, 0);
	handR->setRotation(0, 0, 0);
	//left leg
	glRotatef(rotationGlobal,1,0,0);
	legL = new Cube();
	legL->setColor(240, 240, 240);//Blanco
	legL->setScale(.9f, 2.0f, .9f);
	legL->setPosition(0.65f, -1.5f, 0);
	legL->setRotation(0, 0, 0);

	pantL = new Cube();
	pantL->setColor(30, 144, 255);//Azul
	pantL->setScale(1.0f, 2.0f, 1.0f);
	pantL->setPosition(0.65f, -3.5f, 0);
	pantL->setRotation(0, 0, 0);

	footL = new Cube();
	footL->setColor(30, 144, 255);//Azul
	footL->setScale(1.0f, 0.5f, 1.5f);
	footL->setPosition(0.65f, -4.75f, 0.25f);
	footL->setRotation(0, 0, 0);
	//right leg
	legR = new Cube();
	legR->setColor(240, 240, 240);//Blanco
	legR->setScale(.9f, 2.0f, .9f);
	legR->setPosition(-0.65f, -1.5f, 0);
	legR->setRotation(0, 0, 0);

	pantR = new Cube();
	pantR->setColor(30, 144, 255);//Azul
	pantR->setScale(1.0f, 2.0f, 1.0f);
	pantR->setPosition(-0.65f, -3.5f, 0);
	pantR->setRotation(0, 0, 0);

	footR = new Cube();
	footR->setColor(30, 144, 255);//Azul
	footR->setScale(1.0f, 0.5f, 1.5f);
	footR->setPosition(-0.65f, -4.75f, 0.25f);
	footR->setRotation(0, 0, 0);

	plane = new Cube();
	plane->setColor(4, 2, 0);
	plane->setScale(80.0f, .2f, 80.0f);
	plane->setPosition(0, -5.9f, 0);
	plane->setRotation(0, 0, 0);
}

void display()							// Called for each frame (about 60 times per second).
{
	printf("%f		%f		\n",rotationGlobal, rotationStep);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// Clear color and depth buffers.
	glLoadIdentity();												// Reset 3D view matrix.
	gluLookAt(10.0f, 10.0f, 10.0f,										// Where the camera is.
		0, -2.0f, 0.0,										// To where the camera points at.
		0.0, 1.0, 0.0);										// "UP" vector.
	glPointSize(5);
	plane->draw();
	glPushMatrix();
	{
		glTranslatef(0, rotationGlobal / 200.0f, 0);
		head->draw();
		neck->draw();
		glPushMatrix();
		{
			glRotatef(rotationGlobal / 6.0f, 0, 1, 0);
			body1->draw();
		}
		glPopMatrix();
		body2->draw();
		glPushMatrix();
		{
			glRotatef(rotationGlobal / 3.0f, 0, 1, 0);
			body3->draw();
			//Left arm
			glPushMatrix();
			{
				glTranslatef(-1.75f, 2.675, 0);
				glRotatef(180, 1, 0, 0);
				glRotatef(rotationGlobal / 3.0f, 1, 0, 0);
				glTranslatef(1.75f, -2.675f, 0);
				armL1->draw();
				armL2->draw();
				glTranslatef(0,1.45f,0);
				glRotatef(-10,1,0,0);
				glRotatef(10, 0, 0, 1);
				glTranslatef(.4f, -1.9f, .35f);
				foreArmL->draw();
				handL->draw();
			}
			glPopMatrix();
			//Right arm
			glPushMatrix();
			{
				glTranslatef(1.75f, 2.675, 0);
				glRotatef(-rotationGlobal / 3.0f, 1, 0, 0);
				glTranslatef(-1.75f, -2.675f, 0);
				armR1->draw();
				armR2->draw();
				glTranslatef(0, -1.45f, 0);
				glRotatef(-10,1,0,0);
				glRotatef(10, 0, 0, 1);
				glTranslatef(.47f, 1.45f, .5f);
				foreArmR->draw();
				handR->draw();
			}
			glPopMatrix();
		}
		glPopMatrix();
		//Legs
		glPushMatrix();
		{
			glRotatef(rotationGlobal, 1, 0, 0);
			legL->draw();
			glPushMatrix();
			{
				glTranslatef(0, -2.65f, 0);
				if (rotationStep > 0 && rotationGlobal < 10 && rotationGlobal > 0)//Tieso
				{
					glRotatef(0, 1, 0, 0);
				}
				else
				{
					if (rotationStep > 0 && rotationGlobal > 10)
					{
						glRotatef(rotationGlobal, 1, 0, 0);
					}
					if (rotationStep < 0 && rotationGlobal > 0)
					{
						glRotatef(rotationGlobal, 1, 0, 0);
					}
					if (rotationStep < 0 && rotationGlobal < 0)
					{
						glRotatef(-rotationGlobal, 1, 0, 0);
					}
					if (rotationStep >= 0 && rotationGlobal <= 0)
					{
						glRotatef(-rotationGlobal, 1, 0, 0);
					}
				}
				glTranslatef(0, 2.65f, 0);
				pantL->draw();
				footL->draw();
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glRotatef(-rotationGlobal, 1, 0, 0);
			legR->draw();
			glPushMatrix();
			{
				glTranslatef(0, -2.65f, 0);
				if (rotationStep < 0 && rotationGlobal > 10 && rotationGlobal < 0)//Tieso
				{
					glRotatef(0, 1, 0, 0);
				}
				else
				{
					if (rotationStep < 0 && rotationGlobal < 10)
					{
						glRotatef(-rotationGlobal, 1, 0, 0);
					}
					if (rotationStep > 0 && rotationGlobal < 0)
					{
						glRotatef(-rotationGlobal, 1, 0, 0);
					}
					if (rotationStep > 0 && rotationGlobal > 0)
					{
						glRotatef(rotationGlobal, 1, 0, 0);
					}
					if (rotationStep <= 0 && rotationGlobal >= 0)
					{
						glRotatef(rotationGlobal, 1, 0, 0);
					}
				}
				glTranslatef(0, 2.65f, 0);
				pantR->draw();
				footR->draw();
			}
			glPopMatrix();
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
	rotationGlobal += rotationStep;
	if (rotationGlobal > 20.0f || rotationGlobal < -20.0f)
	{
		rotationStep = -rotationStep;
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
