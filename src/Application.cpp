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

Application::Application() {
}

Application::~Application() {
}

void Application::init(Scene& scene) {
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

    mScene = scene;
}

void Application::setActiveUniformBlock(char* name) {
    uBlock = UniformBlock(this->program, (char*) name);
}

void Application::loop() {
    glutMainLoop();
}

void Application::loadFragmentShader(char* file) {
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLchar * fShaderSource;
    size_t size = loadSource(file, &fShaderSource);

    glShaderSource(fShader, 1, (const GLcharARB**) &fShaderSource, (GLint *) & size);
    glCompileShader(fShader);
    int length = 0, compiled = 0, laux = 0;
    glGetObjectParameterivARB(fShader, GL_COMPILE_STATUS, &compiled);
    glGetObjectParameterivARB(fShader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);

    if (compiled != GL_TRUE) {
        fprintf(stderr, "Failed to compile shader %s\n", file);
    }

    if (length > 0) {
        char *logString = (GLchar *) malloc(length * sizeof (GLcharARB));
        glGetInfoLogARB(fShader, length, &laux, logString);
        fprintf(stdout, "%s\n", logString);
    }

}

void Application::loadVertexShader(char* file) {
    vShader = glCreateShader(GL_VERTEX_SHADER);
    GLchar * vShaderSource;
    size_t size = loadSource(file, &vShaderSource);

    glShaderSource(vShader, 1, (const GLcharARB**) &vShaderSource, (GLint *) & size);
    glCompileShader(vShader);
    int length = 0, compiled = 0, laux = 0;
    glGetObjectParameterivARB(vShader, GL_COMPILE_STATUS, &compiled);
    glGetObjectParameterivARB(vShader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);

    if (compiled != GL_TRUE) {
        fprintf(stderr, "Failed to compile shader %s\n", file);
    }

    if (length > 0) {
        char *logString = (GLchar *) malloc(length * sizeof (GLcharARB));
        glGetInfoLogARB(vShader, length, &laux, logString);
        fprintf(stdout, "%s\n", logString);
    }

}

void Application::linkProgram() {
    program = glCreateProgram();

    glAttachShader(program, vShader);
    glAttachShader(program, fShader);

    glLinkProgram(program);

    int length = 0, linked = 0, laux = 0;
    glGetObjectParameterivARB(program, GL_OBJECT_LINK_STATUS_ARB, &linked);
    glGetObjectParameterivARB(program, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);

    if (length > 0) {
        GLchar *logString = (GLchar *) malloc(length * sizeof (GLchar));
        glGetInfoLogARB(program, length, &laux, logString);
        std::cout << logString << std::endl;
    }

    glUseProgram(program);
}

int Application::loadSource(char *filename, GLchar ** shaderSource) {
    size_t size;
    FILE *source = fopen(filename, "rb");

    if (source == NULL) {
        fprintf(stderr, "GLSL file not found\n");
        exit(EXIT_FAILURE);
    }

    fseek(source, 0, SEEK_END);
    size = ftell(source);
    rewind(source);

    GLchar * string;

    // allocate memory
    string = (GLchar *) malloc(size * sizeof (GLchar));

    if (string == 0) {
        fprintf(stderr, "Error: Out of memory\n");
        exit(EXIT_FAILURE);
    }

    fread(string, size, 1, source);
    fclose(source);

    *shaderSource = string;

    return size;
}
