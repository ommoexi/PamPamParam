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
// call zoom after setting x and y otherwise it won't update the transform matrix
void Camera::setX(const float& value) {
	m_x = value;
	m_xNormalized = normalizeCoord(value);
}
void Camera::setY(const float& value) {
	m_y = value;
	m_yNormalized = normalizeCoord(value);
}

void Camera::setZoom(const float& value) {
	m_zoom = value;
	m_zoomNormalized = normalizeCoord(value) ;
	float x{ m_xNormalized * m_zoomNormalized };
	float y{ m_yNormalized * m_zoomNormalized };
	m_transform[0] = m_zoomNormalized;
	m_transform[4] = m_zoomNormalized;
	m_transform[6] = -x;
	m_transform[7] = -y;
	updateXWithZoom();
	updateYWithZoom();
}


void Camera::updateXWithZoom() {
	m_xWithZoom = m_x * m_transform[0] + m_y * m_transform[3];
}
void Camera::updateYWithZoom() {
	m_yWithZoom = m_y * m_transform[4] + m_x * m_transform[1];
}