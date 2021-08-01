#include "./SceneBoundTest.h"

SceneBoundTest::SceneBoundTest():
	Scene("SceneBoundTest"),
	m_shader(NULL),
	m_texture(NULL){}
	
SceneBoundTest::SceneBoundTest(Shader* shader, Texture* texture):
	Scene("SceneBoundTest"),
	m_shader(shader),
	m_texture(texture){

	m_object = new Object(
		glm::vec2(0.0f,0.0f),
		0.0f,
		glm::vec2(1.0f,1.0f)
	);
	m_object->createBound(BoundingType::AxisAligned);

	addObject(m_object);
			
};

SceneBoundTest::~SceneBoundTest(){}


void SceneBoundTest::render(GWindow* window){
	Renderer::bind();
	m_shader->use();
	m_texture->bind();
	
	m_shader->setUniformMat4f("u_projection",window->getProjectionMatrix());
	m_shader->setUniformMat4f("u_view",window->getCamera()->getViewMatrix());
	
	ObjectRegistration* currentRegistry = m_firstObject;
	while(currentRegistry){
		m_shader->setUniformMat4f("u_model",currentRegistry->object->getModelMatrix());
		Renderer::renderObject();
		currentRegistry = currentRegistry->next;
	}
	
	m_texture->unbind();
	Renderer::unbind();

	//FACE DRAW
	Renderer::basicRenderBegin(BasicRenderMode::BRM_LINES);
	Bound* bound = m_object->getBound();
	Face* currentFace;
	glm::vec2 currentNormal;
	glm::vec2 midpoint;
	for(int i = 0;i<bound->getVertexCount();i++){
		currentFace = bound->getFaceInArray(i);
		float x1 = *(currentFace->x1)/100.0f;
		float y1 = *(currentFace->y1)/100.0f;
		float x2 = *(currentFace->x2)/100.0f;
		float y2 = *(currentFace->y2)/100.0f;
		Renderer::basicRenderPoint(x1,y1);
		Renderer::basicRenderPoint(x2,y2);

		midpoint = EngineMath::calcMidpoint(x1,y1,x2,y2);
		currentNormal = EngineMath::calcFaceNormal(x1,y1,x2,y2);
		currentNormal += midpoint;
		Renderer::basicRenderPoint(midpoint.x,midpoint.y);
		Renderer::basicRenderPoint(currentNormal.x,currentNormal.y);
	}
	Renderer::basicRenderEnd();

}

void SceneBoundTest::update(GWindow* window){
	startFrame();
	runPhysics(ImGui::GetIO().DeltaTime);
	input(window);
	m_object->updateGlobalVertices();
}

void SceneBoundTest::renderGUI(){
	ImGui::Begin(m_title.c_str());

	ImGui::End();
}
	
void SceneBoundTest::input(GWindow* window){
	float speed = 1.0f;
	glm::vec2 currentPosition = m_object->getPosition();

	if(GInput::isKeyDown(GLFW_KEY_UP)){
		currentPosition.y+=speed;
	}
	
	if(GInput::isKeyDown(GLFW_KEY_DOWN)){
		currentPosition.y-=speed;
	}

	if(GInput::isKeyDown(GLFW_KEY_RIGHT)){
		currentPosition.x += speed;
	}

	if(GInput::isKeyDown(GLFW_KEY_LEFT)){
		currentPosition.x -= speed;
	}
	
	m_object->setPosition(currentPosition);

	if(GInput::isKeyPressed(GLFW_KEY_R)){
		m_object->setRotation(0.0f);
	}

	if(GInput::isKeyDown(GLFW_KEY_T)){
		m_object->rotateDegrees(speed);
	}

}

void SceneBoundTest::runPhysics(float dt, GWindow* window){
	// m_forceGravity.updateForce(m_hangingObj,ImGui::GetIO().DeltaTime);
	integrate(ImGui::GetIO().DeltaTime);
	generateContacts();
}