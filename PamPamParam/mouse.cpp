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

bool Mouse::isCollide(const Rectangle& rect) {
	return (rect.x2() >= m_x && rect.x() <= m_x && rect.y2() >= m_y && rect.y() <= m_y);
}
bool Mouse::isCollideWithCam(const Rectangle& rect) {
	return (rect.x2() >= m_xWithCam && rect.x() <= m_xWithCam && rect.y2() >= m_yWithCam && rect.y() <= m_yWithCam);
}
bool Mouse::isCollideWithCamAndZoom(const Rectangle& rect) {
	float x{ m_cam->getXWithZoom(rect.x(), rect.y()) };
	float x2{ m_cam->getXWithZoom(rect.x2(), rect.y2()) };
	float y{ m_cam->getYWithZoom(rect.x(), rect.y()) };
	float y2{ m_cam->getYWithZoom(rect.x2(), rect.y2()) };
	return (x2 >= m_xWithCamZoom && x <= m_xWithCamZoom && y2 >= m_yWithCamZoom && y <= m_yWithCamZoom);
}