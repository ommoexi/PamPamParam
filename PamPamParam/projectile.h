#pragma once
#include "utils.h"
#include "rectangle.h"

class Projectile : public Rectangle {
private:
	float m_speedX;
	float m_speedY;
	float m_lifeSpan;


public:


	Projectile(const float& x, const float& y, const float& width, const float& height, const Texture* texture, const bool&
	isAffectedByCamera, const float& speedX, const float& speedY, const float& lifeSpan);
	virtual ~Projectile();

	void update();

	const float& lifeSpan() const {
		return m_lifeSpan;
	}

	void setLifeSpan(const float& value) {
		m_lifeSpan = value;
	}


#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};