#pragma once
#include "rectangle.h"
#include "collisionBox.h"
#include <array>
#include "basicBlock.h"
#include "stats.h"

class Entity :public Rectangle {
private:
	Stats m_stats;
	bool m_movementUp{ false };
	bool m_movementRight{ false };
	bool m_movementDown{ false };
	bool m_movementLeft{ false };
	bool m_facingRight{true};
	CollisionBox* m_hitCollision;		// unique deleted by destructor
	bool m_isFalling{ true };
	bool m_isJumping{ false };
	float m_jumpSeconds{ 1.5f };
	float m_currentJumpSeconds{ m_jumpSeconds };
	float m_gravity{ 10};

	Animation m_moveLeftAnimation;
	Animation m_moveRightAnimation;
	Animation m_idleLeftAnimation;
	Animation m_idleRightAnimation;
	const Texture* m_jumpTextureRight;
	const Texture* m_fallTextureRight;
	const Texture* m_jumpTextureLeft;
	const Texture* m_fallTextureLeft;
	
	using Rectangle::setX;
	using Rectangle::setY;
	using Rectangle::setWidth;
	using Rectangle::setHeight;


protected:
public:
	Entity(const Entity& entity) = delete;
	Entity& operator=(const Entity& entity) = delete;
	Entity(const float& x, const float& y, const float& width, const float& height, const Stats& stats,
		CollisionBox& hitCollision, const Animation& moveLeftAnim, const Animation& moveRightAnim, const Animation& idleLeftAnim,
		const Animation& idleRightAnim, const Texture& jumpTextureRight, const Texture& fallTextureRight,
		const Texture& jumpTextureLeft, const Texture& fallTextureLeft);
	virtual ~Entity();

	virtual void update(std::vector<std::vector<Entity*>*>& entities, std::vector<std::vector<BasicBlock*>*>& basicBlocks);
	void moveHorizontally();
	void moveVertically();

	const Stats& stats() const {
		return m_stats;
	}

	Stats& stats() {
		return m_stats;
	}

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

	const bool& isFacingRight() const {
		return m_facingRight;
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

	void setFacingRight(const bool& value) {
		m_facingRight = value;
	}

	CollisionBox& hitCollision() const {
		return *m_hitCollision;
	}
	// checks and reacts to collision to basicBlock
	void checkHorizontally(BasicBlock& basicBlock);
	void checkVertically(BasicBlock& basicBlock);
	void check(BasicBlock& basicBlock);

	float setX(const float& x);
	float setY(const float& y);
	//void setHitCollisionX(const float& x);
	//void setHitCollisionY(const float& y);
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

	void setIsFalling(const bool& value) {
		m_isFalling = value;
	}

	void setJumpFalse() {
		m_isJumping = false;
		m_isFalling = true;
		m_currentJumpSeconds = m_jumpSeconds;
	}

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};