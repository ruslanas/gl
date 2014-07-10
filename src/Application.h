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

class Application {
public:
    Application();
    Application(const Application& orig);
    virtual ~Application();
    
    void init(Scene& scene);
    GLhandleARB loadShaders();
    void loop();
    
private:
};

#endif	/* APPLICATION_H */

