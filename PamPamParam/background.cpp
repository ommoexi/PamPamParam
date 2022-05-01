#include "background.h"

Background::Background(const float& x, const float& y, const float& width, const float& height, const Texture* texture,
	const float& isAffectedByCamera) :
	Rectangle{ x,  y, width,  height,  texture,isAffectedByCamera } {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::entity_cpp, &mS_objectsCount);
#endif
}
Background::~Background() {
#ifdef _DEBUG
	if (debugDestructor()) {
		DEBUG_DESTRUCTOR_OBJ(this, Source_Files::background_cpp);
		setDebugDestructor(false);
	}
#endif
}