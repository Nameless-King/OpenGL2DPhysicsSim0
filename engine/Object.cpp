#include "./Object.h"
Object::Object() :
	m_position(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_rotation(0.0f),
	m_scale(glm::vec3(1.0f, 1.0f, 1.0f)),
	m_localVertices(Renderer::getVertices()),
	m_numVertices(4),
	m_globalVertices(NULL),
	m_transformationChanged(false),
	m_bound(NULL),
	m_rigidbody(NULL) {
	m_globalVertices = new float[2 * m_numVertices];
	//m_globalVertices = (float*)malloc(2 * m_numVertices * sizeof(float));
	memcpy(m_globalVertices, m_localVertices, sizeof(float) * m_numVertices * 2);
	updateGlobalVertices();
}


Object::Object(glm::vec3 position, float rotation, glm::vec3 scale) :
	m_position(position),
	m_rotation(rotation),
	m_scale(scale),
	m_localVertices(Renderer::getVertices()),
	m_numVertices(4),
	m_globalVertices(NULL),
	m_transformationChanged(false),
	m_bound(NULL),
	m_rigidbody(NULL) {
	
	m_globalVertices = new float[2 * m_numVertices];
	//m_globalVertices = (float*)malloc(2 * m_numVertices * sizeof(float));
	memcpy(m_globalVertices, m_localVertices, sizeof(float) * m_numVertices * 2);
	/*for (int i = 0; i < m_numVertices * 2; i++) {
		*(m_globalVertices + i) = *(m_localVertices + i);
	}*/
	updateGlobalVertices();
}

Object::Object(const Object& object) :
	m_position(glm::vec3(object.m_position)),
	m_rotation(object.m_rotation),
	m_scale(glm::vec3(object.m_scale)),
	m_localVertices(Renderer::getVertices()),
	m_numVertices(4),
	m_globalVertices(new float[m_numVertices * 2]),
	m_transformationChanged(false),
	m_rigidbody(new Rigidbody2D(*object.m_rigidbody)) {
	switch (object.m_bound->getBoundingType()) {
	case BoundingType::AxisAligned:
		m_bound = new AABB(*((AABB*)object.m_bound));
		//m_bound = new AABB(*static_cast<AABB*>(object.m_bound));
		break;
	case BoundingType::Circle:
		// TODO : create Circle copy constructor
		//not currently being used so no an issue if it's nonexistent
		//m_bound = new Circle(*object.m_bound);
		break;
	case BoundingType::Oriented:
		m_bound = new OBB(*((OBB*)object.m_bound));
		//m_bound = new OBB(*static_cast<OBB*>(object.m_bound));
		break;
	case BoundingType::NA:
		m_bound = new Bound();
		break;
	default:
		std::cout << "Error: Undetectable BoundingType" << std::endl;
		break;
	}
	m_globalVertices = new float[2 * m_numVertices];
	//m_globalVertices = (float*)malloc(2 * m_numVertices * sizeof(float));
	memcpy(m_globalVertices, m_localVertices, sizeof(float) * m_numVertices * 2);
	updateGlobalVertices();
}

Object::~Object() {
	delete m_rigidbody;
	delete m_bound;
	delete[] m_globalVertices;
	//free((void*)m_globalVertices);
}


glm::mat4 Object::getModelMatrix() {
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, m_position);
	model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, m_scale);
	return model;
}

void Object::rotateDegrees(float degrees) {
	m_transformationChanged = true;
	//m_bound holds pointer to m_rotation
	m_rotation += degrees;
}

void Object::setPos(float xPos, float yPos, float zPos) {
	m_transformationChanged = true;
	m_position = glm::vec3(xPos, yPos, zPos);
}

void Object::setPos(float xPos, float yPos) {
	m_transformationChanged = true;
	m_position = glm::vec3(xPos, yPos, m_position.z);
}

void Object::setPos(glm::vec2 pos) {
	m_transformationChanged = true;
	m_position.x = pos.x;
	m_position.y = pos.y;
}

void Object::setRotation(float rot) {
	//m_bound holds pointer to m_rotation
	m_rotation = rot;
}

void Object::setScl(float xScl, float yScl, float zScl) {
	m_scale = glm::vec3(xScl, yScl, zScl);
}

void Object::setScl(float scl){
	m_scale = glm::vec3(scl,scl,scl);
}

void Object::addRigidbody2D(float mass) {
	m_rigidbody = new Rigidbody2D(&m_rotation,mass);
}

void Object::createBound(BoundingType type) {
	m_bound = new Bound(&m_position, &m_rotation, &m_scale, Renderer::getVertices(), type);
}


glm::vec2 Object::getPositionXY() {
	return glm::vec2(m_position.x, m_position.y);
}

glm::vec2 Object::getScaleXY() {
	return glm::vec2(m_scale.x, m_scale.y);
}

int Object::getNumVertices() {
	return m_numVertices;
}

const float* Object::getGlobalVertices() {
	if (m_transformationChanged) {
		updateGlobalVertices();
		m_transformationChanged = false;
	}
	return m_globalVertices;
}

void Object::updateGlobalVertices() {
	glm::mat4 modelMatrix = getModelMatrix();
	for (int i = 0; i < m_numVertices * 2; i += 2) {
		glm::vec4 pos(*(m_localVertices + i), *(m_localVertices + i + 1), 0.0f, 1.0f);
		glm::vec4 worldPos = modelMatrix * pos;
		*(m_globalVertices + i) = worldPos.x;
		*(m_globalVertices + i + 1) = worldPos.y;
	}
}

