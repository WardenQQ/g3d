#include <math.h>

#include "vector.h"


Vector V_new(float x, float y, float z)
{
    Vector v;

    v.x = x;
    v.y = y;
    v.z = z;

    return v;
}


int V_equality(Vector v1, Vector v2)
{
    return (fabsf(v1.x - v2.x) <= EPSILON
            && fabsf(v1.y - v2.y) <= EPSILON
            && fabsf(v1.z - v2.z) <= EPSILON);
}


void V_print(Vector v)
{
    fprintf(stdout, "{ x: %.5f, y: %.5f, z: %.5f }\n", v.x, v.y, v.z);
}


Vector V_add(Vector v1, Vector v2)
{
    return V_new(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}


Vector V_substract(Vector v1, Vector v2)
{
    return V_new(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}


Vector V_multiply(double lambda, Vector v)
{
    return V_new(lambda * v.x, lambda * v.y, lambda * v.z);
}


Vector V_cross(Vector v1, Vector v2)
{
    return V_new(v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x);
}


float V_dot(Vector v1, Vector v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


float V_length(Vector v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}


Vector V_unit(Vector v)
{
    return V_multiply(1 / V_length(v), v);
}


/*
 * Retour: 1 -> M a gauche de [AB]
 *        -1 -> M a droite de [AB]
 *         0 -> M colineaire avec A et B
 */
int V_positionToSegment(Vector M, Vector A, Vector B)
{
    Vector AB = V_substract(B, A);
    Vector AM = V_substract(M, A);
    Vector normal = V_cross(AB, AM);

    if (V_equality(normal, V_new(0, 0, 0))) {
        return 0;
    }

    Vector up = V_new(0, 0, 1);
    float dot = V_dot(normal, up);

    if (dot >= -EPSILON && dot <= EPSILON) {
        up = V_new(0, 1, 0);
        dot = V_dot(normal, up);

        if (dot >= -EPSILON && dot <= EPSILON) {
            up = V_new(1, 0, 0);
            dot = V_dot(normal, up);
        }
    }

    if (dot >= 0) {
        return 1;
    } else {
        return -1;
    }
}

int V_onSegment(Vector M, Vector A, Vector B)
{
    Vector min = V_new(A.x < B.x ? A.x : B.x,
                       A.y < B.y ? A.y : B.y,
                       A.z < B.z ? A.z : B.z);
    Vector max = V_new(A.x > B.x ? A.x : B.x,
                       A.y > B.y ? A.y : B.y,
                       A.z > B.z ? A.z : B.z);

    return (M.x >= min.x && M.x <= max.x
            && M.y >= min.y && M.y <= max.y
            && M.z >= min.z && M.z <= max.z);
}


int V_segmentsIntersect(Vector A, Vector B, Vector C, Vector D)
{
    int posA = V_positionToSegment(A, C, D);
    int posB = V_positionToSegment(B, C, D);
    int posC = V_positionToSegment(C, A, B);
    int posD = V_positionToSegment(D, A, B);

    if (posA != posB && posC != posD) {
        return 1;
    }

    if (posA == 0 && V_onSegment(A, C, D)) {
        return 1;
    }

    if (posB == 0 && V_onSegment(B, C, D)) {
        return 1;
    }

    if (posC == 0 && V_onSegment(C, A, B)) {
        return 1;
    }

    if (posD == 0 && V_onSegment(D, A, B)) {
        return 1;
    }

    return 0;
}


/*
 * Précondition: u est un vecteur unitaire.
 */
double V_decompose(Vector p, Vector u)
{
    return V_dot(p, u);
}

Vector V_recompose(double x, double y, double z, Vector u, Vector v, Vector w)
{
    return V_add(V_multiply(x, u), V_add(V_multiply(y, v), V_multiply(z, w)));
}

/*
 * Précondition: u_z est un vecteur unitaire.
 * Postcondition: u_x et u_y sont des vecteurs unitaires.
 */
void V_uxUyFromUz(Vector u_z, Vector *u_x, Vector *u_y)
{
    Vector u;
    Vector v;

    if (V_equality(u_z, V_new(0, 1, 0))) {
        // Premier cas de u_z colinéaire au vecteur (0, 1, 0).
        u_x->x = 1;
        u_x->y = 0;
        u_x->z = 0;

        u_y->x = 0;
        u_y->y = 0;
        u_y->z = -1;
    } else if (V_equality(u_z, V_new(0, -1, 0))) {
        // Deuxième cas de u_z colinéaire au vecteur (0, 1, 0).
        u_x->x = 1;
        u_x->y = 0;
        u_x->z = 0;

        u_y->x = 0;
        u_y->y = 0;
        u_y->z = 1;
    } else {
        u = V_cross(V_new(0, 1, 0), u_z);
        v = V_cross(u_z, u);

        u = V_unit(u);
        v = V_unit(v);

        u_x->x = u.x;
        u_x->y = u.y;
        u_x->z = u.z;

        u_y->x = v.x;
        u_y->y = v.y;
        u_y->z = v.z;
    }

}


Vector V_rotate(Vector p, Vector center, Vector v1, Vector v2)
{
    double x, y, z;
    Vector ux, uy, vx, vy;
    Vector r;
    
    p = V_substract(p, center);

    V_uxUyFromUz(v1, &ux, &uy);
    V_uxUyFromUz(v2, &vx, &vy);

    x = V_decompose(p, ux);
    y = V_decompose(p, uy);
    z = V_decompose(p, v1);

    r = V_recompose(x, y, z, vx, vy, v2);

    return V_add(r, center);
}
