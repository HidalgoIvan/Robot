#pragma once
class Cube
{
public:
	Cube();
	void setColor(float _r, float _g, float _b);
	void setScale(float x, float y, float z);
	void setPosition(float x, float y, float z);
	void update();
	void draw();
};

