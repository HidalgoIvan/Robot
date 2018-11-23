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
#include "../hCube.h"


Cube::Cube()
{
}
void Cube::setSon(Cube* s)
{
	son = s;
	hasSon = true;
}
void Cube::setColor(float _r, float _g, float _b) {
	r = _r / 255.0f;
	g = _g / 255.0f;
	b = _b / 255.0f;
}
void Cube::setSize(float x, float y, float z) {
	this->size_x = x / 2.0f;
	size_y = y / 2.0f;
	size_z = z / 2.0f;
}
void Cube::setRotation(float x, float y, float z) {
	rot_x = x;
	rot_y = y;
	rot_z = z;
}
void Cube::setTranslation(float x, float y, float z) {
	tra_x = x;
	tra_y = y;
	tra_z = z;
}
void Cube::setRotationPivot(float x, float y, float z)
{
	rPivot_x = x;
	rPivot_y = y;
	rPivot_z = z;
}
void Cube::update() {

}
void Cube::draw() {
	glPushMatrix();
	{
		glTranslatef(tra_x, tra_y, tra_z);
		glTranslatef(rPivot_x, rPivot_y, rPivot_z);
		glRotatef(rot_x, 1, 0, 0);
		glRotatef(rot_y, 0, 1, 0);
		glRotatef(rot_z, 0, 0, 1);
		glTranslatef(-rPivot_x, -rPivot_y, -rPivot_z);

		glBegin(GL_QUADS);
		{
			glColor3f(r, g, b);
			// FRONT FACE
			// Bottom left
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-size_x, -size_y, size_z);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(size_x, -size_y, size_z);
			// Top right
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(size_x, size_y, size_z);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-size_x, size_y, size_z);
			// RIGHT FACE
			// Bottom left
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(size_x, -size_y, size_z);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(size_x, size_y, size_z);
			// Top right
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(size_x, size_y, -size_z);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(size_x, -size_y, -size_z);
			// BACK FACE
			// Bottom left
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(size_x, -size_y, -size_z);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-size_x, -size_y, -size_z);
			// Top right
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-size_x, size_y, -size_z);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(size_x, size_y, -size_z);
			// BOTTOM FACE
			// Bottom left
			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-size_x, -size_y, size_z);
			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(size_x, -size_y, size_z);
			// Top right
			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(size_x, -size_y, -size_z);
			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-size_x, -size_y, -size_z);
			// LEFT FACE
			// Bottom left
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-size_x, -size_y, -size_z);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-size_x, -size_y, size_z);
			// Top right
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-size_x, size_y, size_z);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-size_x, size_y, -size_z);
			// TOP FACE
			// Bottom left
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-size_x, size_y, size_z);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(size_x, size_y, size_z);
			// Top right
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(size_x, size_y, -size_z);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-size_x, size_y, -size_z);
			glTranslatef(-tra_x, -tra_y, -tra_z);
		}
		glEnd();
		if (hasSon)
		{
			son->draw();
		}
	}
	glPopMatrix();
}
#endif