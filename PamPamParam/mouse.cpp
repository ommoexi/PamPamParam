#include "mouse.h"

Mouse::Mouse(Camera& cam) : m_cam{ &cam } {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::mouse_cpp, &mS_objectsCount);
#endif
}
Mouse::~Mouse() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::mouse_cpp);
#endif
}