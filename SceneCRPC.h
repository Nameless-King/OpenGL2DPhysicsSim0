#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"

#include "./Dependencies/imgui/imgui.h"
#include "./Dependencies/imgui/imgui_impl_glfw.h"
#include "./Dependencies/imgui/imgui_impl_opengl3.h"

#include <string>
#include <vector>

#include "./AABB.h"
#include "./Object.h"
#include "./Physics2D.h"
#include "./Scene.h"
#include "./Shader.h"
#include "./StaticRenderer.h"
#include "./Texture.h"
#include "./Window.h"

class SceneCRPC : public Scene{
	private:
		std::string m_title;
		bool m_active;
		bool m_useGravity;
		float m_gravity;
		float m_speed;
		Shader* m_shader;
		Texture* m_texture;
		std::vector<Object*> m_objs;
		Object* m_player;
		
	public:
		SceneCRPC();
		SceneCRPC(Shader* shader, Texture* texture, const float vertices[]);
		~SceneCRPC();
		inline std::string getSceneTitle() const { return m_title;}
		inline bool isActive() const {return m_active;}
		void render(Window* window);
		void update(Window* window);
		void setActive(bool active);
	
	private:
		void renderGUI();
		void input(Window* window);
};