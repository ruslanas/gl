/* 
 * File:   Geometry.cpp
 * Author: Ruslanas
 * 
 * Created on 04 July 2014, 19:21
 */

#include "Geometry.h"

Geometry::Geometry() {
}

Geometry::Geometry(const Geometry& orig) {
}

Geometry::~Geometry() {
}

void Geometry::create() {
    glNewList(1, GL_COMPILE);
    glBegin(GL_TRIANGLES);

    glColor3f(0, 1, 0);

    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(0, 1, 0);

    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(0, 0, 1);

    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);
    glVertex3f(0, 0, 1);

    glEnd();
    glEndList();
}
