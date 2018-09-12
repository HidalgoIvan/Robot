/*
* Ernesto Iv�n Ochoa Hidalgo A01651425
* Alejandro "El navajas" Pe�a
* Ana Karen "Pe�a" Pe�a
* Arturo "La rata" Mac�as
* TC3022. Computer Graphics Course.
* Robot walk animation.
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
#include "Cube.h"
#include "Robot.h"
#endif
Robot* robot;
int main(int argc, char* argv[])
{
	
	robot->run(argc,argv);
	return 0;
}
