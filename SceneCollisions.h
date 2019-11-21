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
#include <vector>

#include "./Object.h"
#include "./Physics2D.h"
#include "./AABB.h"
#include "./Scene.h"
#include "./Shader.h"
#include "./StaticRenderer.h"
#include "./Texture.h"
#include "./Window.h"
#include "./ObjectContact.h"
#include "./ForceGravity.h"

class SceneCollisions : public Scene {
    private:
        std::string m_title;
        bool m_useGravity;
        Shader* m_shader;
        Texture* m_texture;
        Object* m_player;
        std::vector<Object*> m_objects;
        ObjectContact m_contactResolver;
        ForceGravity m_forceGravity;

    public:
        SceneCollisions();
        SceneCollisions(Shader* shader, Texture* texture, const float vertices[]);
        ~SceneCollisions();

        std::string getSceneTitle() const;
        void render(Window* window);
        void update(Window* window);
        void renderGUI();
    private:
        void input(Window* window);
        void checkBounds();


};
