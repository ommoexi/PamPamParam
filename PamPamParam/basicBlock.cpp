#include "basicBlock.h"

BasicBlock::BasicBlock(const float& x, const float& y, const float& width, const float& height, const Texture* texture,
	const Constants::vec4& color)
	: Rectangle{ x, y, width, height, texture, true, color } {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::basicBlock_cpp, &mS_objectsCount);
#endif 
}

BasicBlock::~BasicBlock() {
#ifdef _DEBUG
	if (debugDestructor()) {
		DEBUG_DESTRUCTOR_OBJ(this, Source_Files::basicBlock_cpp);
		setDebugDestructor(false);
	}
#endif 
}
