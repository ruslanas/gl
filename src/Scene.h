/* 
 * File:   Scene.h
 * Author: Ruslanas
 *
 * Created on 09 July 2014, 20:17
 */

#ifndef SCENE_H
#define	SCENE_H

#include "Box.h"

#define MAX_VERTEX_ARRAYS 10

class Scene {
public:
    Scene();
    Scene(const Scene& orig);
    virtual ~Scene();
    
    void render();
    void add(const Mesh& mesh);
    // quick fix
    GLuint array;

private:
    int count;
    Mesh meshes[128];
    GLsizei numVertices;
    GLuint vertexArrays[MAX_VERTEX_ARRAYS];
    int end_ptr;
};

#endif	/* SCENE_H */

