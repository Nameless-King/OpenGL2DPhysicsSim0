#pragma once

#include "./Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"

class CameraController {
	private:
		glm::mat4 m_viewMatrix;
		glm::vec2 m_cameraPos;
		float m_zoom;
	public:
		CameraController();
		CameraController(glm::vec2 pos);
		~CameraController();
		glm::mat4* getViewMatrix();
		void setCameraPos(float px,float py);
		void setCameraPos(glm::vec2 pos);
		void setCameraZoom(float zoom);
		glm::vec2 getCameraPos();
		float getCameraZoom();
};
