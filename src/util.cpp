#include "util.h"

GLhandleARB prepareShaders() {
    
    GLuint vShader, fShader;

    vShader = glCreateShader(GL_VERTEX_SHADER);
    fShader = glCreateShader(GL_FRAGMENT_SHADER);

    size_t size;

    GLcharARB * vShaderSource;
    GLcharARB * fShaderSource;

    size = loadSource((char *) "glsl/vertex.glsl", &vShaderSource);

    std::cout << "Vertex shader size: " << size << std::endl;
    glShaderSource(vShader, 1, (const GLcharARB**) &vShaderSource, (GLint *)&size);

    // Compile
    glCompileShader(vShader);

    int compiled = 0, length = 0, laux = 0;
    glGetObjectParameterivARB(vShader, GL_COMPILE_STATUS, &compiled);
    glGetObjectParameterivARB(vShader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);

    if (compiled == GL_TRUE) {
        std::cout << "Vertex shader compiled successfully" << std::endl;
    }

    if (length > 0) {
        char *logString = (GLchar *) malloc(length * sizeof (GLcharARB));
        glGetInfoLogARB(vShader, length, &laux, logString);
        std::cout << "Log file length: " << length << std::endl;
        std::cout << logString << std::endl;
    }

    size = loadSource((char *) "glsl/fragment.glsl", &fShaderSource);
    std::cout << "Fragment shader size: " << size << std::endl;

    glShaderSourceARB(fShader, 1, (const GLcharARB**) &fShaderSource, (GLint *)&size);
    glCompileShaderARB(fShader);
    length = 0;
    glGetObjectParameterivARB(fShader, GL_COMPILE_STATUS, &compiled);
    glGetObjectParameterivARB(fShader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);

    if (compiled == GL_TRUE) {
        std::cout << "Fragment shader compiled successfully" << std::endl;
    }

    if (length > 0) {
        char *logString = (GLchar *) malloc(length * sizeof (GLcharARB));
        glGetInfoLogARB(fShader, length, &laux, logString);
        std::cout << "LOG: " << logString << std::endl;
    }

    GLuint program = glCreateProgram();
    
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);

    glLinkProgram(program);
    
    glGetObjectParameterivARB(program, GL_OBJECT_LINK_STATUS_ARB, &compiled);
    glGetObjectParameterivARB(program, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);
    
    GLchar *logString = (GLchar *) malloc(length * sizeof (GLchar));
    glGetInfoLogARB(vShader, length, &laux, logString);
    std::cout << "Link status log: " << logString << std::endl;

    glUseProgram(program);

    return program;
}

int loadSource(char *filename, GLcharARB ** shaderSource) {
    size_t size;
    FILE *source = fopen(filename, "rb");

    if (source == NULL) {
        std::cout << "File not found" << std::endl;
        exit(1);
    }

    fseek(source, 0, SEEK_END);
    size = ftell(source);
    rewind(source);
    
    GLcharARB * string;
    // allocate memory
    string = (GLcharARB *) malloc(size * sizeof (GLcharARB));
    
    if(string == 0) {
        printf("Error: Out of memory\n");
        exit(1);
    }
    
    fread(string, size, 1, source);
    fclose(source);

    *shaderSource = string;
    
    return size;
}
