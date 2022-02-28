#include "player.h"


Player::Player(const float& x, const float& y, const float& width, const float& height,const Animation& standingAnimation, 
	const Constants::vec4& color)
	: Entity{x,y,width,height, &standingAnimation.currentTexture(), color} {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::player_cpp, &mS_objectsCount);
#endif

	setStandingAnimation(standingAnimation);
}

void Player::update(std::vector<std::vector<Entity*>*>& entities, std::vector<std::vector<BasicBlock*>*>& basicBlocks) {
	//Entity::update(entities, basicBlocks);
	updateAnimation(mS_standingAnimationString);
}

Player::~Player() {
#ifdef _DEBUG
	if (debugDestructor()) {
		DEBUG_DESTRUCTOR_OBJ(this, Source_Files::player_cpp);
		setDebugDestructor(false);
	}

#endif
}