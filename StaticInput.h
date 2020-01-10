#pragma once

#include <GLFW/glfw3.h>

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"

class StaticInput{
    private:
        static const int FIRST_KEY_CODE = 32;
        static long s_window;
        static bool s_keys[];
        static bool s_mouseButtons[];
        static float s_mouseWheelX;
        static float s_mouseWheelY;

    public:
        static void setContext(long window);
        static bool isKeyDown(int key);
        static bool isKeyPressed(int key);
        static bool isKeyReleased(int key);
        static bool isMouseButtonDown(int button);
        static bool isMouseButtonPressed(int button);
        static bool isMouseButtonReleased(int button);
        static float getMouseX();
        static float getMouseY();
        static glm::vec2 getMouseXY();
        static float getWheelX();
        static float getWheelY();
        static glm::vec2 getWheelXY();
        static void update();

    private:
        static void setWheelX(float offset);
        static void setWheelY(float offset);

};