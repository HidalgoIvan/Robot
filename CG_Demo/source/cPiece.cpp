#ifdef __APPLE__
// For XCode only: New C++ terminal project. Build phases->Compile with libraries: add OpenGL and GLUT
// Import this whole code into a new C++ file (main.cpp, for example). Then run.
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
// For VS only: Download CG_Demo.zip. UNZIP FIRST. Double click on CG_Demo/CG_Demo.sln
// Run
#include "hPiece.h"

Piece::Piece(char* objName)
{
	baseM_pos[0] = 0.0f;
	baseM_pos[1] = 0.0f;
	baseM_pos[2] = 0.0f;
	baseM = glmReadOBJ(objName);
	glmUnitize(baseM);
	glmFacetNormals(baseM);
	glmDimensions(baseM, baseM_dims);
	float center[3] = {
		baseM_pos[0] + baseM_dims[0] / 2.0f,
		baseM_pos[1] + baseM_dims[1] / 2.0f,
		baseM_pos[2] + baseM_dims[2] / 2.0f
	};
}
void Piece::setSon(Piece* s)
{
	son = s;
	hasSon = true;
}
void Piece::setColor(float _r, float _g, float _b) {
	r = _r / 255.0f;
	g = _g / 255.0f;
	b = _b / 255.0f;
}
void Piece::setSize(float x, float y, float z) {
	this->size_x = x;
	size_y = y;
	size_z = z;
}
void Piece::setRotation(float x, float y, float z) {
	rot_x = x;
	rot_y = y;
	rot_z = z;
}
void Piece::setTranslation(float x, float y, float z) {
	tra_x = x;
	tra_y = y;
	tra_z = z;
}
void Piece::setRotationPivot(float x, float y, float z)
{
	rPivot_x = x;
	rPivot_y = y;
	rPivot_z = z;
}
void Piece::update() {

}
void Piece::draw() {
	glPushMatrix();
	{
		glTranslatef(tra_x, tra_y, tra_z);

		glTranslatef(rPivot_x, rPivot_y, rPivot_z);
		glRotatef(rot_x, 1, 0, 0);
		glRotatef(rot_y, 0, 1, 0);
		glRotatef(rot_z, 0, 0, 1);
		glTranslatef(-rPivot_x, -rPivot_y, -rPivot_z);
		glPushMatrix();
		{
			glScalef(size_x, size_y, size_z);
			glmDraw(baseM, GLM_SMOOTH | GLM_TEXTURE);		//base model
			glScalef(1,1,1);
		}
		glPopMatrix();
		glTranslatef(-tra_x, -tra_y, -tra_z);
		glEnd();
		if (hasSon)
		{
			son->draw();
		}
	}
	glPopMatrix();
}
void Piece::rotateSon(Vector3 rotation, float hierarchy)
{

}
#endif