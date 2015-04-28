#include <GL/glx.h>

#include "polygon.h"


void P_init(Polygon *p)
{
    p->nb_vertices = 0;
}


void P_copy(Polygon *original, Polygon *copie)
{
    int i;

    copie->nb_vertices = original->nb_vertices;  

    for (i = 0; i < original->nb_vertices; i++) {
        copie->vertices[i] = original->vertices[i];  
    }
}


void P_addVertex(Polygon *p, Vector pos)
{
    if (p->nb_vertices >= P_MAX_VERTICES) {
        return;
    }

    p->vertices[p->nb_vertices] = pos;
    p->nb_vertices++;

}


void P_removeLastVertex(Polygon *p)
{
    if (p->nb_vertices <= 0) {
        return;
    }

    p->nb_vertices--;
}


Vector P_center(Polygon *p)
{
    int i;
    float x = 0,
          y = 0,
          z = 0;

    for (i = 0; i < p->nb_vertices; i++) {
        x += p->vertices[i].x;
        y += p->vertices[i].y;
        z += p->vertices[i].z;
    }
    x /= p->nb_vertices;
    y /= p->nb_vertices;
    z /= p->nb_vertices;

    return V_new(x, y, z);
}


Vector P_normal(Polygon *p)
{
    // On considère qu'un polygone n'a pas 2 points colinéaires.
    Vector u = V_substract(p->vertices[0], p->vertices[1]);
    Vector v = V_substract(p->vertices[0], p->vertices[2]);

    return V_unit(V_cross(u, v));
}


void P_translate(Polygon *p, Vector trans)
{
    int i;

    for (i = 0; i < p->nb_vertices; i++) {
        p->vertices[i] = V_add(p->vertices[i], trans);
    }
}


void P_rotate(Polygon *p, Vector normal)
{
    int i;
    Vector c = P_center(p);
    Vector n = P_normal(p);

    for (i = 0; i < p->nb_vertices; i++) {
        p->vertices[i] = V_rotate(p->vertices[i], c, n, normal);
    }
}


void P_draw(Polygon *p)
{
    int i;

    glColor3d(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < p->nb_vertices; i++) {
        glVertex3f(p->vertices[i].x,
                   p->vertices[i].y,
                   p->vertices[i].z);
    }
    glEnd();
}
