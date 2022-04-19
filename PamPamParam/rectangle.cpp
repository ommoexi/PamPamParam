#include "rectangle.h"

namespace {

	void setShaderColorR(const int& index, Mesh& rectMesh, const Constants::vec4& colorNormalized,
		const int& stride) {
		rectMesh[index + 6] = colorNormalized.x;
		rectMesh[index + stride + 6] = colorNormalized.x;
		rectMesh[index + stride * 2 + 6] = colorNormalized.x;
	}
	void setShaderColorG(const int& index, Mesh& rectMesh, const Constants::vec4& colorNormalized,
		const int& stride) {
		rectMesh[index + 7] = colorNormalized.y;
		rectMesh[index + stride + 7] = colorNormalized.y;
		rectMesh[index + stride * 2 + 7] = colorNormalized.y;
	}
	void setShaderColorB(const int& index, Mesh& rectMesh, const Constants::vec4& colorNormalized,
		const int& stride) {
		rectMesh[index + 8] = colorNormalized.z;
		rectMesh[index + stride + 8] = colorNormalized.z;
		rectMesh[index + stride * 2 + 8] = colorNormalized.z;
	}
	void setShaderColorA(const int& index, Mesh& rectMesh, const Constants::vec4& colorNormalized,
		const int& stride) {
		rectMesh[index + 9] = colorNormalized.w;
		rectMesh[index + stride + 9] = colorNormalized.w;
		rectMesh[index + stride * 2 + 9] = colorNormalized.w;
	}

	void setShaderColors(const int& index, Mesh& rectMesh, const Constants::vec4& colorNormalized,
		const int& stride) {
		setShaderColorR(index, rectMesh, colorNormalized, stride);
		setShaderColorG(index, rectMesh, colorNormalized, stride);
		setShaderColorB(index, rectMesh, colorNormalized, stride);
		setShaderColorA(index, rectMesh, colorNormalized, stride);
	}

}

void Rectangle::setShaderIsAffectByCamera(const int& index, Mesh& rectMesh, const int& stride, const bool& value) {
	rectMesh[index + 2] = static_cast<float>(value);
	rectMesh[index + stride + 2] = static_cast<float>(value);
	rectMesh[index + stride * 2 + 2] = static_cast<float>(value);
}

Rectangle::Rectangle(const float& x, const float& y, const float& width, const float& height, const Texture* texture,
	const bool& isAffectedByCamera, const Constants::vec4& color) :
	Object{ x, y, width, height, color, Shader::basicAttrib(), isAffectedByCamera, mS_rectangleMesh }, m_currentTexture{ texture } {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::rectangle_cpp, &mS_objectsCount);
#endif

	Mesh& _mesh{ Object::mesh() };
	const int& stride{ attribConfig().stride() };
	const Constants::vec4& _colorNormalized{ colorNormalized() };


	setShaderCoordsX(0, _mesh, stride);
	setShaderCoordsY(0, _mesh, stride);
	setShaderTextures(0, _mesh, *m_currentTexture, stride);
	setShaderColors(0, _mesh, _colorNormalized, stride);
	setShaderIsAffectByCamera(0, _mesh, stride, isAffectedByCamera);
}
Rectangle::~Rectangle() {
#ifdef _DEBUG
	if (debugDestructor()) {
		DEBUG_DESTRUCTOR_OBJ(this, Source_Files::rectangle_cpp);
		setDebugDestructor(false);
	}
#endif
}

void Rectangle::setShaderCoordsX(const int& index, Mesh& rectMesh, const int& stride) {
	float& left_down_x{ rectMesh[index] };
	float& right_down_x{ rectMesh[index + stride] };
	float& left_up_x{ rectMesh[index + stride * 2] };

	left_down_x = transformX(mS_rectangleMesh[index]);
	right_down_x = transformX(mS_rectangleMesh[index + stride]);
	left_up_x = transformX(mS_rectangleMesh[index + stride * 2]);
}
void Rectangle::setShaderCoordsY(const int& index, Mesh& rectMesh, const int& stride) {
	float& left_down_y{ rectMesh[index + 1] };
	float& right_down_y{ rectMesh[index + stride + 1] };
	float& left_up_y{ rectMesh[index + stride * 2 + 1] };

	left_down_y = transformY(mS_rectangleMesh[index + 1]);
	right_down_y = transformY(mS_rectangleMesh[index + stride + 1]);
	left_up_y = transformY(mS_rectangleMesh[index + stride * 2 + 1]);
}

void Rectangle::setShaderTextures(const int& index, Mesh& rectMesh, const Texture& texture, const int& stride) {
	rectMesh[index + 3] = texture.x1;
	rectMesh[index + 4] = texture.y1;
	rectMesh[index + 5] = static_cast<float>(texture.z);

	rectMesh[index + stride + 3] = texture.x2;
	rectMesh[index + stride + 4] = texture.y1;
	rectMesh[index + stride + 5] = static_cast<float>(texture.z);

	rectMesh[index + stride * 2 + 3] = texture.x1;
	rectMesh[index + stride * 2 + 4] = texture.y2;
	rectMesh[index + stride * 2 + 5] = static_cast<float>(texture.z);
}


void Rectangle::setColorBody(rectangle::setShaderColorFunc* func) {
	Mesh& _mesh{ Object::mesh() };
	const int& stride{ attribConfig().stride() };
	const Constants::vec4& _colorNormalized{ colorNormalized() };

	func(0, _mesh, _colorNormalized, stride);
}

Rectangle& Rectangle::setColor(const float& r, const float& g, const float& b, const float& a) {
	Object::setColor(r, g, b, a);

	setColorBody(setShaderColors);

	return *this;
}

Rectangle& Rectangle::setColor(const Constants::vec4& color) {
	Object::setColor(color);

	setColorBody(setShaderColors);

	return *this;
}

Rectangle& Rectangle::setColorR(const float& value) {
	Object::setColorR(value);
	setColorBody(setShaderColorR);

	return *this;

}
Rectangle& Rectangle::setColorG(const float& value) {
	Object::setColorG(value);

	setColorBody(setShaderColorG);

	return *this;
}
Rectangle& Rectangle::setColorB(const float& value) {
	Object::setColorB(value);

	setColorBody(setShaderColorB);

	return *this;
}
Rectangle& Rectangle::setColorA(const float& value) {
	Object::setColorA(value);

	setColorBody(setShaderColorA);

	return *this;
}

void Rectangle::resizeWidth() {
	Mesh& _mesh{ Object::mesh() };
	const int& stride{ attribConfig().stride() };
	setShaderCoordsX(0, _mesh, stride);
}
void Rectangle::resizeHeight() {
	Mesh& _mesh{ Object::mesh() };
	const int& stride{ attribConfig().stride() };
	setShaderCoordsY(0, _mesh, stride);
}

Rectangle& Rectangle::setWidth(const float& width) {
	Object::setWidth(width);
	m_x2 = x() + width;
	return *this;
}
Rectangle& Rectangle::setHeight(const float& height) {
	Object::setHeight(height);
	m_y2 = y() + height;
	return *this;
}
Rectangle& Rectangle::setSize(const float& width, const float& height) {
	setWidth(width);
	setHeight(height);
	return *this;
}

Rectangle& Rectangle::setTexture(const Texture* texture) {
	m_currentTexture = texture;
	Mesh& _mesh{ Object::mesh() };
	const int& stride{ attribConfig().stride() };
	setShaderTextures(0, _mesh, *m_currentTexture, stride);
	return *this;
}

bool Rectangle::isCollide(const Rectangle& rect) const {
	return (x2() >= rect.x() && x() <= rect.x2() && y2() >= rect.y() && y() <= rect.y2());

}

bool Rectangle::isCollide(const float& x, const float& y) {
	return (x2() >= x && Rectangle::x() <= x && y2() >= y && Rectangle::y() <= y);
}

const Directions::Direction& Rectangle::isCollideAfterMovingHorizontally(const Rectangle& rect) const {
	if (m_previousY < rect.y2() && m_previousY2 > rect.y()) { //check horizontally if 2 objects align
		if (m_previousX2 < rect.x2() && m_x2 > rect.x()) { // self is left obj is right
			return Directions::RIGHT;
		}
		else if (m_previousX > rect.x() && x() < rect.x2()) { // self is right obj is left
			return Directions::LEFT;

		}
	}
	return Directions::NODIRECTION;
}
const Directions::Direction& Rectangle::isCollideAfterMovingVertically(const Rectangle& rect) const {
	if (m_previousX < rect.x2() && m_previousX2 > rect.x()) { // check vertically if 2 objects align
		if (m_previousY2 < rect.y2() && m_y2 > rect.y()) { // self is down object is up		
			return Directions::UP;
		}
		else if (m_previousY > rect.y() && y() < rect.y2()) {  //self is up object is down
			return Directions::DOWN;
		}
	}
	return Directions::NODIRECTION;
}

float Rectangle::setX(const float& value) {
	float xDistance{ Object::setX(value) };
	m_x2 = value + width();
	return xDistance;
}
float Rectangle::setY(const float& value) {
	float yDistance{ Object::setY(value) };
	m_y2 = value + height();
	return yDistance;
}

void Rectangle::updateAnimation(const Animation& animation) {
	auto& texture{ animation.nextTexture() };
	if (m_currentTexture != &texture) {
		setTexture(&texture);
	}
}

void Rectangle::updateGraphics() {
	Object::updateGraphics();
	if (width() != previousWidth()) {
		resizeWidth();
		setPreviousWidth(width());
	}
	if (height() != previousHeight()) {
		resizeHeight();
		setPreviousHeight(height());
	}
	else {
		Object::updateGraphics();
	}


}
