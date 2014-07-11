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
    end_ptr = 0;
    count = 0;
    numVertices = 0;
}

Scene::Scene(const Scene& orig) {
    end_ptr = 0;
    count = orig.count;
    numVertices = orig.numVertices;
}

Scene::~Scene() {
}

void Scene::add(const Mesh& mesh) {
    meshes[count] = mesh;
    numVertices += mesh.numVertices();
    
    GLuint arr;
    glGenVertexArrays(1, &arr);

    vertexArrays[end_ptr] = arr;
    end_ptr++;
    
    // activate previously created vertex-array
    glBindVertexArray(arr);
    
    // load vertex data into GPU memory
    mesh.loadVertices();
    mesh.loadNormals();
    
}

void Scene::render() {
    
    std::cout << "Rendering scene..." << std::endl;
    
    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //glEnable(GL_CULL_FACE);
    //glEnable(GL_DEPTH_TEST);
    //glDepthMask(GL_TRUE);

    for(int i=0;i<end_ptr;i++) {
        // select array for use as vertex data
        glBindVertexArray(vertexArrays[i]);

        fprintf(stdout, "Vertex array bound: %d\n", vertexArrays[i]);

        // send vertex data to OpenGL pipeline.
        // take NumVertices, start from 0th element in vertex array
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)numVertices);

        GLenum err = glGetError();
        if(err != GL_NO_ERROR) {
            const GLubyte* msg = gluErrorString(err);
            fprintf(stderr, "Last known GL error: %s\n", msg);
        }
    }
    glFlush();
}
