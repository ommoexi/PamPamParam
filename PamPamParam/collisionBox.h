#pragma once
#include "utils.h"
#include "rectangle.h"
#ifdef _DEBUG
using CollisionBox = Rectangle;
#else

class CollisionBox {
private:
	float m_x;
	float m_y;
	float m_x2;
	float m_y2;
	float m_width;
	float m_height;
	float m_previousX {m_x};
	float m_previousX2 {m_x2};
	float m_previousY {m_y};
	float m_previousY2 {m_y2};
public:
	CollisionBox(const float& x, const float& y, const float& width, const float& height);
	~CollisionBox();

	const float& x() const {
		return m_x;
	}

	const float& y() const {
		return m_y;
	}

	const float& x2() const {
		return m_x2;
	}

	const float& y2() const {
		return m_y2;
	}

	const float& width() const {
		return m_width;
	}

	const float& height() const {
		return m_height;
	}

	const float& previousX2() const {
		return m_previousX2;
	}
	const float& previousY2() const {
		return m_previousY2;
	}

	void updatePreviousX() {
		m_previousX = x();
		m_previousX2 = m_x2;
	}
	void updatePreviousY() {
		m_previousY = y();
		m_previousY2 = m_y2;
	}

	void setX(const float& value) {
		m_x = value;
		m_x2 = value + m_width;
	}

	void setY(const float& value) {
		m_y = value;
		m_y2 = value + m_height;
	}

	void setWidth(const float& value) {
		m_width = value;
		m_x2 = m_x + value;
	}

	void setHeight(const float& value) {
		m_height = value;
		m_y2 = m_y + value;
	}

	bool isCollide(const Rectangle& rect);
	bool isCollide(const CollisionBox& collisionBox);

	const std::string& isCollideAfterMovingHorizontally(const Rectangle& rect) const ;
	const std::string& isCollideAfterMovingVertically(const Rectangle& rect) const ;
	const std::string& isCollideAfterMovingHorizontally(const CollisionBox& collisionBox) const ;
	const std::string& isCollideAfterMovingVertically(const CollisionBox& collisionBox) const;
#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};

#endif
};
#endif