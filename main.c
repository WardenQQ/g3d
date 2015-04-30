
/*======================================================*\
  Wednesday September the 25th 2013
  Arash HABIBI

  Modifié pour le projet g3d 2015 par Matthieu Michels
  \*======================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glx.h>

#include "vector.h"
#include "polygon.h"
#include "mesh.h"

/* dimensions de la fenetre */
int width = 600;
int height = 600;
float camera_zoom_level = 2.0f;
float camera_x_rotate = 0.0f;
float camera_y_rotate = 0.0f;

int is_drawing = 1;

Polygon polygon;
Mesh extrusion;

void set_projection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (is_drawing) {
        glOrtho(0, 1, 0, 1, 0, 1);
    } else {
        gluPerspective(60, (float)width / height, 0.1, 100);
    }
}

//------------------------------------------------------------

void drawRepere()
{
    glColor3d(1,0,0);
    glBegin(GL_LINES);
    glVertex3d(0,0,0);
    glVertex3d(1,0,0);
    glEnd();

    glColor3d(0,1,0);
    glBegin(GL_LINES);
    glVertex3d(0,0,0);
    glVertex3d(0,1,0);
    glEnd();

    glColor3d(0,0,1);
    glBegin(GL_LINES);
    glVertex3d(0,0,0);
    glVertex3d(0,0,1);
    glEnd();
}

//------------------------------------------------------------

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (!is_drawing) {
        Vector camera_pos = P_center(&polygon);
        glTranslatef(-camera_pos.x, -camera_pos.y, -camera_pos.z);
        glTranslatef(0, 0, -camera_zoom_level);
    }
    glRotatef(camera_x_rotate, 1, 0, 0);
    glRotatef(camera_y_rotate, 0, 1, 0);

    if (is_drawing) {
        P_draw(&polygon);
    } else {
        M_draw(&extrusion);
    }

    drawRepere();

    glutSwapBuffers();
}

//------------------------------------------------------------

void reshape(int w, int h)
{
    width = w;
    height = h;

    glViewport(0, 0, w, h);

    set_projection();
}

//------------------------------------------------------------

void keyboard(unsigned char keycode, int x, int y)
{
    printf("Touche frapee : %c (code ascii %d)\n",keycode, keycode);
    /* touche ECHAP */
    if (keycode==27) {
        exit(0);
    } else if (keycode == '+' && camera_zoom_level < 100.0f) {
        camera_zoom_level += 0.1f;
    } else if (keycode == '-' && camera_zoom_level > 2.0f) {
        camera_zoom_level -= 0.1f;
    } else if (keycode == '0') {
        camera_zoom_level = 2.0f;
        camera_x_rotate = 0.0f;
        camera_y_rotate = 0.0f;
    } else if (keycode == ' ') {
        is_drawing = 0;
        set_projection();
        M_perlinExtrude(&extrusion, &polygon, 1);
    } else if (keycode >= '0' && keycode <= '9') {
        M_perlinExtrude(&extrusion, &polygon, keycode - '0');
    }

    glutPostRedisplay();
}

//------------------------------------------------------------

void special(int keycode, int x, int y)
{
    if (!is_drawing) {
        switch(keycode) {
            case GLUT_KEY_UP:
                camera_x_rotate += 15;
                break;

            case GLUT_KEY_DOWN :
                camera_x_rotate -= 15;
                break;

            case GLUT_KEY_LEFT:
                camera_y_rotate -= 15;
                break;

            case GLUT_KEY_RIGHT:
                camera_y_rotate += 15;
                break;

            default:
                break;
        }
    }

    glutPostRedisplay();
}

//------------------------------------------------------------

void mouse(int button, int state, int x, int y)
{
    if (is_drawing) {
        float world_x = (float)x / glutGet(GLUT_WINDOW_WIDTH);
        float world_y = (float)y / glutGet(GLUT_WINDOW_HEIGHT) * -1 + 1;
        switch(button) {
            case GLUT_LEFT_BUTTON :
                if(state==GLUT_DOWN)
                    P_addVertex(&polygon, V_new(world_x, world_y, 0));
                break;

            case GLUT_RIGHT_BUTTON :
                if(state==GLUT_DOWN)
                    P_removeLastVertex(&polygon);
                break;
        }
    }
    glutPostRedisplay();
}

/*************************************************************************/
/* Fonction principale */
/*************************************************************************/

int main(int argc, char *argv[])
{
    P_init(&polygon);
    M_init(&extrusion);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Projet extrusion");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}
