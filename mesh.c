#include "mesh.h"


Quad Q_new(Vector v1, Vector v2, Vector v3, Vector v4)
{
    Quad q;

    q.vertices[0] = v1;
    q.vertices[1] = v2;
    q.vertices[2] = v3;
    q.vertices[3] = v4;

    return q;
}

void M_init(Mesh *m)
{
   m->nb_quads = 0; 
}

void M_addQuad(Mesh *m, Quad q)
{
    if (m->nb_quads >= M_MAX_QUADS) {
        return;
    }

    m->quads[m->nb_quads] = q;
    m->nb_quads++;
}

void M_addSlice(Mesh *m, Polygon *p1, Polygon *p2)
{
    int i;
    Quad q;

    for (i = 0; i < p1->nb_vertices; i++) {
        q = Q_new(p1->vertices[i],
                  p1->vertices[(i + 1) % p1->nb_vertices],
                  p2->vertices[(i + 1) % p1->nb_vertices],
                  p2->vertices[i]);
        M_addQuad(m, q);
    }
}

void M_perlinExtrude(Mesh *m, Polygon *p, int nb_slices)
{
    int i;
    Polygon cur,
            new;
    Vector v_noise;

    P_copy(p, &cur);

    for (i = 0; i < nb_slices; i++) {
        P_copy(&cur, &new);

        v_noise = PRLN_vectorNoise(P_center(&new));
        if (V_dot(v_noise, P_normal(&new)) < 0) {
            v_noise = V_multiply(-1, v_noise);
        }
        P_translate(&new, v_noise);
        P_rotate(&new, V_unit(v_noise));

        M_addSlice(m, &cur, &new);

        P_copy(&new, &cur);
    }
}

void M_draw(Mesh *m)
{
    int i, j;

    glColor3d(0, 0, 0);
    for (i = 0; i < m->nb_quads; i++) {
        glBegin(GL_LINE_LOOP);
        for (j = 0; j < 4; j++) {
            glVertex3f(m->quads[i].vertices[j].x,
                       m->quads[i].vertices[j].y,
                       m->quads[i].vertices[j].z);
        }
        glEnd();
    }
}
