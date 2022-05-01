#pragma once
#include "utils.h"

class Stats {
private:
	float m_movementSpeed{};
	float m_jumpSpeed{};
	float m_attackSpeed{};
public:
	Stats();
	Stats(const Stats& other);
	Stats(const float& movementSpeed, const float& jumpSpeed, const float& attackSpeed);
	virtual ~Stats();

	const float& movementSpeed() const {
		return m_movementSpeed;
	}

	const float& jumpSpeed() const {
		return m_jumpSpeed;
	}

	const float& attackSpeed() const {
		return m_attackSpeed;
	}

	void setMovementSpeed(const float& value) {
		m_movementSpeed = value;
	}

	void setJumpSpeed(const float& value) {
		m_jumpSpeed = value;
	}

	void setAttackSpeed(const float& value) {
		m_attackSpeed = value;
	}

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};

#endif
};