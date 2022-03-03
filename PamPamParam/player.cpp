#include "player.h"


Player::Player(const float& x, const float& y, const float& width, const float& height,const Animation& standingAnimation,
	const float& movementSpeed, Rectangle& topCollision, Rectangle& rightCollision, Rectangle& bottomCollision,
	Rectangle& leftCollision, Rectangle& hitCollision, const Constants::vec4& color)
	: Entity{x,y,width,height, &standingAnimation.currentTexture(), movementSpeed, topCollision, rightCollision,
	bottomCollision, leftCollision, hitCollision, color} {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::player_cpp, &mS_objectsCount);
#endif

	setStandingAnimation(standingAnimation);
}

void Player::update(std::vector<std::vector<Entity*>*>& entities, std::vector<std::vector<BasicBlock*>*>& basicBlocks) {
	setMovementByInput();
	Entity::update(entities, basicBlocks);
	updateAnimation(mS_standingAnimationString);
	for (auto& blocks : basicBlocks) {
		for (auto& block : *blocks) {
			check(*block);
		}
	}
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