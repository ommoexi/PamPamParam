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
	float m_previousX2{m_x2};
	float m_previousY2{m_y2};

	const Texture* m_currentTexture{};
	std::map<std::string, Animation> m_animations{};

	static inline Mesh mS_rectangleMesh{
		//position coords		                            texture coords       color
		Constants::pixelStart,  Constants::pixelStart,		0, 0, 1,             0,0,0,0,	         //left down
		Constants::pixelEnd,    Constants::pixelStart, 		0, 0, 1,             0,0,0,0,            //right down
		Constants::pixelStart,  Constants::pixelEnd, 		0, 0, 1,	         0,0,0,0,            //left up
	};

	void setShaderCoords(const int& index, Mesh& rectMesh, const int& stride);
	void setShaderTextures(const int& index, Mesh& rectMesh, const Texture& texture, const int& stride);

	void resize();
	
	using Object::setX;
	using Object::setY;

public:

	Rectangle(const Rectangle& rect) = delete;
	Rectangle& operator=(const Rectangle& rect) = delete;
	Rectangle(const float& x, const float& y, const float& width, const float& height, const Texture* texture,
		const std::map<std::string, Animation>* animations = nullptr,const Constants::vec4& color = Colors::white);
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
	const float& previousX2() const {
		return m_previousX2;
	}
	const float& previousY2() const {
		return m_previousY2;
	}

	Rectangle& setX(const float& value);
	Rectangle& setY(const float& value);

	// simple collision
	bool isCollide(const Rectangle& rect);

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};

#endif
};