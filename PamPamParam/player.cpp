#include "player.h"


Player::Player(const float& x, const float& y, const float& width, const float& height,const Animation& rightWalk,const Animation& leftWalk,
	const Animation& idleRight, const Animation& idleLeft, const float& movementSpeed, CollisionBox& hitCollision, 
	const Constants::vec4& color)
	: Entity{x,y,width,height, &idleRight.currentTexture(), movementSpeed, hitCollision, color} {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::player_cpp, &mS_objectsCount);
#endif

	setAnimation(leftWalk, mS_walkLeftAnimationString);
	setAnimation(rightWalk, mS_walkRightAnimationString);
	setAnimation(idleRight, mS_idleRightAnimationString);
	setAnimation(idleLeft, mS_idleLeftAnimationString);
}

void Player::update(std::vector<std::vector<Entity*>*>& entities, std::vector<std::vector<BasicBlock*>*>& basicBlocks) {
	Entity::update(entities, basicBlocks);
	setMovementByInput();
	if (movementLeft()) {
		updateAnimation(mS_walkLeftAnimationString);
	}
	else if (movementRight()) {
		updateAnimation(mS_walkRightAnimationString);
	}
	else if(isFacingRight()) {
		updateAnimation(mS_idleRightAnimationString);
	}
	else {
		updateAnimation(mS_idleLeftAnimationString);
	}
	moveVertically();
	moveHorizontally();
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
	if (Input::keyW) {
		setMovementUp(true);
		setMovementDown(false);
	}
	else if (Input::keyS) {
		setMovementUp(false);
		setMovementDown(true);
	}
	else {
		setMovementUp(false);
		setMovementDown(false);
	}
	if (Input::keyA) {
		setMovementLeft(true);
		setMovementRight(false);
		setFacingRight(false);
	}
	else if (Input::keyD) {
		setMovementRight(true);
		setMovementLeft(false);
		setFacingRight(true);
	}
	else {
		setMovementRight(false);
		setMovementLeft(false);
	}
}