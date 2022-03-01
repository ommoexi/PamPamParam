#include "entity.h"
#include <random>
Entity::Entity(const float& x, const float& y, const float& width, const float& height, const Texture* texture, 
	const float& movementSpeed, const Constants::vec4& color) :
	Rectangle{ x, y, width, height, texture, color }, m_movementSpeed{ movementSpeed } {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::entity_cpp, &mS_objectsCount);
#endif 
}

Entity::~Entity() {
#ifdef _DEBUG
	if (debugDestructor()) {
		DEBUG_DESTRUCTOR_OBJ(this, Source_Files::entity_cpp);
		setDebugDestructor(false);
	}

#endif 
}

void Entity::update(std::vector<std::vector<Entity*>*>& entities, std::vector<std::vector<BasicBlock*>*>& basicBlocks) {
	if (m_movementUp) {
		setY(y() + m_movementSpeed);
	}
	else if (m_movementDown) {
		setY(y() - m_movementSpeed);
	}
	if (m_movementLeft) {
		setX(x() - m_movementSpeed);
	}
	else if (m_movementRight) {
		setX(x() + m_movementSpeed);
	}
}