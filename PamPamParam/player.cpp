#include "player.h"


Player::Player(const float& x, const float& y, const float& width, const float& height,const float& movementSpeed, 
	CollisionBox& hitCollision)
	: Entity{x,y,width,height, movementSpeed, hitCollision, Textures::animations::dogWalkingLeft,
Textures::animations::dogWalkingRight, Textures::animations::dogIdleLeft, Textures::animations::dogIdleRight } {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::player_cpp, &mS_objectsCount);
#endif

}

void Player::update(std::vector<std::vector<Entity*>*>& entities, std::vector<std::vector<BasicBlock*>*>& basicBlocks) {
	setMovementByInput();
	Entity::update(entities, basicBlocks);

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