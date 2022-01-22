#pragma once
#include "utils.h"
#include <iostream>

class Camera {
private:
	float m_x;
	float m_y;
	float m_z;

	float m_transform[9]{
		1.0f, 0.0, 0.0f, // x
		0.0f, 1.0f, 0.0f, //y 
		0.0f, 0.0f, 1.0f //w
	};

	Camera(const Camera& camera);
	Camera& operator=(const Camera& camera);

protected:
public:
	Camera(float x, float y, float z);
	virtual ~Camera();


	const float* transform() {
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



#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};		
#endif
};