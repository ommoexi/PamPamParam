#pragma once
#include "utils.h"
#include <iostream>



class Camera {
private:
	float m_x;
	float m_y;
	float m_xWithZoom;
	float m_yWithZoom;
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

	Camera(float x, float y);
	virtual ~Camera();


	const transformArray& transform() {
		return m_transform;
	}

	Camera& setTransformX(const float& x, const float& y, const float& w = 0.f) {
		m_transform[0] = x;
		m_transform[1] = y;
		m_transform[2] = w;
		return *this;
	}

	Camera& setTransformY(const float& x, const float& y, const float& w = 0.f) {
		m_transform[3] = x;
		m_transform[4] = y;
		m_transform[5] = w;
		return *this;
	}

	Camera& setTransformW(const float& x, const float& y, const float& w = 1.f) {
		m_transform[6] = x;
		m_transform[7] = y;
		m_transform[8] = w;
		return *this;
	}

	void translate(const float& x, const float& y) {
		m_transform[6] = x;
		m_transform[7] = y;
	}

	const float& zoom() const {
		return m_zoom;
	}

	const float& zoomNormalized() const {
		return m_zoomNormalized;
	}

	void setZoom(const float& value);

	const float& x() const {
		return m_x;
	}

	const float& y() const {
		return m_y;
	}

	const float& xWithZoom() const {
		return m_xWithZoom;
	}

	const float& yWithZoom() const {
		return m_yWithZoom;
	}

	void setX(const float& value);
	void setY(const float& value);

	// for mouse collision only
	float getXWithZoom(const float& x, const float& y) const ; 
	// for mouse collision only
	float getYWithZoom(const float& x, const float& y) const;
	


#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};		
#endif
};