/*
* Sergio Ruiz.
*
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
#include "Cube.h"
#include "Robot.h"
#endif
Robot* robot;
int main(int argc, char* argv[])
{
	robot->run(argc,argv);
	return 0;
}
