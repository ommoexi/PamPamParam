#include "entity.h"
#include <random>
Entity::Entity(const float& x, const float& y, const float& width, const float& height, const Texture* texture,
	const float& movementSpeed, Rectangle& topCollision, Rectangle& rightCollision, Rectangle& bottomCollision,
	Rectangle& leftCollision, Rectangle& hitCollision, const Constants::vec4& color) :
	Rectangle{ x, y, width, height, texture, color }, m_movementSpeed{ movementSpeed }, m_topCollision{ &topCollision },
	m_rightCollision{ &rightCollision }, m_bottomCollision{ &bottomCollision }, m_leftCollision{ &leftCollision },
	m_hitCollision{ &hitCollision } {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::entity_cpp, &mS_objectsCount);
#endif

	m_topCollision->setX(Object::x() + m_topCollision->x());
	m_rightCollision->setX(Object::x() + m_rightCollision->x());
	m_bottomCollision->setX(Object::x() + m_bottomCollision->x());
	m_leftCollision->setX(Object::x() + m_leftCollision->x());
	m_hitCollision->setX(Object::x() + m_hitCollision->x());

	m_topCollision->setY(Object::y() + m_topCollision->y());
	m_rightCollision->setY(Object::y() + m_rightCollision->y());
	m_bottomCollision->setY(Object::y() + m_bottomCollision->y());
	m_leftCollision->setY(Object::y() + m_leftCollision->y());
	m_hitCollision->setY(Object::y() + m_hitCollision->y());
}

Entity::~Entity() {
#ifdef _DEBUG
	if (debugDestructor()) {
		DEBUG_DESTRUCTOR_OBJ(this, Source_Files::entity_cpp);
		setDebugDestructor(false);
	}
#endif 
}

void Entity::update(std::vector<std::vector<Entity*>*>& entities, std::vector<std::vector<BasicBlock*>*>& basicBlocks) {
	if (m_movementUp) {
		setY(y() + m_movementSpeed);
	}
	else if (m_movementDown) {
		setY(y() - m_movementSpeed);
	}
	if (m_movementLeft) {
		setX(x() - m_movementSpeed);
	}
	else if (m_movementRight) {
		setX(x() + m_movementSpeed);
	}
}

float Entity::setX(const float& x) {
	float xDistance{ Rectangle::setX(x) };

	m_topCollision->setX(m_topCollision->x() + xDistance);
	m_rightCollision->setX(m_rightCollision->x() + xDistance);
	m_bottomCollision->setX(m_bottomCollision->x() + xDistance);
	m_leftCollision->setX(m_leftCollision->x() + xDistance);
	m_hitCollision->setX(m_hitCollision->x() + xDistance);
	return xDistance;
}
float Entity::setY(const float& y) {
	float yDistance{ Rectangle::setY(y) };
	m_topCollision->setY(m_topCollision->y() + yDistance);
	m_rightCollision->setY(m_rightCollision->y() + yDistance);
	m_bottomCollision->setY(m_bottomCollision->y() + yDistance);
	m_leftCollision->setY(m_leftCollision->y() + yDistance);
	m_hitCollision->setY(m_hitCollision->y() + yDistance);
	return yDistance;
}

void Entity::check(BasicBlock& basicBlock) {
	if (m_rightCollision->isCollide(basicBlock)) {
		setX(x() - m_movementSpeed);
	}
	else if (m_leftCollision->isCollide(basicBlock)) {
		setX(x() + m_movementSpeed);
	}
	else if (m_topCollision->isCollide(basicBlock)) {
		setY(y() - m_movementSpeed);
	}
	else if (m_bottomCollision->isCollide(basicBlock)) {
		setY(y() + m_movementSpeed);
	}
}