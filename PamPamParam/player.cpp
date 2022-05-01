#include "player.h"


Player::Player(const float& x, const float& y, const float& width, const float& height,const Stats& stats, 
	CollisionBox& hitCollision)
	: Entity{x,y,width,height, stats, hitCollision, Textures::animations::dogWalkingLeft,
Textures::animations::dogWalkingRight, Textures::animations::dogIdleLeft, Textures::animations::dogIdleRight,
*Textures::animationV::dogWalkingRight[4], *Textures::animationV::dogWalkingRight[4], 
*Textures::animationV::dogWalkingLeft[4], *Textures::animationV::dogWalkingLeft[4] } {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::player_cpp, &mS_objectsCount);
#endif

}

void Player::update(std::vector<std::vector<Entity*>*>& entities, std::vector<std::vector<BasicBlock*>*>& basicBlocks) {
	setMovementByInput();
	Entity::update(entities, basicBlocks);

	if (Input::mouse.isLeftClick()) {
		if (isFacingRight()) {
			m_projectiles.push_back(new Projectile{ hitCollision().x2(), (hitCollision().y() + hitCollision().y2()) / 2, 50,50,
				Textures::animationV::dogIdleRight[0], true, 50, 0, 1.8f });
		}
		else {
			m_projectiles.push_back(new Projectile{ hitCollision().x(), (hitCollision().y() + hitCollision().y2()) / 2, 50,50,
			Textures::animationV::dogIdleLeft[0], true, -50, 0, 1.8f });
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
	}
	else if (Input::keyD) {
		setMovementRight(true);
		setMovementLeft(false);
	}
	else {
		setMovementRight(false);
		setMovementLeft(false);
	}
}