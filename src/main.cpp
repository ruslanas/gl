/**
 * @author Ruslanas Balciunas <ruslanas.com@gmail.com>
 */

#include <iostream>
#include <cstdio>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>

#include "util.h"
#include "Geometry.h"

void display() {
    glClearColor(0, 0, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    Geometry geom = Geometry();
    geom.create();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 0.01, 1000);
    gluLookAt(-10000, 10, 10, 0, 0, 0, 0, 1, 0);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    float color4f[4] = {2.0, 2.0, 2.0};
    glLightfv(GL_LIGHT0, GL_POSITION, color4f);

    glColor3f(1, 1, 1);
    glLoadIdentity();

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glCallList(1);
    glPopMatrix();

    glFlush();
}

int main(int argc, char**argv) {

    glutInit(&argc, argv);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenGL");

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cout << "Glew init err: " << glewGetErrorString(err) << std::endl;
        exit(1);
    }

    std::cout << "GLEW version: " << glewGetString(GLEW_VERSION) << std::endl;

    if (!GLEW_ARB_shader_objects || !GLEW_ARB_fragment_shader
            || !GLEW_ARB_vertex_shader || !GLEW_ARB_shading_language_100) {
        std::cout << "Unsupported extensions" << std::endl;
        exit(1);
    }

    // Load shader source from file


    std::cout << glGetString(GL_VERSION) << std::endl;

    glutDisplayFunc(display);
    prepareShaders();
    glutMainLoop();

    return 0;
}