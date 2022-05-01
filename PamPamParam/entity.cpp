#include "entity.h"
#include <random>
Entity::Entity(const float& x, const float& y, const float& width, const float& height, const Stats& stats,
	CollisionBox& hitCollision, const Animation& moveLeftAnim, const Animation& moveRightAnim, const Animation& idleLeftAnim,
	const Animation& idleRightAnim, const Texture& jumpTextureRight, const Texture& fallTextureRight, const Texture& jumpTextureLeft,
	const Texture& fallTextureLeft) :
	Rectangle{ x, y, width, height, &idleRightAnim.currentTexture(), true, Colors::white }, m_stats{ stats },
	m_hitCollision{ &hitCollision }, m_moveLeftAnimation{ moveLeftAnim }, m_moveRightAnimation{ moveRightAnim },
	m_idleLeftAnimation{ idleLeftAnim }, m_idleRightAnimation{ idleRightAnim }, m_jumpTextureRight{ &jumpTextureRight }, 
	m_fallTextureRight{ &fallTextureRight }, m_jumpTextureLeft{ &jumpTextureLeft }, m_fallTextureLeft{ &fallTextureLeft } {
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
	hitCollision().updatePreviousX();
	hitCollision().updatePreviousY();

	moveVertically();
	moveHorizontally();

	//be sure not to iterate basicBlock on children
	for (auto& blocks : basicBlocks) {
		for (auto& block : *blocks) {
			check(*block);
		}
	}

	if (isFalling() || isJumping()) {
		if (isFacingRight()) {
			setTexture(m_jumpTextureRight);
		}
		else {
			setTexture(m_jumpTextureLeft);
		}
	}
	else if (movementLeft()) {
		updateAnimation(m_moveLeftAnimation);
	}
	else if (movementRight()) {
		updateAnimation(m_moveRightAnimation);
	}
	else if (isFacingRight()) {
		updateAnimation(m_idleRightAnimation);
	}
	else {
		updateAnimation(m_idleLeftAnimation);
	}

	if (!m_isFalling && m_movementUp) {
		m_isJumping = true;
	}
	else if (!m_isJumping) {
		m_isFalling = true;
	}

}

void Entity::moveHorizontally() {
	if (m_movementLeft) {
		setX(x() - m_stats.movementSpeed());
		setFacingRight(false);
	}
	else if (m_movementRight) {
		setX(x() + m_stats.movementSpeed());
		setFacingRight(true);
	}
}
void Entity::moveVertically() {
	if (m_isFalling && !m_isJumping) {
		setY(y() - m_gravity);
	}
	else if (m_isJumping) {
		m_currentJumpSeconds -= 0.01f;
		setY(y() + m_stats.jumpSpeed() *  m_currentJumpSeconds - m_gravity);
		if (m_currentJumpSeconds <= 0) {
			setJumpFalse();
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

//void Entity::setHitCollisionX(const float& x) {
//	
//	float xDistance{ m_hitCollision->setX(x) };
//	Rectangle::setX(Entity::x() + xDistance);
//
//}
//void Entity::setHitCollisionY(const float& y) {
//	float xDistance{ m_hitCollision->setY(y) };
//	Rectangle::setY(Entity::y() + xDistance);
//}

void Entity::setWidth(const float& width) {
	// de modificat mai tarziu
	float diff{ width - Rectangle::width() };
	float yesyesYes{ (m_hitCollision->x() - x()) / Rectangle::width() * diff };
	float nonono{ (x2() - m_hitCollision->x2()) / Rectangle::width() * diff };
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

void Entity::check(BasicBlock& basicBlock) {
	const Directions::Direction& entIsCollideHorizontally{ m_hitCollision->isCollideAfterMovingHorizontally(basicBlock) };
	const Directions::Direction& entIsCollideVertically{ m_hitCollision->isCollideAfterMovingVertically(basicBlock) };

	if (entIsCollideHorizontally == Directions::LEFT ) {
		setX(basicBlock.x2() + x() - m_hitCollision->x() + 1);
	}
	else if (entIsCollideHorizontally == Directions::RIGHT ) {
		setX(basicBlock.x() - width() + x2() - m_hitCollision->x2() - 1);
	}
	if (entIsCollideVertically == Directions::UP ) {
		setY(basicBlock.y() - height() + y2() - m_hitCollision->y2() - 1);
		m_currentJumpSeconds -= 0.2f;
	}
	else if (entIsCollideVertically == Directions::DOWN ) {
		setY(basicBlock.y2() + y() - m_hitCollision->y() + 1);
		stopJump();
	}
}

