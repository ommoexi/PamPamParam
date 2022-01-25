#pragma once
#include "object.h"

namespace rectangle {
	using setShaderColorFunc = void(const int& index, Mesh& rectMesh, const Constants::vec4& colorNormalized,
		const int& stride);
}

class Rectangle : public Object {
private:

	// de modificat 
	const Texture* m_texture{};

	static inline Mesh mS_rectangleMesh{
		//position coords		                            texture coords       color
		Constants::pixelStart,  Constants::pixelStart,		0, 0, 1,             0,0,0,0,	         //left down
		Constants::pixelEnd,    Constants::pixelStart, 		0, 0, 1,             0,0,0,0,            //right down
		Constants::pixelStart,  Constants::pixelEnd, 		0, 0, 1,	         0,0,0,0,            //left up
	};

	void setShaderCoords(const int& index, Mesh& rectMesh, const int& stride);
	void setShaderTextures(const int& index, Mesh& rectMesh, const Texture& texture, const int& stride);

	void resize();

public:


	Rectangle(const float& x, const float& y, const float& width, const float& height, const Constants::vec4& color, 
		const Texture* texture);
	virtual ~Rectangle();

	void setColorBody(rectangle::setShaderColorFunc* func);

	Rectangle& setColor(const float& r, const float& g, const float& b, const float& a);

	Rectangle& setColorR(const float& value);
	Rectangle& setColorG(const float& value);
	Rectangle& setColorB(const float& value);
	Rectangle& setColorA(const float& value);

	Rectangle& setWidth(const float& width);
	Rectangle& setHeight(const float& height);
	Rectangle& setSize(const float& width, const float& height);

	Rectangle& setTexture(const Texture* texture);

	bool isCollide(const Rectangle& rect);

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};

#endif
};