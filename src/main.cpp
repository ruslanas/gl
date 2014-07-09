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
#include "Box.h"
#include "Scene.h"
#include "util.h"

#define BUFFER_OFFSET(offset) ((void *)(offset))

Scene scene;

enum VAO_IDs {
    Triangles, NumVAOs
};

enum Buffer_IDs {
    ArrayBuffer, NumBuffers
};

enum Attrib_IDs {
    vPosition = 0,
    vNormal = 1
};

GLuint VAOs[NumVAOs]; // Vertex array objects
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 18;

void init(void) {
    scene = Scene();

    // allocate vertex array object names
    glGenVertexArrays(NumVAOs, VAOs);

    // activate previously created vertex-array
    glBindVertexArray(VAOs[Triangles]);

    Box box = Box(1.0, 1.0, 1.0);
    scene.add(box);
    
    scene.array = VAOs[Triangles];
    
    size_t size = sizeof(GLfloat) * box.numVertices * 3;
    GLfloat* vertices = (GLfloat*)malloc(size);

    box.loadVertices(vertices);

    glGenBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);

    // allocate OpenGL server memory for storing data
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    // unbind from target
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // ...and bind again
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    
    // tell how to interpret data
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vPosition);

    // load normals
    
    GLfloat* normals = (GLfloat*)malloc(size);
    
    if(normals == NULL) {
        fprintf(stderr, "Unable to allocate memory");
        exit(EXIT_FAILURE);
    }
    
    box.loadNormals(normals);
    
    GLuint normalBuffer;
    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, size, normals, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(vNormal);
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    
    GLuint program = prepareShaders();
    
    Matrix4 mat = Matrix4(); // create identity matrix
    mat.makeRotationY(-60 * M_PI / 180);

    Matrix4 rotZ = Matrix4();
    rotZ.makeRotationZ(-60 * M_PI / 180);
    
    mat = mat * rotZ;
    
    UniformBlock uBlock = UniformBlock(program, (char*)"UniformBlock");
    uBlock.append(mat);
}

void display() {
    scene.render();
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
