#include "entity.h"

Entity::Entity(const float& x, const float& y, const float& width, const float& height, const Texture* texture,
	const std::map<std::string, Animation>* animations, const Constants::vec4& color) :
	Rectangle{ x, y, width, height, texture, animations, color } {
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

void Entity::update(std::vector<Entity*>& entities, std::vector<BasicBlock*>& basicBlocks) {
	updateAnimation(Textures::animations::animationString);
	for (auto& basicBlock : basicBlocks) {
		if (basicBlock) {
			if (isCollide(*basicBlock)) {
				basicBlock->setRemoveFromHandler(true);
				std::cout << " PLEASE DELETE \n";
			}
		}
	}
	for (auto& entity : entities) {

	}

}