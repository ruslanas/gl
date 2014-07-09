/* 
 * File:   Scene.h
 * Author: Ruslanas
 *
 * Created on 09 July 2014, 20:17
 */

#ifndef SCENE_H
#define	SCENE_H

#include "Box.h"

class Scene {
public:
    Scene();
    Scene(const Scene& orig);
    virtual ~Scene();
    
    void render();
    void add(const Box& box);
    // quick fix
    GLuint array;
    
private:
    GLsizei numVertices;
};

#endif	/* SCENE_H */

