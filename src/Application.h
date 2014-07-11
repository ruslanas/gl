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
    void linkProgram();
    int loadSource(char *filename, GLcharARB ** shaderSource);
    void loop();
    void setActiveUniformBlock(char* name);
    
    void loadVertexShader(char* file);
    void loadFragmentShader(char* file);
    
private:
    GLuint program;
    GLuint fShader;
    GLuint vShader;
    Scene mScene;
};

#endif	/* APPLICATION_H */

