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

void Entity::update(std::vector<Object*>& objs) {
	for (size_t i{}; i < 10; i++) {

	}
	/*for (auto& obj : objs) {
		Rectangle& d{ dynamic_cast<Rectangle&>(*obj) };
		if (isCollide(d) && this != obj) {

		}
	}*/
}