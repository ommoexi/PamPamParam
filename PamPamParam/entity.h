#pragma once
#include "rectangle.h"
#include "collisionBox.h"
#include "basicBlock.h"
#include <array>

class Entity :public Rectangle {
private:
	float m_movementSpeed;
	bool m_movementUp{ false };
	bool m_movementRight{ false };
	bool m_movementDown{ false };
	bool m_movementLeft{ false };
	CollisionBox* m_hitCollision;		// unique deleted by destructor
	bool m_isFalling{ true };
	bool m_isJumping{ false };
	float m_jumpSeconds{ 1.20f };
	float m_currentJumpSeconds{ 0 };
	float m_gravity{ 7.5 };
	float m_jumpAcceleration{};

	using Rectangle::setX;
	using Rectangle::setY;
	using Rectangle::setWidth;
	using Rectangle::setHeight;

protected:
public:
	Entity(const Entity& entity) = delete;
	Entity& operator=(const Entity& entity) = delete;
	Entity(const float& x, const float& y, const float& width, const float& height, const Texture* texture,
		const float& movementSpeed, CollisionBox& hitCollision, const Constants::vec4& color = Colors::white);
	virtual ~Entity();

	virtual void update(std::vector<std::vector<Entity*>*>& entities,std::vector<std::vector<BasicBlock*>*>& basicBlocks);
	void moveHorizontally();
	void moveVertically();

	const bool& movementUp() const {
		return m_movementUp;
	}
	const bool& movementRight() const {
		return m_movementRight;
	}
	const bool& movementDown() const {
		return m_movementDown;
	}
	const bool& movementLeft() const {
		return m_movementLeft;
	}

	void setMovementUp(const bool& value) {
		m_movementUp = value;
	}
	void setMovementRight(const bool& value) {
		m_movementRight = value;
	}
	void setMovementDown(const bool& value) {
		m_movementDown = value;
	}
	void setMovementLeft(const bool& value) {
		m_movementLeft = value;
	}

	CollisionBox& hitCollision() const {
		return *m_hitCollision;
	}
	// checks and reacts to collision to basicBlock
	void checkHorizontally(BasicBlock& basicBlock);
	void checkVertically(BasicBlock& basicBlock);

	float setX(const float& x);
	float setY(const float& y);
	void setWidth(const float& width);
	void setHeight(const float& height);

	const bool& isJumping() const {
		return m_isJumping;
	}

	const bool& isFalling() const {
		return m_isFalling;
	}

	void setJump(const bool& value) {
		m_isJumping = value;
	}

	void setJumpIfNotfalling() {
		if (!m_isFalling && m_movementUp) {
			m_isJumping = true;
		}
	}

	void setJumpFalse() {
		m_isJumping = false;
		m_isFalling = true;
		m_currentJumpSeconds = 0;
	}

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};