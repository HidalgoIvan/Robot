//
//  cVector3.h
//  ParticlePractice
//
//  Created by Ana Karen Campos on 10/26/18.
//  Copyright © 2018 Tec de Monterrey. All rights reserved.
//
#pragma one

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include "freeglut.h"
#endif

#ifndef __VECTOR3
#define __VECTOR3

#include <stdio.h>
class Vector3{
public:
    Vector3();
    Vector3(Vector3* other);
    Vector3(float _x, float _y, float _z);
    ~Vector3();
    
    void print();
    
    float x, y, z;
};

#endif /* __VECTOR3 */
