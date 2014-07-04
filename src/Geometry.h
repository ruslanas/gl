/* 
 * File:   Geometry.h
 * Author: Ruslanas
 *
 * Created on 04 July 2014, 19:21
 */

#ifndef GEOMETRY_H
#define	GEOMETRY_H

#include <cstdlib>
#include <GL/glew.h>

class Geometry {
public:
    Geometry();
    Geometry(const Geometry& orig);
    virtual ~Geometry();
    void create();
private:

};

#endif	/* GEOMETRY_H */

