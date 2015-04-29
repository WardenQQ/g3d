#include <stdio.h>

#include "minunit.h"
#include "polygon.h"
#include "vector.h"

int tests_run = 0;

static char * test_init()
{
    Polygon p;

    p.nb_vertices = 15;
    P_init(&p);
    mu_assert("erreur, nb_vertices != 0", p.nb_vertices == 0);

    return 0;
}

static char * test_copy()
{
    Polygon o, c;

    o.nb_vertices = 10;
    c.nb_vertices = 2345;
    P_copy(&o, &c);
    mu_assert("erreur, p != c", o.nb_vertices == c.nb_vertices);

    return 0;
}

static char * test_addVertex()
{
    Polygon p;
    Vector v = V_new(0, 2, 4);

    p.nb_vertices = 10;
    P_addVertex(&p, v);
    mu_assert("erreur, nb_vertices != 11", p.nb_vertices == 11);
    mu_assert("erreur, nouveau sommet n'est pas bon", V_equality(p.vertices[10], v));

    return 0;
}

static char * test_removeLastVertex()
{
    Polygon p;

    P_init(&p);
    P_removeLastVertex(&p);
    mu_assert("erreur, nb_vertices négatif", p.nb_vertices == 0);

    P_addVertex(&p, V_new(0, 0, 0));
    P_removeLastVertex(&p);
    mu_assert("erreur, nb_vertices != 0", p.nb_vertices == 0);

    return 0;
}

static char * test_center()
{
    Vector a = V_new(0, 0, 0),
           b = V_new(2, 0, 2),
           c = V_new(2, 2, 2),
           d = V_new(0, 2, 0),
           cen = V_new(1, 1, 1);
    Polygon p;

    P_init(&p);
    P_addVertex(&p, a);
    P_addVertex(&p, b);
    P_addVertex(&p, c);
    P_addVertex(&p, d);
    mu_assert("erreur, le centre  a été mal calculé", V_equality(P_center(&p), cen));

    return 0;
}

static char * test_normal()
{
    Vector a = V_new(0, 0, 0),
           b = V_new(2, 0, 0),
           c = V_new(2, 2, 0),
           d = V_new(0, 2, 0),
           norm = V_new(0, 0, 1);
    Polygon p;

    P_init(&p);
    P_addVertex(&p, a);
    P_addVertex(&p, b);
    P_addVertex(&p, c);
    P_addVertex(&p, d);
    mu_assert("erreur, la normale  a été mal calculé", V_equality(P_normal(&p), norm));

    return 0;
}


static char * all_tests()
{
    mu_run_test(test_init);
    mu_run_test(test_copy);
    mu_run_test(test_addVertex);
    mu_run_test(test_removeLastVertex);
    mu_run_test(test_center);
    mu_run_test(test_normal);

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
