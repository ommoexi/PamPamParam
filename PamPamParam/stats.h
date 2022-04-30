#pragma once
#include "utils.h"

class Stats {
private:
	float m_movementSpeed{};
	float m_jumpSpeed{};
public:
	Stats();
	Stats(const Stats& other);
	Stats(const float& movementSpeed, const float& jumpSpeed);
	virtual ~Stats();

	const float& movementSpeed() const {
		return m_movementSpeed;
	}

	const float& jumpSpeed() const {
		return m_jumpSpeed;
	}

	void setMovementSpeed(const float& value) {
		m_movementSpeed = value;
	}

	void setJumpSpeed(const float& value) {
		m_jumpSpeed = value;
	}

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};

#endif
};