
/*======================================================*\
  Wednesday September the 25th 2013
  Arash HABIBI
  Mesh.h

  Modifié pour le projet g3d 2015 par Matthieu Michels
  \*======================================================*/

#ifndef _MESH_H_
#define _MESH_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glx.h>

#include "vector.h"
#include "polygon.h"
#include "perlin.h"

#define M_MAX_QUADS 5000

typedef struct {
    Vector vertices[4];
} Quad;

Quad Q_new(Vector v1, Vector v2, Vector v3, Vector v4);

//--------------------------------------------

typedef struct {
    int nb_quads;
    Quad quads[M_MAX_QUADS];
    int is_filled;
} Mesh;

void M_init(Mesh *m);
void M_print(Mesh *P, char *message);

void M_addQuad(Mesh *m, Quad q);
void M_addSlice(Mesh *m, Polygon *p1, Polygon *p2);
void M_perlinExtrude(Mesh *m, Polygon *p, int nb_slices);

void M_draw(Mesh *m);

#endif // _MESH_H_
