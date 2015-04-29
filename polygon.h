
/*======================================================*\
  Wednesday September the 25th 2013
  Arash HABIBI
  Polygon.h

  Modifié pour le projet g3d 2015 par Matthieu Michels
\*======================================================*/

#ifndef __POLYGON_H__
#define __POLYGON_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vector.h"

#define P_MAX_VERTICES 1000

typedef struct {
	int nb_vertices;
	Vector vertices[P_MAX_VERTICES];
	int is_closed;
	int is_filled;
	int is_convex;
} Polygon;

void P_init(Polygon *p);

void P_copy(Polygon *original, Polygon *copie);

void P_addVertex(Polygon *p, Vector pos);

void P_removeLastVertex(Polygon *p);

Vector P_center(Polygon *p);

Vector P_normal(Polygon *p);

void P_translate(Polygon *p, Vector trans);

void P_rotate(Polygon *p, Vector normal);

void P_draw(Polygon *p);

void P_print(Polygon *p);


#endif // __POLYGON_H__
