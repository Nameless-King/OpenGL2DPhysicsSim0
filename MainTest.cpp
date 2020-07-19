
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
#include "./SceneQuadTreeDemo.h"

void input();
void cameraInput(GWindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userparam);

const int WIDTH = 800;
const int HEIGHT = 600;
int zoom = 1.0f;
    
GWindow gameWindow(WIDTH, HEIGHT, "Game");

int main(){
    std::cout << "Program Start" << std::endl;
    
    gameWindow.setFramebufferSizeCallback(framebuffer_size_callback);
    gameWindow.setClearColor(glm::vec4(0.0f,0.0f,0.0f,1.0f));

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
    Texture textureRectangle("./textures/rectangle.png");

    Renderer::init();

    GInput::setContext(gameWindow.getWindow());

    SceneCollisions scene0(&shader, &textureCircle);
    SceneSpring scene1(&shader, &textureCircle);
    SceneForces scene2(&shader, &textureWhite);
    SceneTest scene3(&shader, &textureWhite);
    SceneOBB scene4(&shader, &textureWhite);
    SceneQuadTreeDemo scene5;

    SceneManager::registerScene(&scene0);
    SceneManager::registerScene(&scene1);
    SceneManager::registerScene(&scene2);
    SceneManager::registerScene(&scene3);
    SceneManager::registerScene(&scene4);
    SceneManager::registerScene(&scene5);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glPointSize(2.0f);

    SceneManager::setCurrentScene(-1);

    std::cout << "Initial Error Code: " << glGetError() << std::endl;

    while(!gameWindow.windowShouldClose()){
        /*
                                 .i;;;;i.                                  
                               iYcviii;vXY:                                
                             .YXi       .i1c.                              
                            .YC.     .    in7.                             
                           .vc.   ......   ;1c.                            
                           i7,   ..        .;1;                            
                          i7,   .. ...      .Y1i                           
                         ,7v     .6MMM@;     .YX,                          
                        .7;.   ..IMMMMMM1     :t7.                         
                       .;Y.     ;$MMMMMM9.     :tc.                        
                       vY.   .. .nMMM@MMU.      ;1v.                       
                      i7i   ...  .#MM@M@C. .....:71i                       
                     it:   ....   $MMM@9;.,i;;;i,;tti                      
                    :t7.  .....   0MMMWv.,iii:::,,;St.                     
                   .nC.   .....   IMMMQ..,::::::,.,czX.                    
                  .ct:   ....... .ZMMMI..,:::::::,,:76Y.                   
                  c2:   ......,i..Y$M@t..:::::::,,..inZY                   
                 vov   ......:ii..c$MBc..,,,,,,,,,,..iI9i                  
                i9Y   ......iii:..7@MA,..,,,,,,,,,....;AA.                 
               iIS.  ......:ii::..;@MI....,............;Ez.                
              .I9.  ......:i::::...8M1..................C0z.               
             .z9;  ......:i::::,.. .i:...................zWX.              
             vbv  ......,i::::,,.      ................. :AQY              
            c6Y.  .,...,::::,,..:t0@@QY. ................ :8bi             
           :6S. ..,,...,:::,,,..EMMMMMMI. ............... .;bZ,            
          :6o,  .,,,,..:::,,,..i#MMMMMM#v.................  YW2.           
         .n8i ..,,,,,,,::,,,,.. tMMMMM@C................... .1Wn           
         7Uc. .:::,,,,,::,,,,..   i1t;,..................... .UEi          
         7C...::::::::::::,,,,..        ....................  vSi.         
         ;1;...,,::::::,.........       ..................    Yz:          
          v97,.........                                     .voC.          
           izAotX7777777777777777777777777777777777777777Y7n92:            
             .;CoIIIIIUAA666666699999ZZZZZZZZZZZZZZZZZZZZ6ov.              
 
         * ADJUSTING THE ORDER OF OPERATIONS BELOW RESULTS IN IMGUI FPS DROP
         * WITH USER INTERACTION WITH WINDOW
         */

        //start of frame
        GInput::update();
        gameWindow.pollEvents();
        input();
        cameraInput(&gameWindow);

        //update scene logic, collision, physics, etc.
        SceneManager::updateCurrentScene(&gameWindow);

        //Clear screen and buffers
        gameWindow.clear();

        //imgui start new frame
        SceneManager::start();

        //render opengl
        SceneManager::renderCurrentScene(&gameWindow);

        //render scene guis
        SceneManager::renderMenu();
        gameWindow.displayWindowStats();
        SceneManager::renderCurrentSceneGUI();

        //render imgui onto screen
        SceneManager::render();
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