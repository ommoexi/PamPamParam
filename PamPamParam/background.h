#pragma once
#include "utils.h"
#include "rectangle.h"

class Background : public Rectangle {
private:
public:
	Background(const float& x, const float& y, const float& width, const float& height, const Texture* texture, 
		const float& isAffectedByCamera);
	virtual ~Background();

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};