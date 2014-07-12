/**
 * @author Ruslanas Balciunas <ruslanas.com@gmail.com>
 */

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>

#include "Application.h"
#include "Vec3.h"
#include "UniformBlock.h"
#include "Box.h"
#include "Scene.h"

Scene scene;

void display() {
    scene.render();
}

int main(int argc, char**argv) {

    glutInit(&argc, argv);

    Application app = Application();

    app.init(scene);
    app.loadFragmentShader((char*) "glsl/fragment.glsl");
    app.loadVertexShader((char*) "glsl/vertex.glsl");
    app.linkProgram();

    app.setActiveUniformBlock((char*) "UniformBlock");

    Matrix4 mat = Matrix4(); // create identity matrix
    mat.makeRotationX(60 * M_PI / 180);
    Matrix4 mat2 = Matrix4();
    mat2.makeRotationY(30 * M_PI / 180);
    Matrix4 mat3 = Matrix4();
    mat3.makeRotationZ(-30 * M_PI / 180);

    // append model transformation matrix to uniform block
    app.uBlock.append(mat * mat2 * mat3);
    // append light direction vector to uniform block

    Vec3 light = Vec3(0, 0.5, 1);
    app.uBlock.append(light);

    Vec3 blue = Vec3(0, 0, 1);
    app.uBlock.append(blue);
    
    app.uBlock.transfere();
    
    Box box = Box(0.5, 0.5, 0.5);
    box.applyMatrix(mat * mat2 * mat3);
    
    scene.add(box);
    Box box2 = Box(-0.5, -0.5, -0.5);
    box2.applyMatrix(mat2);
    scene.add(box2);
    scene.add(Box(-0.25, 1, 0.25));

    glutDisplayFunc(display);

    app.loop();

    return 0;
}
