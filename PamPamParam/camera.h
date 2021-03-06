#pragma once
#include "utils.h"
#include <iostream>



class Camera {
private:
	float m_x;
	float m_y;
	float m_previousX{ m_x };
	float m_previousY{ m_y };
	float m_xWithZoom{m_x};
	float m_yWithZoom{m_y};
	float m_zoom{Constants::windowStretch };
	float m_zoomNormalized{ normalizeCoord(m_zoom) };
	float m_xNormalized{ normalizeCoord(m_x) };
	float m_yNormalized{ normalizeCoord(m_y)};

	static inline const int mS_transformSize{ 9 };

	float m_transform[mS_transformSize]{
		1.0f, 0.0, 0.0f, // x
		0.0f, 1.0f, 0.0f, //y 
		0.0f, 0.0f, 1.0f //w
	};

	using transformArray = float[mS_transformSize];

protected:
public:
	Camera(const Camera& camera) = delete;
	Camera& operator=(const Camera& camera) = delete;

	Camera(float x, float y, float zoom);
	virtual ~Camera();


	const transformArray& transform() {
		return m_transform;
	}

	void translate(const float& x, const float& y) {
		m_transform[6] = x;
		m_transform[7] = y;
	}

	void setZoom(const float& value);

	const float& zoom() const {
		return m_zoom;
	}

	const float& zoomNormalized() const {
		return m_zoomNormalized;
	}

	const float& x() const {
		return m_x;
	}

	const float& y() const {
		return m_y;
	}

	const float& previousX() const {
		return m_previousX;
	}

	const float& previousY() const {
		return m_previousY;
	}

	const float& xWithZoom() const {
		return m_xWithZoom;
	}

	const float& yWithZoom() const {
		return m_yWithZoom;
	}

	void update();

	void setX(const float& value);
	void setY(const float& value);

	// for mouse collision only
	float getXWithZoom(const float& x) const ; 
	// for mouse collision only
	float getYWithZoom(const float& y) const;

	float divideByZoomX(const float& x) const {
		return x / m_transform[0];
	}
	float divideByZoomY(const float& y) const {
		return y / m_transform[4];
	}

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};		
#endif
};