#pragma once
#include "utils.h"
#include "camera.h"

class Mouse {
private:
	Camera* m_cam;
	float m_x{};
	float m_y{};
	float m_xPerspective{m_x + m_cam->x()};
	float m_yPerspective{m_y + m_cam->y()};
	bool m_leftClick{};
	bool m_rightClick{};
public:
	Mouse(Camera& cam);
	virtual ~Mouse();

	const float& x() const {
		return m_x;
	}

	const float& y() const {
		return m_y;
	}

	const float& xPerspective() const {
		return m_xPerspective;
	}

	const float& yPerspective() const {
		return m_yPerspective;
	}

	const bool& isLeftClick() const {
		return m_leftClick;
	}

	const bool& isRightClick() const {
		return m_rightClick;
	}

	void setX(const float& value) {
		m_x = value;
		m_xPerspective = value + m_cam->x();
	}

	void setY(const float& value) {
		m_y = value;
		m_yPerspective = value + m_cam->y();
	}

	void setLeftClick(const bool& value) {
		m_leftClick = value;
	}

	void setRightClick(const bool& value) {
		m_rightClick = value;
	}


#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};