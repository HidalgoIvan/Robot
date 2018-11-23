//
//  cVector3.cpp
//  ParticlePractice
//
//  Created by Ana Karen Campos on 10/26/18.
//  Copyright © 2018 Tec de Monterrey. All rights reserved.
//

#include "cVector3.h"

Vector3::Vector3(){
    x = y = z = 0;
}

Vector3::Vector3(Vector3* other){
    x = other->x;
    y = other->y;
    z = other->z;
}

Vector3::Vector3(float _x, float _y, float _z){
    x = _x;
    y = _y;
    z = _z;
}

Vector3::~Vector3(){
    
}

void Vector3::print(){
    printf("%.3f, %.3f, %.3f\n", x, y, z);
}
