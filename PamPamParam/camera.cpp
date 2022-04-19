#include "camera.h"


Camera::Camera(float x, float y, float zoom) : m_x{ x }, m_y{ y }{
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::camera_cpp, &mS_objectsCount);
#endif
	setZoom(zoom);
}

Camera::~Camera() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::camera_cpp);
#endif
}
// call zoom after setting x and y otherwise it won't update the transform matrix
void Camera::setX(const float& value) {
	m_previousX = m_x;
	m_x = value;
	m_xNormalized = normalizeCoord(value);
}
void Camera::setY(const float& value) {
	m_previousY = m_y;
	m_y = value;
	m_yNormalized = normalizeCoord(value);
}

void Camera::setZoom(const float& value) {
	m_zoom = value;
	m_zoomNormalized = normalizeCoord(value) ;
	m_xWithZoom = getXWithZoom(m_x);
	m_yWithZoom = getYWithZoom(m_y);
}

// for mouse collision only
float Camera::getXWithZoom(const float& x) const {
	if (m_transform[0] == 0) {
		return 0;
	}
	return m_transform[0] * x;
}
// for mouse collision only
float Camera::getYWithZoom(const float& y) const {
	if (m_transform[4] == 0) {
		return 0;
	}
	return m_transform[4] * y;
}

void Camera::update() {
	float x{ m_xNormalized * m_zoomNormalized };
	float y{ m_yNormalized * m_zoomNormalized };
	m_transform[0] = m_zoomNormalized;
	m_transform[4] = m_zoomNormalized;
	m_transform[6] = -x;
	m_transform[7] = -y;
}