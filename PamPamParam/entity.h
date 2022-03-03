#pragma once
#include "rectangle.h"
#include "basicBlock.h"
#include <array>

class Entity :public Rectangle {
private:
	float m_movementSpeed;
	bool m_movementUp{ false };
	bool m_movementRight{ false };
	bool m_movementDown{ false };
	bool m_movementLeft{ false };

	Rectangle* m_topCollision;		// unique deleted by destructor
	Rectangle* m_rightCollision;	// unique deleted by destructor
	Rectangle* m_bottomCollision;	// unique deleted by destructor
	Rectangle* m_leftCollision;		// unique deleted by destructor
	Rectangle* m_hitCollision;		// unique deleted by destructor

	using Rectangle::setX;
	using Rectangle::setY;

protected:
public:
	Entity(const Entity& entity) = delete;
	Entity& operator=(const Entity& entity) = delete;
	Entity(const float& x, const float& y, const float& width, const float& height, const Texture* texture,
		const float& movementSpeed, Rectangle& topCollision, Rectangle& rightCollision, Rectangle& bottomCollision,
		Rectangle& leftCollision, Rectangle& hitCollision, const Constants::vec4& color = Colors::white);
	virtual ~Entity();

	virtual void update(std::vector<std::vector<Entity*>*>& entities,std::vector<std::vector<BasicBlock*>*>& basicBlocks);

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

	const Rectangle& topCollision() const {
		return *m_topCollision;
	}
	const Rectangle& rightCollision() const {
		return *m_rightCollision;
	}
	const Rectangle& bottomCollision() const {
		return *m_bottomCollision;
	}
	const Rectangle& leftCollision() const {
		return *m_leftCollision;
	}
	const Rectangle& hitCollision() const {
		return *m_hitCollision;
	}
	// checks and reacts to collision to basicBlock
	void check(BasicBlock& basicBlock);

	float setX(const float& x);
	float setY(const float& y);

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};