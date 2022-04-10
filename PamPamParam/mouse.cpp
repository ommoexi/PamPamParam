#include "mouse.h"

Mouse::Mouse() {
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
bool Mouse::isCollideWithCamMovement(const Rectangle& rect, const Camera& cam) {
	float mouseXWithCamMovement{ m_x + cam.x() };
	float mouseYWithCamMovement{ m_y + cam.y() };
	return (rect.x2() >= mouseXWithCamMovement && rect.x() <= mouseXWithCamMovement && rect.y2() >= mouseYWithCamMovement && rect.y() <= mouseYWithCamMovement);
}
bool Mouse::isCollideWithCamMovementAndZoom(const Rectangle& rect, const Camera& cam) {
	float x{ cam.getXWithZoom(rect.x(), rect.y()) };
	float x2{ cam.getXWithZoom(rect.x2(), rect.y2()) };
	float y{ cam.getYWithZoom(rect.x(), rect.y()) };
	float y2{ cam.getYWithZoom(rect.x2(), rect.y2()) };
	float mouseXWithCamZoom{ m_x + cam.xWithZoom() }; // zoom and movement
	float mouseYWithCamZoom{ m_y + cam.yWithZoom() }; // zoom and movement
	return (x2 >= mouseXWithCamZoom && x <= mouseXWithCamZoom && y2 >= mouseYWithCamZoom && y <= mouseYWithCamZoom);
}