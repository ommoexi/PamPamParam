#pragma once
#include "utils.h"
#include "camera.h"
#include "rectangle.h"

class Mouse {
private:
	float m_x{};
	float m_y{};
	float m_previousX{ m_x };
	float m_previousY{ m_y };
	bool m_leftClick{};
	bool m_rightClick{};
	Rectangle* m_dragRect{ nullptr };
public:
	Mouse();
	virtual ~Mouse();

	const float& x() const {
		return m_x;
	}

	const float& y() const {
		return m_y;
	}

	const bool& isLeftClick() const {
		return m_leftClick;
	}

	const bool& isRightClick() const {
		return m_rightClick;
	}

	void setX(const float& value) {
		m_previousX = m_x;
		m_x = value - Constants::windowStretch;
	}

	void setY(const float& value) {
		m_previousY = m_y;
		m_y = value - Constants::windowStretch;
	}

	void setLeftClick(const bool& value) {
		m_leftClick = value;
	}

	void setRightClick(const bool& value) {
		m_rightClick = value;
	}

	bool isCollide(const Rectangle& rect);
	bool isCollideWithCamMovement(const Rectangle& rect, const Camera& cam);
	bool isCollideWithCamMovementAndZoom(const Rectangle& rect, const Camera& cam);


	void dragRect(Rectangle& rect, const Camera& cam);
	void update(const Camera& cam);


#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};