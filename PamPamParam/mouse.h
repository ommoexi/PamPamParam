#pragma once
#include "utils.h"
#include "camera.h"
#include "rectangle.h"

class Mouse {
private:
	Camera* m_cam;
	float m_x{};
	float m_y{};
	float m_xWithCam{m_x + m_cam->x()}; // with camMovement
	float m_yWithCam{m_y + m_cam->y()}; // with camMovement
	float m_xWithCamZoom{m_x + m_cam->xWithZoom()};
	float m_yWithCamZoom{ m_x + m_cam->yWithZoom() };
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

	const float& xWithCam() const {
		return m_xWithCam;
	}

	const float& yWithCam() const {
		return m_yWithCam;
	}

	const bool& isLeftClick() const {
		return m_leftClick;
	}

	const bool& isRightClick() const {
		return m_rightClick;
	}

	void setX(const float& value) {
		m_x = value - Constants::windowStretch;
		m_xWithCam = m_x + m_cam->x();
		m_xWithCamZoom = m_x + m_cam->xWithZoom();
	}

	void setY(const float& value) {
		m_y = value - Constants::windowStretch;
		m_yWithCam =  m_y + m_cam->y();
		m_yWithCamZoom = m_y + m_cam->yWithZoom();
	}

	void setLeftClick(const bool& value) {
		m_leftClick = value;
	}

	void setRightClick(const bool& value) {
		m_rightClick = value;
	}

	bool isCollide(const Rectangle& rect);
	bool isCollideWithCam(const Rectangle& rect);
	bool isCollideWithCamAndZoom(const Rectangle& rect);


#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};