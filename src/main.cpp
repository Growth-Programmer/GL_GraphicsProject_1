#include <Glew/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];

GLuint createShaderProgram(){
    const char* vshaderSource =
            "#version 430 \n"
            "void main(void) \n"
            "{gl_Position = vec4(0.0,0.0,0.0,1.0);}";

    const char* fshaderSource =
            "#version 430 \n"
            "out vec4 color; \n"
            "void main(void) \n"
            "{ if (gl_FragCoord.x < 395) color = vec4(0.0, 0.0, 1.0, 1.0); else color = vec4(1.0, 0.0, 0.0, 1.0);"
            "}";

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vshaderSource, nullptr);
    glShaderSource(fShader, 1, &fshaderSource, nullptr);
    glCompileShader(vShader);
    glCompileShader(fShader);

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);

    return vfProgram;
}

void init(GLFWwindow* window){
    renderingProgram = createShaderProgram();
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}
void display(GLFWwindow* window, double currentTime){
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.5,0.5,0.5,1.0);
    glUseProgram(renderingProgram);
    glPointSize(30.0f);
    glDrawArrays(GL_POINTS, 0, 1);
}

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    GLFWwindow* window = glfwCreateWindow(800,800,"TestWindow", nullptr,nullptr);
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK){
        exit(EXIT_FAILURE);
    }

    init(window);
    glfwSwapInterval(1);

    while(!glfwWindowShouldClose(window)){
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}