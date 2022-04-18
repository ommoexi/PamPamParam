//#pragma once
//#include "entity.h"
//#include <random>
//
//class Enemy : public Entity {
//private:
//	int m_maxCounter{ 120 };
//	int m_nowCounter{};
//public:
//
//	Enemy(const float& x, const float& y, const float& width, const float& height, const Texture* texture,
//		const float& movementSpeed, CollisionBox& hitCollision, const Constants::vec4& color = Colors::white);
//	virtual ~Enemy();
//
//	virtual void update(std::vector<std::vector<Entity*>*>& entities, std::vector<std::vector<BasicBlock*>*>& basicBlocks) override;
//
//#ifdef _DEBUG
//private:
//	static inline ObjectsCount mS_objectsCount{};
//#endif
//};