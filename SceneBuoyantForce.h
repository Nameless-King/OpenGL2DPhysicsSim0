#pragma once

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"

#include "./Dependencies/imgui/imgui.h"
#include "./Dependencies/imgui/imgui_impl_glfw.h"
#include "./Dependencies/imgui/imgui_impl_opengl3.h"

#include <string>

#include "./Object.h"
#include "./Scene.h"
#include "./Shader.h"
#include "./StaticRenderer.h"
#include "./Texture.h"
#include "./Window.h"

class SceneBuoyantForce : public Scene{
    private:
        std::string m_title;
        bool m_active;
        Shader* m_shader;
        Texture* m_texture;
        Object* m_object;
    
    public:
        SceneBuoyantForce();
        SceneBuoyantForce(Shader* shader,Texture* texture,const float vertices[]);
        ~SceneBuoyantForce();
        std::string getSceneTitle() const;
        bool isActive() const;
        void render(Window* window);
        void update(Window* window);
        void setActive(bool active);
        void renderGUI();
};