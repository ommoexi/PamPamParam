#include "player.h"


Player::Player(const float& x, const float& y, const float& width, const float& height,const Animation& standingAnimation,
	const float& movementSpeed, CollisionBox& hitCollision, const Constants::vec4& color)
	: Entity{x,y,width,height, &standingAnimation.currentTexture(), movementSpeed, hitCollision, color} {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::player_cpp, &mS_objectsCount);
#endif

	setStandingAnimation(standingAnimation);
}

void Player::update(std::vector<std::vector<Entity*>*>& entities, std::vector<std::vector<BasicBlock*>*>& basicBlocks) {
	Entity::update(entities, basicBlocks);
	setMovementByInput();
	moveHorizontally();
	moveVertically();
	updateAnimation(mS_standingAnimationString);
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

Player::~Player() {
#ifdef _DEBUG
	if (debugDestructor()) {
		DEBUG_DESTRUCTOR_OBJ(this, Source_Files::player_cpp);
		setDebugDestructor(false);
	}

#endif
}

void Player::setMovementByInput() {
	if (input::keyW) {
		setMovementUp(true);
		setMovementDown(false);
	}
	else if (input::keyS) {
		setMovementUp(false);
		setMovementDown(true);
	}
	else {
		setMovementUp(false);
		setMovementDown(false);
	}
	if (input::keyA) {
		setMovementLeft(true);
		setMovementRight(false);
	}
	else if (input::keyD) {
		setMovementRight(true);
		setMovementLeft(false);
	}
	else {
		setMovementRight(false);
		setMovementLeft(false);
	}
}