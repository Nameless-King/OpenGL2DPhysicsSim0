
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"

#include <iostream>

#include "./engine/io/GWindow.h"
#include "./engine/io/GInput.h"
#include "./engine/scene/SceneManager.h"
#include "./engine/graphics/Shader.h"
#include "./engine/graphics/Texture.h"
#include "./engine/graphics/Renderer.h"

#include "./SceneCollisions.h"
#include "./SceneSpring.h"
#include "./SceneForces.h"
#include "./SceneTest.h"
#include "./SceneOBB.h"

void input();
void cameraInput(GWindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userparam);

const int WIDTH = 800;
const int HEIGHT = 600;
int zoom = 1.0f;
    
GWindow gameWindow(WIDTH, HEIGHT, "Game");

int main(){

    gameWindow.setFramebufferSizeCallback(framebuffer_size_callback);
    gameWindow.setClearColor(glm::vec4(0.0f,1.0f,0.0f,1.0f));

    if(glewInit() != GLEW_OK){
        std::cout << "Error glewInit" << std::endl;
        return EXIT_FAILURE;
    }

    //glEnable(GL_DEBUG_OUTPUT);
    //glDebugMessageCallback(MessageCallback,0);

    SceneManager::init(gameWindow.getWindow(), true);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    Shader shader("./shaders/shaderQuad.vs","./shaders/shaderQuad.fs");
    
    Texture textureWhite("./textures/white.png");
    Texture textureCircle("./textures/circle.png");

    Renderer::init();

    GInput::setContext(gameWindow.getWindow());

    SceneCollisions scene0(&shader, &textureCircle);
    SceneSpring scene1(&shader, &textureCircle);
    SceneForces scene2(&shader, &textureWhite);
    SceneTest scene3(&shader, &textureWhite);
    SceneOBB scene4(&shader, &textureWhite);

    SceneManager::registerScene(&scene0);
    SceneManager::registerScene(&scene1);
    SceneManager::registerScene(&scene2);
    SceneManager::registerScene(&scene3);
    SceneManager::registerScene(&scene4);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    SceneManager::setCurrentScene(-1);

    std::cout << "Initial Error Code: " << glGetError() << std::endl;

    while(!gameWindow.windowShouldClose()){
        //Gui initialization  and creation
        SceneManager::start();
        SceneManager::renderMenu();
        gameWindow.displayWindowStats();
        SceneManager::renderCurrentSceneGUI();

        //start of frame
        GInput::update();
        gameWindow.pollEvents();
        input();
        cameraInput(&gameWindow);

        SceneManager::updateCurrentScene(&gameWindow);
       
        gameWindow.clear();
        SceneManager::renderCurrentScene(&gameWindow);

        SceneManager::finalize();

        gameWindow.swapBuffers();

        
    }
    Renderer::destroy();
    SceneManager::destroy();

    std::cout << "Terminating Error Code: " << glGetError() << std::endl;

    return EXIT_SUCCESS;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height);
    gameWindow.resize(width,height);
}

void input(){
    if(GInput::isKeyDown(GLFW_KEY_ESCAPE)){
        gameWindow.closeWindow();
    }
}

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar* message, const void* userParam){
	
	 fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

void cameraInput(GWindow* window){
    float camSpeed = 2.0f;
    float zoomSpeed = 0.1f;

    glm::vec2 camPos = window->getCamera()->getCameraPos();

    float px = camPos.x;
    float py = camPos.y;
    float dz = window->getCamera()->getCameraZoom();

    if(GInput::isKeyDown(GLFW_KEY_W)){
        py += camSpeed;
    }else if(GInput::isKeyDown(GLFW_KEY_S)){
        py -= camSpeed;
    }

    if(GInput::isKeyDown(GLFW_KEY_D)){
        px += camSpeed;
    }else if (GInput::isKeyDown(GLFW_KEY_A)){
        px -= camSpeed;
    }

    int maxZoom = 12.0f;
    if(GInput::isKeyDown(GLFW_KEY_E)){
        if(dz < maxZoom){
            dz += zoomSpeed;
        }else{
            dz = maxZoom;
        }
    }else if (GInput::isKeyDown(GLFW_KEY_Q)){
        if(dz > 2.0f){
            dz -= zoomSpeed;
        }else{
            dz = 2.0f;
        }
    }

    window->getCamera()->setCameraPos(px,py);
    window->getCamera()->setCameraZoom(dz);
}