#include <stdio.h>
#include <math.h>

#include "minunit.h"
#include "vector.h"

int tests_run = 0;

static char * test_add()
{
    Vector a = V_new(2, 3, 4);
    Vector b = V_new(8, 7, 6);
    Vector c = V_new(10, 10, 10);

    mu_assert("erreur, a + b != c", V_equality(V_add(a, b), c));

    return 0;
}

static char * test_substract()
{
    Vector a = V_new(2, 3, 4);
    Vector b = V_new(8, 7, 6);
    Vector c = V_new(10, 10, 10);

    mu_assert("erreur, c - b != a", V_equality(V_substract(c, b), a));

    return 0;
}

static char * test_multiply()
{
    Vector a = V_new(2, 3, 4);
    double l = 2.5;
    Vector b = V_new(2 * 2.5, 3 * 2.5, 4 * 2.5);

    mu_assert("erreur, l * a != b", V_equality(V_multiply(l, a), b));

    return 0;
}

static char * test_cross()
{
    Vector i = V_new(1, 0, 0);
    Vector j = V_new(0, 1, 0);
    Vector k = V_new(0, 0, 1);

    mu_assert("erreur, i x j != k", V_equality(V_cross(i, j), k));

    return 0;
}

static char * test_dot()
{
    Vector a = V_new(2, 3, 4);
    Vector b = V_new(8, 7, 6);
    float d = 16 + 21 + 24;

    mu_assert("erreur, a + b != c", fabsf(V_dot(a, b) - d) <= EPSILON);

    return 0;
}

static char * test_length()
{
    Vector v = V_new(3, 5, 6);
    float l = sqrtf(3 * 3 + 5 * 5 + 6 * 6);

    mu_assert("erreur, ||v|| != l", fabsf(V_length(v) - l) <= EPSILON);

    return 0;
}

static char * test_unit()
{
    Vector u = V_new(1, 0, 0);

    mu_assert("erreur, û != u", V_equality(V_unit(u), u));

    return 0;
}

static char * test_decompose()
{
    Vector p = V_new(3, 9, 6);
    Vector i = V_new(1, 0, 0);

    mu_assert("erreur, decomposition de p sur i != 3", fabsf(V_decompose(p, i) - 3) <= EPSILON);

    return 0;
}

static char * test_recompose()
{
    Vector i = V_new(1, 0, 0);
    Vector j = V_new(0, 1, 0);
    Vector k = V_new(0, 0, 1);
    Vector v = V_new(19, 12, 14.2);

    mu_assert("erreur, recomposition n'a pas réussi", V_equality(V_recompose(19, 12, 14.2, i, j, k), v));

    return 0;
}

static char * test_ux_uy_from_uz()
{
    Vector i = V_new(1, 0, 0);
    Vector j = V_new(0, 1, 0);
    Vector k = V_new(0, 0, 1);

    Vector u_x;
    Vector u_y;

    V_uxUyFromUz(k, &u_x, &u_y);
    mu_assert("erreur, u_x != i", V_equality(i, u_x));
    mu_assert("erreur, u_y != j", V_equality(j, u_y));

    V_uxUyFromUz(j, &u_x, &u_y);
    mu_assert("erreur, u_x != i", V_equality(i, u_x));
    mu_assert("erreur, u_y != -k", V_equality(V_multiply(-1, k), u_y));

    V_uxUyFromUz(V_new(23.5, 2.7, -9.1342), &u_x, &u_y);
    mu_assert("erreur, u_x n'est pas unitaire", V_equality(V_unit(u_x), u_x));
    mu_assert("erreur, u_y n'est pas unitaire", V_equality(V_unit(u_y), u_y));

    return 0;
}

static char * test_rotate()
{
    Vector i = V_new(1, 0, 0);
    Vector j = V_new(0, 1, 0);
    Vector k = V_new(0, 0, 1);
    Vector o = V_new(0, 0, 0);

    mu_assert("erreur, mauvais rotation", V_equality(V_rotate(j, o, i, k), j));

    return 0;
}


static char * all_tests()
{
    mu_run_test(test_add);
    mu_run_test(test_substract);
    mu_run_test(test_multiply);
    mu_run_test(test_cross);
    mu_run_test(test_dot);
    mu_run_test(test_length);
    mu_run_test(test_unit);
    mu_run_test(test_decompose);
    mu_run_test(test_recompose);
    mu_run_test(test_ux_uy_from_uz);
    mu_run_test(test_rotate);

    return 0;
}

int main(int argc, char ** argv)
{
    char * result = all_tests();

    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("Tous les tests sont OK!!\n");
    }

    printf("Tests lancés: %d\n", tests_run);

    return  result != 0;
}
