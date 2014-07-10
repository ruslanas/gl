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
    count = 0;
    numVertices = 0;
}

Scene::Scene(const Scene& orig) {
    count = orig.count;
    numVertices = orig.numVertices;
}

Scene::~Scene() {
}

void Scene::add(const Mesh& mesh) {
    meshes[count] = mesh;
    numVertices += mesh.numVertices();
    
    // load vertices and normals to GPU
    mesh.loadVertices();
    mesh.loadNormals();
}

void Scene::render() {
    
    std::cout << "Rendering scene..." << std::endl;
    
    glClearColor(0.7, 0.7, 0.7, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // select array for use as vertex data
    glBindVertexArray(array);
    
    fprintf(stdout, "Vertex array bound: %d\n", array);
    
    // send vertex data to OpenGL pipeline.
    // take NumVertices, start from 0th element in vertex array
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)numVertices);
    
    GLenum err = glGetError();
    if(err != GL_NO_ERROR) {
        const GLubyte* msg = gluErrorString(err);
        fprintf(stderr, "Last known GL error: %s\n", msg);
    }

    glFlush();
}