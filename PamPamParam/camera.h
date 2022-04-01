#pragma once
#include "utils.h"
#include <iostream>



class Camera {
private:
	float m_x;
	float m_y;

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

	const float& x() {
		return m_x;
	}

	const float& y() {
		return m_y;
	}

	void setX(const float& value);
	void setY(const float& value);


#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};		
#endif
};