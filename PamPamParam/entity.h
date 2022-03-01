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

protected:
public:
	Entity(const Entity& entity) = delete;
	Entity& operator=(const Entity& entity) = delete;
	Entity(const float& x, const float& y, const float& width, const float& height, const Texture* texture,
		const float& movementSpeed, const Constants::vec4& color = Colors::white);
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


#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};