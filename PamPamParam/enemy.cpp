#include "enemy.h"

Enemy::Enemy(const float& x, const float& y, const float& width, const float& height, const Texture* texture,
	const float& movementSpeed, CollisionBox& hitCollision, const Constants::vec4& color) :
	Entity{ x,y,width,height,texture,movementSpeed, hitCollision, color }
{
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::enemy_cpp, &mS_objectsCount);
#endif
}

Enemy::~Enemy() {
#ifdef _DEBUG
	if (debugDestructor()) {
		DEBUG_DESTRUCTOR_OBJ(this, Source_Files::entity_cpp);
		setDebugDestructor(false);
	}
#endif 
}

void Enemy::update(std::vector<std::vector<Entity*>*>& entities, std::vector<std::vector<BasicBlock*>*>& basicBlocks) {
	Entity::update(entities, basicBlocks);
	int v1 = rand() % 100;
	if (m_nowCounter > m_maxCounter) {
		m_nowCounter = 0;
		if (v1 < 50) {
			setMovementLeft(true);
			setMovementRight(false);
		}
		else {
			setMovementRight(true);
			setMovementLeft(false);
		}
	}
	else {
		m_nowCounter++;
	}
	if (v1 > 50 && v1 < 60) {
		setMovementUp(true);
	}
	else {
		setMovementUp(false);
	}
	moveHorizontally();
	moveVertically();
	for (auto& blocks : basicBlocks) {
		for (auto& block : *blocks) {
			checkHorizontally(*block);
			checkVertically(*block);
		}
	}
	setJumpIfNotfalling();
	hitCollision().updatePreviousX();
	hitCollision().updatePreviousY();
}
