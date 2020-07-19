
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "./engine/graphics/Shader.h"

/*Small testing program
to push limits of a single draw call*/

GLFWwindow* getWindow();

const int WIDTH = 800;
const int HEIGHT = 600;
const int NUM_POINTS = 2;//caps out around 600k to 700k points
const int DRAW_MODE = GL_LINES;
float vertices[NUM_POINTS * 2];

int main(){
    for(int i = 0;i<NUM_POINTS*2;i+=2){
        vertices[i] = ((float)i)/((float)NUM_POINTS);
        vertices[i+1] = ((float)i)/((float)NUM_POINTS);
    }

    GLFWwindow* window = getWindow();

    if(glewInit() != GLEW_OK){
        std::cout << "Error glewInit" << std::endl;
    }

    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    Shader pointShader("./build/shaders/shaderPoint.vs","./build/shaders/shaderPoint.fs");
    std::cout << glGetError() << "shader" << std::endl;



    GLuint vao = 0;
    glGenVertexArrays(1,&vao);

    GLuint vbo = 0;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    glBindVertexArray(vao);
    //vbo is already binded

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        2,
        GL_FLOAT,
        GL_FALSE,
        0,
        0
    );

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    std::cout << glGetError() << "VAO and VBO" << std::endl;

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        
        if(glfwGetKey(window,GLFW_KEY_ESCAPE)){
            glfwSetWindowShouldClose(window,true);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearColor(0.0f,0.0f,0.0f,1.0f);

        pointShader.use();

        glBindVertexArray(vao);
        //glEnableVertexAttribArray(0);
        glDrawArrays(DRAW_MODE,0,NUM_POINTS);
        //glDisableVertexAttribArray(0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }
    glDeleteBuffers(1,&vbo);
    std::cout << glGetError() << "vbo delete" << std::endl;

    glDeleteVertexArrays(1,&vao);
    std::cout << glGetError() << "vao delete" << std::endl;

    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << glGetError() << std::endl;

    return 0;
}


GLFWwindow* getWindow(){
    if(!glfwInit()){
        std::cout << "Error window" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE,GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(WIDTH,HEIGHT,"Program",NULL,NULL);

    if(!window){
        std::cout << "error window 2" << std::endl;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    return window;
}