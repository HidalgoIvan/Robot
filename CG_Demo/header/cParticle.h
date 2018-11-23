//
//  cParticle.h
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

#include "cVector3.h"

#ifndef __PARTICLE
#define __PARTICLE

#include <stdio.h>
class Particle{
public:
    Particle(Vector3* _position, float _radius);
    ~Particle();
    
    void draw();
    void update(float dt);
    void VerletIntegration(float dt);
    void checkFloorCollision();
    bool checkCollision(Particle* another);
	void makeRed();
	void returnToOriginalColor();
    float mass;
    float radius;
    float restitutionCoefficient;
    float upDown;
	bool colliding = false;
	bool isStatic = false;
    GLfloat* mat0_ambient;
    GLfloat* mat0_specular;
    GLfloat* mat0_diffuse;
    GLfloat* mat0_shininess;
    Vector3* position;
    Vector3* prev_pos;
    Vector3* forces;
    Vector3* dragForce;
	Vector3* originalColor;
};


#endif /* __PARTICLE */
