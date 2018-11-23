//
//  cParticle.cpp
//  ParticlePractice
//
//  Created by Ana Karen Campos on 10/26/18.
//  Copyright © 2018 Tec de Monterrey. All rights reserved.
//

#include "cParticle.h"
#include <stdlib.h>
#include <random>

Particle::Particle(Vector3* _position, float _radius){
    position = new Vector3(_position);
    radius = _radius;
    prev_pos = new Vector3(_position);
    mass = 10.0f;
    forces = new Vector3();
    dragForce = new Vector3();
    float area = 4.0f * 3.1415 * radius * radius;
    dragForce->x = 0;
    dragForce->y = area / 9.81f;
    dragForce->z = 0;
    
    restitutionCoefficient = 0.2f;
    upDown = -1.0f;
    
    
    mat0_ambient  = new GLfloat[4];
    mat0_ambient[0] = (((float)rand()/(float)(RAND_MAX)) * 0.1) + 0.1;
    mat0_ambient[1] = (((float)rand()/(float)(RAND_MAX)) * 0.1) + 0.1;
    mat0_ambient[2] = (((float)rand()/(float)(RAND_MAX)) * 0.1) + 0.1;
    mat0_ambient[3] = 1.0f;
    
    
    mat0_specular = new GLfloat[4];
    mat0_specular[0] = (((float)rand()/(float)(RAND_MAX)) * 4.0) + 0.6;
    mat0_specular[1] = (((float)rand()/(float)(RAND_MAX)) * 4.0) + 0.6;
    mat0_specular[2] = (((float)rand()/(float)(RAND_MAX)) * 4.0) + 0.6;
    mat0_specular[3] = 1.0f;
    
    
    mat0_diffuse = new GLfloat[4];
    mat0_diffuse[0] = (((float)rand()/(float)(RAND_MAX)) * 0.5) + 0.2;
    mat0_diffuse[1] = (((float)rand()/(float)(RAND_MAX)) * 0.8) + 0.2;
    mat0_diffuse[2] = (((float)rand()/(float)(RAND_MAX)) * 0.8) + 0.2;
    mat0_diffuse[3] = 1.0f;
    
	originalColor = new Vector3(mat0_diffuse[0], mat0_diffuse[1], mat0_diffuse[2]);

    mat0_shininess = new GLfloat[1];
    mat0_shininess[0] = (((float)rand()/(float)(RAND_MAX)) * 50.0) + 50.0;
}

void Particle::draw(){
	if(colliding)
	{
		mat0_diffuse[0] = 1.0f;
		mat0_diffuse[1] = 0;
		mat0_diffuse[2] = 0;
	}
    glPushMatrix();
    {
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat0_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat0_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat0_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat0_shininess);
        glTranslatef(position->x, position->y, position->z);
        glutSolidSphere(radius, 30, 30);
    }
    glPopMatrix();
	if (colliding)
	{
		mat0_diffuse[0] = originalColor->x;
		mat0_diffuse[1] = originalColor->y;
		mat0_diffuse[2] = originalColor->z;
		colliding = false;
	}
}

void Particle::update(float dt){
	if (!isStatic)
	{
		forces->y += (-9.81 * mass / 60.0f);
		//La fricción al moverse
		forces->x /= 1.035f;
		forces->z /= 1.035f;
		VerletIntegration(dt);
		checkFloorCollision();
	}
    /*if (position->y >= -3.0) {
        VerletIntegration(dt);
    }
    else {
        printf("I hit the ground \n", 0);
    }*/
}

Particle::~Particle(){
    
}

void Particle::VerletIntegration(float dt){
    
    forces->x += dragForce->x;
    forces->y += upDown * dragForce->y;
    forces->z += dragForce->z;
    Vector3* a = new Vector3(forces->x/mass, forces->y/mass, forces->z/mass);
    prev_pos = new Vector3(position);
    position->x += position->x-prev_pos->x + a->x * dt * dt;
    position->y += position->y-prev_pos->y + a->y * dt * dt;
    position->z += position->z-prev_pos->z + a->z * dt * dt;
    //position->print();
    
    if((position->y - prev_pos->y) > 0.0f){
        upDown = 1.0f;
    }else if((position->y - prev_pos->y) < 0.0f && position-> x*position->x+position->z*position->z <= 8*8){
        upDown = -1.0f;
    }
    
}

bool Particle::checkCollision(Particle* other){
    float r1 = radius;
    float r2 = other->radius;
    Vector3* c1 = position;
    Vector3* c2 = other->position;
    float sumR = r1 + r2;
    float sumR2 = sumR * sumR;
    float dx = c2->x - c1->x;
    dx *= dx;
    float dy = c2->y - c1->y;
    dy *= dy;
    float dz = c2->z - c1->z;
    dz *= dz;
    float d = dx + dy + dz;
    
    if(d <= sumR2){
		// "Chocan" y se repelen
		float myDisp = 0.0;
		float otherDisp = 0.0f;
		float dispDistance = 5.0f + ((abs(forces->x) + abs(forces->z) + abs(other->forces->x) + abs(other->forces->z))/80.0f);
		/*if (radius >= other->radius)
		{
			otherDisp = (other->radius / radius);
			myDisp = 1.0 - otherDisp;
		}
		else
		{
			myDisp = (radius / other->radius);
			otherDisp = 1.0 - myDisp;
		}*/
		otherDisp = radius / other->radius;
		myDisp = other->radius / radius;
		if (position->x <= other->position->x) //Le llega por la derecha
		{
			printf("por la derecha \n");
			//Estos rebotan la particula hasta una distancia igual a la suma de los radios, no es muy realista
			//disp = ((position->x + radius) - (other->position->x - other->radius)) / 2.0f;
			forces->x += -myDisp * dispDistance;
			other->forces->x += otherDisp * dispDistance;
		}
		if (position->x > other->position->x) //Le llega por la izquierda
		{
			printf("por la izquierda \n");
			//disp = ((position->x - radius) - (other->position->x + other->radius)) / 2.0f;
			forces->x += myDisp * dispDistance;
			other->forces->x += -otherDisp * dispDistance;
		}
		if (position->z <= other->position->z) //Le llega por adelante
		{
			printf("por adelante\n");
			//disp = ((position->z + radius) - (other->position->z - other->radius)) / 2.0f;
			forces->z += -myDisp * dispDistance;
			other->forces->z += otherDisp * dispDistance;
		}
		if (position->z > other->position->z) //Le llega por atras
		{
			printf("por atras, igual que a Paty \n");
			//disp = ((position->z - radius) - (other->position->z + other->radius)) / 2.0f;
			forces->z += myDisp * dispDistance;
			other->forces->z += -otherDisp * dispDistance;
		}
        return true;
    }else{
        return false;
    }
}

void Particle::checkFloorCollision(){
    if(position->y < radius){
        prev_pos->y = position->y;
        position->y = radius;
        forces->y = -forces->y * restitutionCoefficient;
    }
}

void Particle::makeRed()
{
	colliding = true;
}

void Particle::returnToOriginalColor()
{
	mat0_diffuse[0] = originalColor->x;
	mat0_diffuse[1] = originalColor->y;
	mat0_diffuse[2] = originalColor->z;
}
