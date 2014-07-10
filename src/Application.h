/* 
 * File:   Application.h
 * Author: Ruslanas
 *
 * Created on 10 July 2014, 03:40
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include "Scene.h"
#include "UniformBlock.h"

class Application {
public:
    UniformBlock uBlock;
    
    Application();
    Application(const Application& orig);
    virtual ~Application();
    
    void init(Scene& scene);
    void loadShaders();
    int loadSource(char *filename, GLcharARB ** shaderSource);
    void loop();
    
private:
    GLuint program;
};

#endif	/* APPLICATION_H */

