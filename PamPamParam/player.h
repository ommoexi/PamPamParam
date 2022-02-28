#pragma once
#include "entity.h"
class Player : public Entity {
private:
	// must implement these animations when creating a new player or crash 

	const static inline std::string mS_standingAnimationString{"stand"};

public:
	Player(const float& x, const float& y, const float& width, const float& height,const Animation& standingAnimation,
		const Constants::vec4& color = Colors::white);
	virtual ~Player();

	void update(std::vector<std::vector<Entity*>*>& entities, std::vector<std::vector<BasicBlock*>*>& basicBlocks) override;

	static const std::string& standingAnimationString() {
		return mS_standingAnimationString;
	}

	Player& setStandingAnimation(const Animation& animation) {
		setAnimation(animation, mS_standingAnimationString);
		return *this;
	}

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};