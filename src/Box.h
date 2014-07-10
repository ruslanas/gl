/* 
 * File:   Box.h
 * Author: Ruslanas
 *
 * Created on 08 July 2014, 17:03
 */

#ifndef BOX_H
#define	BOX_H

#include <GL/glut.h>
#include "Vec3.h"
#include "Mesh.h"

class Box : public Mesh {
public:
    Box(double _length, double _width, double _depth);
    Box(const Box& orig);
    virtual ~Box();

private:
    double length, width, depth;
};

#endif	/* BOX_H */

