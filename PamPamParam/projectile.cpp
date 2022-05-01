#include "projectile.h"

Projectile::Projectile(const float& x, const float& y, const float& width, const float& height, const Texture* texture, const bool&
	isAffectedByCamera, const float& speedX, const float& speedY, const float& lifeSpan) : 
	Rectangle{x,y,width,height,texture, isAffectedByCamera, Colors::white},
	m_speedX{ speedX }, m_speedY{ speedY }, m_lifeSpan{ lifeSpan } {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::projectile_cpp, &mS_objectsCount);
#endif

}

Projectile::~Projectile() {
#ifdef _DEBUG
	if (debugDestructor()) {
		DEBUG_DESTRUCTOR_OBJ(this, Source_Files::projectile_cpp);
		setDebugDestructor(false);
	}
#endif 
}

void Projectile::update() {
	setX(x() + m_speedX);
	setY(y() + m_speedY);
	m_lifeSpan -= 0.01f;
	if (m_lifeSpan <= 0) {
		setRemoveFromVector(true);
	}
}