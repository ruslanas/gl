/**
 * @author Ruslanas Balciunas <ruslanas.com@gmail.com>
 */

#include <iostream>
#include <cstdio>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>

#include "Vec3.h"
#include "UniformBlock.h"
#include "util.h"

#define BUFFER_OFFSET(offset) ((void *)(offset))

enum VAO_IDs {
    Triangles, NumVAOs
};

enum Buffer_IDs {
    ArrayBuffer, NumBuffers
};

enum Attrib_IDs {
    vPosition = 0
};

GLuint VAOs[NumVAOs]; // Vertex array objects
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 3;

void init(void) {

    // allocate vertex array object names
    glGenVertexArrays(NumVAOs, VAOs);

    // activate previously created vertex-array
    glBindVertexArray(VAOs[Triangles]);

    Vec3 vecArray[] = {
        Vec3(-0.9, -0.9, 0),
        Vec3(0.85, -0.9, 0),
        Vec3(-0.9, 0.85, 0)
    };

    Matrix4 mat = Matrix4();

    mat.makeRotationY(-60 * M_PI / 180);

    GLfloat vertices[NumVertices][3];

    for (unsigned i = 0; i < NumVertices; i++) {
        Vec3 vec = vecArray[i].applyMatrix(mat);
        vertices[i][0] = (GLfloat) vec.x;
        vertices[i][1] = (GLfloat) vec.y;
        vertices[i][2] = (GLfloat) vec.z;
    }

    glGenBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);

    // allocate OpenGL server memory for storing data
    glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vPosition);
    
    GLuint program = prepareShaders();
    
    UniformBlock uBlock = UniformBlock(program, (char*)"UniformBlock");
    uBlock.append(mat);
}

void display() {
    glClearColor(0, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // select array for use as vertex data
    glBindVertexArray(VAOs[Triangles]);

    // send vertex data to OpenGL pipeline
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    glFlush();
}

int main(int argc, char**argv) {

    glutInit(&argc, argv);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenGL");

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cout << "Glew init err: " << glewGetErrorString(err) << std::endl;
        exit(1);
    }

    std::cout << "GLEW version: " << glewGetString(GLEW_VERSION) << std::endl;

    if (!GLEW_ARB_shader_objects || !GLEW_ARB_fragment_shader
            || !GLEW_ARB_vertex_shader || !GLEW_ARB_shading_language_100) {
        std::cout << "Unsupported extensions" << std::endl;
        exit(1);
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
