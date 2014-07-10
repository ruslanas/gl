/* 
 * File:   Application.cpp
 * Author: Ruslanas
 * 
 * Created on 10 July 2014, 03:40
 */

#include "Application.h"
#include "Box.h"
#include "Scene.h"
#include "UniformBlock.h"

int loadSource(char *filename, GLcharARB ** shaderSource) {
    size_t size;
    FILE *source = fopen(filename, "rb");

    if (source == NULL) {
        fprintf(stderr, "GLSL file not found\n");
        exit(1);
    }

    fseek(source, 0, SEEK_END);
    size = ftell(source);
    rewind(source);

    GLchar * string;

    // allocate memory
    string = (GLchar *) malloc(size * sizeof (GLchar));

    if (string == 0) {
        fprintf(stderr, "Error: Out of memory\n");
        exit(1);
    }

    fread(string, size, 1, source);
    fclose(source);

    *shaderSource = string;

    return size;
}

Application::Application() {
}

Application::~Application() {
}

void Application::init(Scene& scene) {

    // allocate vertex array object names
    GLuint arr;
    glGenVertexArrays(1, &arr);

    // activate previously created vertex-array
    glBindVertexArray(arr);

    fprintf(stdout, "Vertex array bound: %d\n", arr);

    scene.array = arr;

    Box box = Box(.5, .5, .5);
    scene.add(box);

    GLuint program = loadShaders();

    Matrix4 mat = Matrix4(); // create identity matrix
    mat.makeRotationY(-60 * M_PI / 180);

    Matrix4 rotZ = Matrix4();
    rotZ.makeRotationZ(-60 * M_PI / 180);

    mat = mat * rotZ;

    UniformBlock uBlock = UniformBlock(program, (char*) "UniformBlock");
    uBlock.append(mat);

}

void Application::loop() {
    glutMainLoop();
}

GLhandleARB Application::loadShaders() {

    GLuint vShader, fShader;

    vShader = glCreateShader(GL_VERTEX_SHADER);
    fShader = glCreateShader(GL_FRAGMENT_SHADER);

    size_t size;

    GLcharARB * vShaderSource;
    GLcharARB * fShaderSource;

    size = loadSource((char *) "glsl/vertex.glsl", &vShaderSource);

    glShaderSource(vShader, 1, (const GLcharARB**) &vShaderSource, (GLint *) & size);

    // Compile
    glCompileShader(vShader);

    int compiled = 0, length = 0, laux = 0;
    glGetObjectParameterivARB(vShader, GL_COMPILE_STATUS, &compiled);
    glGetObjectParameterivARB(vShader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);

    if (compiled != GL_TRUE) {
        fprintf(stderr, "Failed to compile vertex shader\n");
    }

    if (length > 0) {
        char *logString = (GLchar *) malloc(length * sizeof (GLchar));
        glGetInfoLogARB(vShader, length, &laux, logString);
        std::cout << logString << std::endl;
    }

    size = loadSource((char *) "glsl/fragment.glsl", &fShaderSource);

    glShaderSourceARB(fShader, 1, (const GLcharARB**) &fShaderSource, (GLint *) & size);
    glCompileShaderARB(fShader);
    
    length = 0;
    glGetObjectParameterivARB(fShader, GL_COMPILE_STATUS, &compiled);
    glGetObjectParameterivARB(fShader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);

    if (compiled != GL_TRUE) {
        fprintf(stderr, "Failed to compile fragment shader\n");
    }

    if (length > 0) {
        char *logString = (GLchar *) malloc(length * sizeof (GLcharARB));
        glGetInfoLogARB(fShader, length, &laux, logString);
        fprintf(stdout, "%s\n", logString);
    }

    GLuint program = glCreateProgram();

    glAttachShader(program, vShader);
    glAttachShader(program, fShader);

    glLinkProgram(program);

    glGetObjectParameterivARB(program, GL_OBJECT_LINK_STATUS_ARB, &compiled);
    glGetObjectParameterivARB(program, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);

    if (length > 0) {
        GLchar *logString = (GLchar *) malloc(length * sizeof (GLchar));
        glGetInfoLogARB(program, length, &laux, logString);
        std::cout << logString << std::endl;
    }

    glUseProgram(program);

    return program;
}
