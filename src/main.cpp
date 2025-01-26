#include <Glew/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];

//GL Error Handling
void printShaderLog(GLuint shader){
    int len = 0;
    int chWrittn = 0;
    char* log;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

    if (len > 0){
        log = (char*)malloc(len);
        glGetShaderInfoLog(shader, len, &chWrittn, log);
        std::cout << "Shader Info Log" << log << std::endl;
        free(log);
    }
}

void printProgramLog(GLuint prog){
    int len = 0;
    int chWrittn = 0;
    char* log;
    glGetShaderiv(prog, GL_INFO_LOG_LENGTH, &len);

    if (len > 0){
        log = (char*)malloc(len);
        glGetShaderInfoLog(prog, len, &chWrittn, log);
        std::cout << "Shader Info Log" << log << std::endl;
        free(log);
    }
}

bool checkOpenGLError(){
    bool foundError = false;
    GLuint glErr = glGetError();
    while(glErr != GL_NO_ERROR) {
        std::cout << "glError: " << glErr << std::endl;
        foundError = true;
        glErr = glGetError();
    }
    return foundError;
}

// Read shader glsl files
std::string readShaderSource(const char* filePath){
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);
    std::string line;

    while(!fileStream.eof()){
        std::getline(fileStream, line);
        content.append(line + "\n");
    }
    fileStream.close();
    return content;
}

GLuint createShaderProgram(){
    GLint vertCompiled;
    GLint fragCompiled;
    GLint linked;

    std::string vertShaderString = readShaderSource("res/shaders/basic_point/vertShader.glsl");
    std::string fragShaderString = readShaderSource("res/shaders/basic_point/fragShader.glsl");

    const char* vshaderSource = vertShaderString.c_str();
    const char* fshaderSource = fragShaderString.c_str();

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vshaderSource, nullptr);
    glShaderSource(fShader, 1, &fshaderSource, nullptr);

    // Catch Errors During Compilation
    glCompileShader(vShader);
    checkOpenGLError();
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
    if (vertCompiled != 1){
        std::cout << "Vertex Compilation failed" << std::endl;
        printShaderLog(vShader);
    }

    glCompileShader(fShader);
    checkOpenGLError();
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
    if(fragCompiled != 1){
        std::cout << "Fragment Compilation failed" << std::endl;
        printShaderLog(fShader);
    }

    //Catch errors while linking shaders
    GLuint vfProgram = glCreateProgram();

    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);
    checkOpenGLError();

    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
    if (linked != 1){
        std::cout << "Shader Program Link Step Failed" << std::endl;
        printProgramLog(vfProgram);
    }
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
    glDrawArrays(GL_TRIANGLES, 0, 3);
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