#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"

#include "./Dependencies/imgui/imgui.h"
#include "./Dependencies/imgui/imgui_impl_glfw.h"
#include "./Dependencies/imgui/imgui_impl_opengl3.h"

#include <string>

#include "./Object.h"
#include "./Physics2D.h"
#include "./AABB.h"
#include "./Scene.h"
#include "./Shader.h"
#include "./StaticRenderer.h"
#include "./Texture.h"
#include "./Window.h"
#include "./ObjectContact.h"

class SceneCollisions : public Scene {
    private:
        std::string m_title;
        bool m_active;
        Shader* m_shader;
        Texture* m_texture;
        Object* m_player;
        Object* m_other;
        ObjectContact m_contactResolver;

    public:
        SceneCollisions();
        SceneCollisions(Shader* shader, Texture* texture, const float vertices[]);
        ~SceneCollisions();

        std::string getSceneTitle() const;
        bool isActive() const;
        void render(Window* window);
        void update(Window* window);
        void setActive(bool active);
        void renderGUI();
    private:
        void input(Window* window);


};
