/* 
 * File:   Mesh.h
 * Author: Ruslanas
 *
 * Created on 09 July 2014, 22:41
 */

#ifndef MESH_H
#define	MESH_H

#include <GL/glut.h>

#include "Vec3.h"

class Mesh {
public:
    Mesh();
    Mesh(const Mesh& orig);
    virtual ~Mesh();
    
    void addVertex(const Vec3& vertex);
    void addVertex(const Vec3& vertex, const Vec3& normal);
    void addFace(const Vec3& v1, const Vec3& v2, const Vec3& v3);
    int numVertices() const;
    
    void loadVertices() const; // do not modify object state
    void loadNormals() const;
    
    
protected:
    GLfloat* vertices;
    GLfloat* normals;
    int count;
    
private:
};

#endif	/* MESH_H */

