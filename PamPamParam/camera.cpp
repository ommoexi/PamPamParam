#include "camera.h"


Camera::Camera(float x, float y) : m_x{ x }, m_y{ y }{
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::camera_cpp, &mS_objectsCount);
#endif
}

Camera::~Camera() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::camera_cpp);
#endif
}

void Camera::setX(const float& value) {
	m_x = value;
	m_transform[6] = -normalizeX(value);
}
void Camera::setY(const float& value) {
	m_y = value;
	m_transform[7] = -normalizeY(value);
}