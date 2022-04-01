#include "entity.h"
#include <random>
Entity::Entity(const float& x, const float& y, const float& width, const float& height, const Texture* texture,
	const float& movementSpeed, CollisionBox& hitCollision, const Constants::vec4& color) :
	Rectangle{ x, y, width, height, texture, true, color }, m_movementSpeed{ movementSpeed },m_hitCollision{ &hitCollision } {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::entity_cpp, &mS_objectsCount);
#endif

	m_hitCollision->setX(Object::x() + m_hitCollision->x());
	m_hitCollision->setY(Object::y() + m_hitCollision->y());
	m_hitCollision->updatePreviousX();
	m_hitCollision->updatePreviousY();
}

Entity::~Entity() {
#ifdef _DEBUG
	if (debugDestructor()) {
		DEBUG_DESTRUCTOR_OBJ(this, Source_Files::entity_cpp);
		setDebugDestructor(false);
	}
#endif 
	delete m_hitCollision;
}

void Entity::update(std::vector<std::vector<Entity*>*>& entities, std::vector<std::vector<BasicBlock*>*>& basicBlocks) {
	if (!m_isJumping) {
		m_isFalling = true;
	}
}

void Entity::moveHorizontally() {
	if (m_movementLeft) {
		setX(x() - m_movementSpeed);
	}
	else if (m_movementRight) {
		setX(x() + m_movementSpeed);
	}
}
void Entity::moveVertically() {
	if (m_isFalling && !m_isJumping) {
		setY(y() - m_gravity);
	}
	else if (m_isJumping && (m_currentJumpSeconds < m_jumpSeconds)) {
		m_currentJumpSeconds += 0.01f;
		setY(y() + m_movementSpeed);
		if (m_currentJumpSeconds >= m_jumpSeconds) {
			m_isJumping = false;
			m_isFalling = true;
			m_currentJumpSeconds = 0;
		}
	}

}

float Entity::setX(const float& x) {
	float xDistance{ Rectangle::setX(x) };
	m_hitCollision->setX(m_hitCollision->x() + xDistance);
	return xDistance;
}
float Entity::setY(const float& y) {
	float yDistance{ Rectangle::setY(y) };
	m_hitCollision->setY(m_hitCollision->y() + yDistance);
	return yDistance;
}

void Entity::setWidth(const float& width) {
	// de modificat mai tarziu
	float diff{ width - Rectangle::width()  };
	float yesyesYes{ (m_hitCollision->x() - x() ) / Rectangle::width() * diff };
	float nonono{ (x2() - m_hitCollision->x2() ) / Rectangle::width() * diff };
	m_hitCollision->setWidth(m_hitCollision->width() - yesyesYes - nonono + diff);
	m_hitCollision->setX(m_hitCollision->x() + yesyesYes);
	Rectangle::setWidth(width);
}
void Entity::setHeight(const float& height) {
	// de modificat mai tarziu
	float diff{ height - Rectangle::height() };
	float yesyesYes{ (m_hitCollision->y() - y()) / Rectangle::height() * diff };
	float nonono{ (y2() - m_hitCollision->y2()) / Rectangle::height() * diff };
	m_hitCollision->setHeight(m_hitCollision->height() - yesyesYes - nonono + diff);
	m_hitCollision->setY(m_hitCollision->y() + yesyesYes);
	Rectangle::setHeight(height);
}

// checks and reacts to collision to basicBlock
// daca e glitch verific
void Entity::checkHorizontally(BasicBlock& basicBlock) {
	const Directions::Direction& isCollide{ m_hitCollision->isCollideAfterMovingHorizontally(basicBlock) };
	if (isCollide == Directions::LEFT) {
		setX(basicBlock.x2() + x() - m_hitCollision->x());
	}
	else if (isCollide == Directions::RIGHT) {
		setX(basicBlock.x() - width() + x2() - m_hitCollision->x2() );
	}
}
void Entity::checkVertically(BasicBlock& basicBlock) {
	const Directions::Direction& isCollide{ m_hitCollision->isCollideAfterMovingVertically(basicBlock) };
	if (isCollide == Directions::UP) {
		setY(basicBlock.y() - height() + y2() - m_hitCollision->y2());
	}
	else if (isCollide == Directions::DOWN) {
		setY(basicBlock.y2() + y() - m_hitCollision->y());
		m_isFalling = false;
	}
}