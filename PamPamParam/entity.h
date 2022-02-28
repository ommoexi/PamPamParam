#pragma once
#include "rectangle.h"
#include "basicBlock.h"
#include <array>

class Entity :public Rectangle {
private:

protected:
public:
	Entity(const Entity& entity) = delete;
	Entity& operator=(const Entity& entity) = delete;
	Entity(const float& x, const float& y, const float& width, const float& height, const Texture* texture,
		const Constants::vec4& color = Colors::white);
	virtual ~Entity();

	virtual void update(std::vector<std::vector<Entity*>*>& entities,std::vector<std::vector<BasicBlock*>*>& basicBlocks);

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};