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
            && fabsf(v1.x - v2.x) <= EPSILON
            && fabsf(v1.x - v2.x) <= EPSILON);
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
    float length = V_length(v);

    return V_new(v.x / length, v.y / length, v.z / length);
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
    return V_new(x * u.x + x * v.x + x * w.x,
            y * u.y + y * v.y + y * w.y,
            z * u.z + z * v.z + z * w.z);

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
