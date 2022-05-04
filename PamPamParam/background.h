#pragma once
#include "utils.h"
#include "rectangle.h"

class Background : public Rectangle {
private:
	Animation m_animation;
public:
	Background(const float& x, const float& y, const float& width, const float& height, const Texture* texture, 
		const float& isAffectedByCamera);
	Background(const float& x, const float& y, const float& width, const float& height, const Animation& animation,
		const float& isAffectedByCamera);
	virtual ~Background();

	void update();

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};