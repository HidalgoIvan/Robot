#pragma once
#include "hCube.h"
#include "glm.h"
#include "cVector3.h"
class Piece
{
public:
	Piece(char* objName);
	float size_x = 1;
	float size_y = 1;
	float size_z = 1;
	float pos_x = 0;
	float pos_y = 0;
	float pos_z = 0;
	float tra_x = 0;
	float tra_y = 0;
	float tra_z = 0;
	float r = .1f;
	float g = .1f;
	float b = .1f;
	float rot_x = 0;
	float rot_y = 0;
	float rot_z = 0;
	float rPivot_x = 0;
	float rPivot_y = 0;
	float rPivot_z = 0;
	GLMmodel* baseM;
	Piece* son;
	float baseM_pos[3];
	float baseM_dims[3];
	bool hasSon = false;
	bool isBase = false;
	void setColor(float _r, float _g, float _b);
	void setSize(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setTranslation(float x, float y, float z);
	void setRotationPivot(float x, float y, float z);
	void Piece::setSon(Piece* s);
	void update();
	void draw();
	void rotateSon(Vector3 rotation, float hierarchy);
};

