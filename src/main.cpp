/**
 * @author Ruslanas Balciunas <ruslanas.com@gmail.com>
 */

#include <cstdio>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>

#include "Application.h"
#include "Vec3.h"
#include "UniformBlock.h"
#include "Box.h"
#include "Scene.h"

#define BUFFER_OFFSET(offset) ((void *)(offset))

Scene scene;

void display() {
    scene.render();
}

int main(int argc, char**argv) {

    glutInit(&argc, argv);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("OpenGL Application");

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "GLEW version: %s\n", glewGetString(GLEW_VERSION));
    
    if (!GLEW_ARB_shader_objects || !GLEW_ARB_fragment_shader
            || !GLEW_ARB_vertex_shader || !GLEW_ARB_shading_language_100) {
        fprintf(stderr, "Unsupported extensions\n");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "GL version: %s\n", glGetString(GL_VERSION));

    Application app = Application();
    
    app.init(scene);
    
    Matrix4 mat = Matrix4(); // create identity matrix
    mat.makeRotationY(-60 * M_PI / 180);
    Matrix4 rotZ = Matrix4();
    rotZ.makeRotationZ(-60 * M_PI / 180);
    mat = mat * rotZ;

    app.loadFragmentShader((char*)"glsl/fragment.glsl");
    app.loadVertexShader((char*)"glsl/vertex.glsl");
    
    app.linkProgram();
    
    app.setActiveUniformBlock((char*)"UniformBlock");
    
    // append model transformation matrix to uniform block
    app.uBlock.append(mat);
    // append light direction vector to uniform block
    Vec3 light = Vec3(0, 0.5, 1);
    app.uBlock.append(light);
    
    Vec3 red = Vec3(1, 1, 0);
    app.uBlock.append(red);
    
    app.uBlock.transfere(); // copy to GPU memory
    
    Box box = Box(0.5, 1.0, 2.0);
    scene.add(box);
    
    // print some info to stdout
    box.print();
    
    glutDisplayFunc(display);

    app.loop();
    
    return 0;
}
