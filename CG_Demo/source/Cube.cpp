#include "Cube.h"
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
float scale_x;
float scale_y;
float scale_z;
float pos_x;
float pos_y;
float pos_z;
float rot_x;
float rot_y;
float rot_z;
float r;
float g;
float b;
Cube::Cube()
{

}
void Cube::setColor(float _r, float _g, float _b) {
	r = _r / 255.0f;
	g = _g / 255.0f;
	b = _b / 255.0f;
}
void Cube::setScale(float x, float y, float z) {
	scale_x = x;
	scale_y = y;
	scale_z = z;
}
void Cube::setPosition(float x, float y, float z) {
	pos_x = x;
	pos_y = y;
	pos_z = z;
}
void Cube::setRotation(float x, float y, float z) {
	rot_x = x;
	rot_y = y;
	rot_z = z;
}
void Cube::update() {

}
void Cube::draw() {
	glPushMatrix(); 
	{
		float mcolor[] = { 1.0f, 0.0f, 0.0f, 1.0f };

		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
		glColor3f(r, g, b);
		glTranslatef(pos_x, pos_y, pos_z);
		glRotatef(rot_x, 1, 0, 0);
		glRotatef(rot_y, 0, 1, 0);
		glRotatef(rot_z,0,0,1);
		glScalef(scale_x, scale_y, scale_z);
		glutSolidCube(1);
	}
	glPopMatrix();
}

