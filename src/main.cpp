#include <Glew/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];

void init (GLFWwindow* window){}
void display(GLFWwindow* window){
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.3,0.3,0.3,1.0);
}

// GL Error Handling
void printShaderLog(GLuint shader){
    int len;
    int chrsWrittn;
    char* log;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        log =(char*)malloc(len);
        glGetShaderInfoLog(shader, len, &chrsWrittn, log);
        std::cout << "Shader Info Log: " << log << std::endl;
        free(log);
    }
}

void printProgramLog(GLuint program){
    int len;
    int charsWrttn;
    char* log;
    glGetShaderiv(program, GL_INFO_LOG_LENGTH, &len);

    if (len > 0) {
        log = (char*)malloc(len);
        glGetProgramInfoLog(program, len, &charsWrttn, log);
        std::cout << "Program Info Log: " << log << std::endl;
        free(log);
    }
}

bool checkOpenGLError() {
    bool foundErr = false;
    GLuint glErr = glGetError();
    while(glErr != GL_NO_ERROR){
        std::cout << "GL Error: " << glErr << std::endl;
        glErr = glGetError();
        foundErr = true;
    }
    return foundErr;
}

int main () {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(600,600,"Test Graphics", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK){
        exit(EXIT_FAILURE);
    }

    init(window);
    glfwSwapInterval(1);

    while(!glfwWindowShouldClose(window)){
        display(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}