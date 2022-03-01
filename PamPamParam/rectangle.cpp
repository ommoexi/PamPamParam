#include "rectangle.h"

namespace {

	void setShaderColorR(const int& index, Mesh& rectMesh, const Constants::vec4& colorNormalized,
		const int& stride) {
		rectMesh[index + 5] = colorNormalized.x;
		rectMesh[index + stride + 5] = colorNormalized.x;
		rectMesh[index + stride * 2 + 5] = colorNormalized.x;
	}
	void setShaderColorG(const int& index, Mesh& rectMesh, const Constants::vec4& colorNormalized,
		const int& stride) {
		rectMesh[index + 6] = colorNormalized.y;
		rectMesh[index + stride + 6] = colorNormalized.y;
		rectMesh[index + stride * 2 + 6] = colorNormalized.y;
	}
	void setShaderColorB(const int& index, Mesh& rectMesh, const Constants::vec4& colorNormalized,
		const int& stride) {
		rectMesh[index + 7] = colorNormalized.z;
		rectMesh[index + stride + 7] = colorNormalized.z;
		rectMesh[index + stride * 2 + 7] = colorNormalized.z;
	}
	void setShaderColorA(const int& index, Mesh& rectMesh, const Constants::vec4& colorNormalized,
		const int& stride) {
		rectMesh[index + 8] = colorNormalized.w;
		rectMesh[index + stride + 8] = colorNormalized.w;
		rectMesh[index + stride * 2 + 8] = colorNormalized.w;
	}

	void setShaderColors(const int& index, Mesh& rectMesh, const Constants::vec4& colorNormalized,
		const int& stride) {
		setShaderColorR(index, rectMesh, colorNormalized, stride);
		setShaderColorG(index, rectMesh, colorNormalized, stride);
		setShaderColorB(index, rectMesh, colorNormalized, stride);
		setShaderColorA(index, rectMesh, colorNormalized, stride);
	}

}

Rectangle::Rectangle(const float& x, const float& y, const float& width, const float& height, const Texture* texture,
	 const Constants::vec4& color) :
	Object{ x, y, width, height, color, Shader::basicAttrib(), mS_rectangleMesh }, m_currentTexture{ texture } {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::rectangle_cpp, &mS_objectsCount);
#endif

	Mesh& _mesh{ Object::mesh() };
	const int& stride{ attribConfig().stride() };
	const Constants::vec4& _colorNormalized{ colorNormalized() };


	setShaderCoords(0, _mesh, stride);
	setShaderTextures(0, _mesh, *m_currentTexture, stride);
	setShaderColors(0, _mesh, _colorNormalized, stride);
}
Rectangle::~Rectangle() {
#ifdef _DEBUG
	if (debugDestructor()) {
		DEBUG_DESTRUCTOR_OBJ(this, Source_Files::rectangle_cpp);
		setDebugDestructor(false);
	}
#endif
}

void Rectangle::setShaderCoords(const int& index, Mesh& rectMesh, const int& stride) {
	
	float& left_down_x { rectMesh[index] };
	float& left_down_y { rectMesh[index + 1] };

	float& right_down_x{ rectMesh[index + stride] };
	float& right_down_y{ rectMesh[index + stride + 1] };

	float& left_up_x{ rectMesh[index + stride * 2] };
	float& left_up_y{ rectMesh[index + stride * 2 + 1] };

	left_down_x = transformX(mS_rectangleMesh[index]);
	left_down_y = transformY(mS_rectangleMesh[index + 1]);

	right_down_x = transformX(mS_rectangleMesh[index + stride]);
	right_down_y = transformY(mS_rectangleMesh[index + stride + 1]);

	left_up_x = transformX(mS_rectangleMesh[index + stride * 2]);
	left_up_y = transformY(mS_rectangleMesh[index + stride * 2 + 1]);
}

void Rectangle::setShaderTextures(const int& index, Mesh& rectMesh, const Texture& texture, const int& stride) {
	rectMesh[index + 2] = texture.x1;
	rectMesh[index + 3] = texture.y1;
	rectMesh[index + 4] = texture.z;

	rectMesh[index + stride + 2] = texture.x2;
	rectMesh[index + stride + 3] = texture.y1;
	rectMesh[index + stride + 4] = texture.z;

	rectMesh[index + stride * 2 + 2] = texture.x1;
	rectMesh[index + stride * 2 + 3] = texture.y2;
	rectMesh[index + stride * 2 + 4] = texture.z;
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

void Rectangle::resize() {
	Mesh& _mesh{ Object::mesh() };
	const int& stride{ attribConfig().stride() };
	setShaderCoords(0, _mesh, stride);
}

Rectangle& Rectangle::setWidth(const float& width) {
	Object::setWidth(width);
	resize();
	return *this;
}
Rectangle& Rectangle::setHeight(const float& height) {
	Object::setHeight(height);
	resize();
	return *this;
}
Rectangle& Rectangle::setSize(const float& width, const float& height) {
	Object::setWidth(width);
	Object::setHeight(height);
	resize();
	return *this;
}

Rectangle& Rectangle::setTexture(const Texture* texture) {
	m_currentTexture = texture;
	Mesh& _mesh{ Object::mesh() };
	const int& stride{ attribConfig().stride() };
	setShaderTextures(0, _mesh, *m_currentTexture, stride);
	return *this;
}

bool Rectangle::isCollide(const Rectangle& rect) {
	if (x2() >= rect.x() && x() <= rect.x2() && y2() >= rect.y() && y() <= rect.y2()) {
		return true;
	}
	else {
		return false;
	}
}

Rectangle& Rectangle::setX(const float& value) {
	Object::setX(value);
	m_x2 = value + width();
	return *this;
}
Rectangle& Rectangle::setY(const float& value) {
	Object::setY(value);
	m_y2 = value + height();
	return *this;
}

void Rectangle::updateAnimation(const std::string& animationName) {
	try {
		auto& animation{ m_animations.at(animationName) };
		auto& texture{ animation.nextTexture() };
		if (m_currentTexture != &texture) {
			setTexture(&texture);
		}
	}
	catch (...) {
#ifdef _DEBUG
		debugMessage("Rectangle animation not found!\n");
#endif
	}
}

void Rectangle::setAnimationFramesPerTexture(const std::string& animationName, const unsigned int& framesPerTexture) {
	try {
		auto& animation{ m_animations.at(animationName) };
		animation.setFramesPerTexture(framesPerTexture);
	}
	catch (...) {
#ifdef _DEBUG
		debugMessage("Rectangle animation not found!\n");
#endif
	}
}

namespace {
	unsigned int nullUInt{};
	Animation nullAnimation{};
}

const unsigned int& Rectangle::animationFramesPerTexture(const std::string& animationName) {
	try {
		auto& animation{ m_animations.at(animationName) };
		return animation.framesPerTextures();
	}
	catch (...) {
#ifdef _DEBUG
		debugMessage("Rectangle animation not found!\n");
#endif
	}
	return nullUInt;
}

const Animation& Rectangle::getAnimation(const std::string& animationName) {
	try {
		auto& animation{ m_animations.at(animationName) };
		return animation;
	}
	catch (...) {
#ifdef _DEBUG
		debugMessage("Rectangle animation not found!\n");
#endif
	}
	return nullAnimation;
}