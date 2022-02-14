#pragma once
#include "rectangle.h"

class BasicBlock : public Rectangle {
private:
protected:
public:
	BasicBlock(const BasicBlock& basicBlock) = delete;
	BasicBlock& operator=(const BasicBlock& basicBlock) = delete;
	BasicBlock(const float& x, const float& y, const float& width, const float& height, const Texture* texture,
		const Constants::vec4& color = Colors::white);
	virtual ~BasicBlock();

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};