#pragma once
#include "object.h"
#include "animation.h"
#include "initTextures.h"

namespace rectangle {
	using setShaderColorFunc = void(const int& index, Mesh& rectMesh, const Constants::vec4& colorNormalized,
		const int& stride);
}

class Rectangle : public Object {
private:
	float m_x2{x() + width()};
	float m_y2{y() + height()};
	float m_previousX{ x() };
	float m_previousY{ y() };
	float m_previousX2{m_x2};
	float m_previousY2{m_y2};

	const Texture* m_currentTexture{};
	std::map<std::string, Animation> m_animations{};

	static inline Mesh mS_rectangleMesh{
		//position coords		                      //isAfectedByCamera      texture coords       color
		Constants::pixelStart,  Constants::pixelStart,	0,					   0, 0, 1,             0,0,0,0,	         //left down
		Constants::pixelEnd,    Constants::pixelStart, 	0,					   0, 0, 1,             0,0,0,0,            //right down
		Constants::pixelStart,  Constants::pixelEnd, 	0,					   0, 0, 1,	            0,0,0,0,            //left up
	};

	void setShaderCoordsX(const int& index, Mesh& rectMesh, const int& stride);
	void setShaderCoordsY(const int& index, Mesh& rectMesh, const int& stride);
	void setShaderTextures(const int& index, Mesh& rectMesh, const Texture& texture, const int& stride);

	void setShaderIsAffectByCamera(const int& index, Mesh& rectMesh, const int& stride,  const bool& value);

	void resizeWidth();
	void resizeHeight();
	
	using Object::setX;
	using Object::setY;
	using Object::setWidth;
	using Object::setHeight;
	using Object::updateGraphics;
	using Object::updateGraphicsX;
	using Object::updateGraphicsY;

public:

	Rectangle(const Rectangle& rect) = delete;
	Rectangle& operator=(const Rectangle& rect) = delete;
	Rectangle(const float& x, const float& y, const float& width, const float& height, const Texture* texture,
		const bool& isAffectedByCamera, const Constants::vec4& color = Colors::white);
	virtual ~Rectangle();

	void setColorBody(rectangle::setShaderColorFunc* func);

	Rectangle& setColor(const float& r, const float& g, const float& b, const float& a);
	Rectangle& setColor(const Constants::vec4& color);
	Rectangle& setColorR(const float& value);
	Rectangle& setColorG(const float& value);
	Rectangle& setColorB(const float& value);
	Rectangle& setColorA(const float& value);

	Rectangle& setWidth(const float& width);
	Rectangle& setHeight(const float& height);
	Rectangle& setSize(const float& width, const float& height);

	Rectangle& setTexture(const Texture* texture);

	const float& x2() const {
		return m_x2;
	}
	const float& y2() const {
		return m_y2;
	}
	const float& previousX() const {
		return m_previousX;
	}
	const float& previousY() const {
		return m_previousY;
	}
	const float& previousX2() const {
		return m_previousX2;
	}
	const float& previousY2() const {
		return m_previousY2;
	}

	float setX(const float& value);
	float setY(const float& value);

	// simple collision
	bool isCollide(const Rectangle& rect) const ;
	bool isCollide(const float& x, const float& y);

	const Directions::Direction& isCollideAfterMovingHorizontally(const Rectangle& rect) const;
	const Directions::Direction& isCollideAfterMovingVertically(const Rectangle& rect) const;

	const std::map<std::string, Animation>& animations() const {
		return m_animations;
	}
	Rectangle& setAllAnimations(const std::map<std::string, Animation>& value) {
		m_animations = value;
		return *this;
	}

	Rectangle& setAnimation(const Animation& animation, const std::string& animationName) {
		m_animations[animationName] = animation;
		return *this;
	}

	const Animation& getAnimation(const std::string& animationName);

	void updateAnimation(const std::string& animationName);
	void setAnimationFramesPerTexture(const std::string& animationName, const unsigned int& framesPerTexture);
	const unsigned int& animationFramesPerTexture(const std::string& animationName);

	void updatePreviousX() {
		m_previousX = x();
		m_previousX2 = m_x2;
	}
	void updatePreviousY() {
		m_previousY = y();
		m_previousY2 = m_y2;
	}

	void updateGraphics();

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};