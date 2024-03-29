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

int P_valid(Polygon *p)
{
    int i;

    if (p->nb_vertices < 3) {
        return 0;
    }

    for (i = 1; i < p->nb_vertices - 2; i++) {
        if (V_segmentsIntersect(p->vertices[i],
                                p->vertices[i + 1],
                                p->vertices[p->nb_vertices - 1],
                                p->vertices[0])) {
            return 0;
        }
    }

    if (V_equality(P_normal(p), V_new(0, 0, 0))) {
        return 0;
    }

    return 1;
}

void P_addVertex(Polygon *p, Vector pos)
{
    int i;

    if (p->nb_vertices >= P_MAX_VERTICES) {
        return;
    }

    // Les segments ne doivent pas se croiser.
    for (i = 0; i < p->nb_vertices - 2; i++) {
        if (V_segmentsIntersect(p->vertices[i],
                                p->vertices[i + 1],
                                p->vertices[p->nb_vertices - 1],
                                pos)) {
            return;
        }
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
    Vector cen = V_new(0, 0, 0);

    for (i = 0; i < p->nb_vertices; i++) {
        cen = V_add(cen, p->vertices[i]);
    }

    return V_multiply(1.0f / p->nb_vertices, cen);
}


Vector P_normal(Polygon *p)
{
    int i;
    Vector n, u, v;

    for (i = 0; i < p->nb_vertices; i++) {
        u = V_substract(p->vertices[i], p->vertices[(i + 1) % p->nb_vertices]);
        v = V_substract(p->vertices[i], p->vertices[(i + 2) % p->nb_vertices]);
        n = V_cross(u, v);

        if (!V_equality(n, V_new(0, 0, 0))) {
            return V_unit(n);
        }
    }

    return V_new(0, 0, 0);
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

    glColor3f(131.0 / 255.0, 148.0 / 255.0, 150.0 / 255.0);
    glBegin(GL_LINE_STRIP);
    for (i = 0; i < p->nb_vertices; i++) {
        glVertex3f(p->vertices[i].x,
                   p->vertices[i].y,
                   p->vertices[i].z);
    }
    glEnd();

    if (p->nb_vertices > 2) {
        glColor3f(180.0 / 255.0, 137.0 / 255.0, 0.0);
        glBegin(GL_LINES);
        glVertex3f(p->vertices[i - 1].x,
                p->vertices[i - 1].y,
                p->vertices[i - 1].z);
        glVertex3f(p->vertices[0].x,
                p->vertices[0].y,
                p->vertices[0].z);
        glEnd();
    }
}

void P_print(Polygon *p)
{
    int i;

    fprintf(stdout, "%d sommet(s): \n", p->nb_vertices);

    for (i = 0; i < p->nb_vertices; i++) {
        V_print(p->vertices[i]);
    }
}
