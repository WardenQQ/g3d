
/*======================================================*\
  Wednesday September the 25th 2013
  Arash HABIBI
  Vector.h

  Modifié pour le projet g3d 2015 par Matthieu Michels
\*======================================================*/

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 0.001

typedef struct {
	float x, y, z;
} Vector;

Vector V_new(float x, float y, float z);

int V_equality(Vector v1, Vector V2);
void V_print(Vector v, char *message);

Vector V_add(Vector v1, Vector v2);
Vector V_substract(Vector v1, Vector v2);
Vector V_multiply(double lambda, Vector v);
Vector V_cross(Vector v1, Vector v2);
float V_dot(Vector v1, Vector v2);
float V_length(Vector v);
Vector V_unit(Vector v);

double V_decompose(Vector p, Vector u); 
Vector V_recompose(double x, double y, double z, Vector u, Vector v, Vector w); 
void V_uxUyFromUz(Vector u_z, Vector *u_x, Vector *u_y); 
Vector V_rotate(Vector p, Vector center, Vector v1, Vector v2);


#endif // __VECTOR_H__
