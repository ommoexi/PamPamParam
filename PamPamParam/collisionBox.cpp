#include "collisionBox.h"
#ifndef _DEBUG

CollisionBox::CollisionBox(const float& x, const float& y, const float& width, const float& height) :
	m_x{ x }, m_y{ y }, m_x2{ x + width }, m_y2{ y + height }, m_width{ width }, m_height{ height }{
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::collisionBox_cpp, &mS_objectsCount);
#endif

}

bool CollisionBox::isCollide(const Rectangle& rect) {
	return (m_x2 >= rect.x() && m_x <= rect.x2() && m_y2 >= rect.y() && m_y <= rect.y2());
}
bool CollisionBox::isCollide(const CollisionBox& collisionBox) {
	return (m_x2 >= collisionBox.x() && m_x <= collisionBox.x2() && m_y2 >= collisionBox.y() && m_y <= collisionBox.y2());
}

CollisionBox::~CollisionBox() {
#ifdef _DEBUG

	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::collisionBox_cpp);
#endif
}

const std::string& CollisionBox::isCollideAfterMovingHorizontally(const Rectangle& rect) const {
	if (m_previousY < rect.y2() && m_previousY2 > rect.y()) { //check horizontally if 2 objects align
		if (m_previousX2 < rect.x2() && m_x2 > rect.x()) { // self is left obj is right
			return Directions::RIGHT;
		}
		else if (m_previousX > rect.x() && x() < rect.x2()) { // self is right obj is left
			return Directions::LEFT;

		}
	}
	return BasicNullTypes::string;
}
const std::string& CollisionBox::isCollideAfterMovingVertically(const Rectangle& rect) const {
	if (m_previousX < rect.x2() && m_previousX2 > rect.x()) { // check vertically if 2 objects align
		if (m_previousY2 < rect.y2() && m_y2 > rect.y()) { // self is down object is up
			return Directions::UP;
		}
		else if (m_previousY > rect.y() && y() < rect.y2()) {  //self is up object is down
			return Directions::DOWN;
		}
	}
	return BasicNullTypes::string;
}
const std::string& CollisionBox::isCollideAfterMovingHorizontally(const CollisionBox& collisionBox) const {
	if (m_previousY < collisionBox.y2() && m_previousY2 > collisionBox.y()) { //check horizontally if 2 objects align
		if (m_previousX2 < collisionBox.x2() && m_x2 > collisionBox.x()) { // self is left obj is right
			return Directions::RIGHT;
		}
		else if (m_previousX > collisionBox.x() && x() < collisionBox.x2()) { // self is right obj is left
			return Directions::LEFT;

		}
	}
	return BasicNullTypes::string;
}
const std::string& CollisionBox::isCollideAfterMovingVertically(const CollisionBox& collisionBox) const {
	if (m_previousX < collisionBox.x2() && m_previousX2 > collisionBox.x()) { // check vertically if 2 objects align
		if (m_previousY2 < collisionBox.y2() && m_y2 > collisionBox.y()) { // self is down object is up
			return Directions::UP;
		}
		else if (m_previousY > collisionBox.y() && y() < collisionBox.y2()) {  //self is up object is down
			return Directions::DOWN;
		}
	}
	return BasicNullTypes::string;
}
#endif