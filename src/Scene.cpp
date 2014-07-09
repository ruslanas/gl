/* 
 * File:   Scene.cpp
 * Author: Ruslanas
 * 
 * Created on 09 July 2014, 20:17
 */

#include <GL/glew.h>
#include <iostream>

#include "Scene.h"
#include "Box.h"

Scene::Scene() {
    numVertices = 0;
}

Scene::Scene(const Scene& orig) {
    numVertices = orig.numVertices;
}

Scene::~Scene() {
}

// of course it is a stub
void Scene::add(const Mesh& mesh) {
    numVertices += mesh.numVertices();
}

void Scene::render() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // select array for use as vertex data
    glBindVertexArray(array);

    // send vertex data to OpenGL pipeline.
    // take NumVertices, start from 0th element in vertex array
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)numVertices);

    glFlush();
}