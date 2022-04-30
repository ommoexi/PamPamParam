#pragma once
#include "entity.h"
#include "input.h"
class Player : public Entity {
private:

public:
	Player(const float& x, const float& y, const float& width, const float& height, const Stats& stats, 
		CollisionBox& hitCollision);
	virtual ~Player();

	void update(std::vector<std::vector<Entity*>*>& entities, std::vector<std::vector<BasicBlock*>*>& basicBlocks) override;


	void setMovementByInput();

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};