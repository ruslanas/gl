/* 
 * File:   Mesh.h
 * Author: Ruslanas
 *
 * Created on 09 July 2014, 22:41
 */

#ifndef MESH_H
#define	MESH_H

#include "Vec3.h"

class Mesh {
public:
    Mesh();
    Mesh(const Mesh& orig);
    virtual ~Mesh();
    
    void addVertex(const Vec3& vertex);
    void addFace(const Vec3& v1, const Vec3& v2, const Vec3& v3);
    void print();
    int numVertices() const;
    
protected:
    Vec3* vertices;
    int count;
    
private:
};

#endif	/* MESH_H */

