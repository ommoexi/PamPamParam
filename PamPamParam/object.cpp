#include "object.h"

Object::Object(const float& x, const float& y, const float& width, const float& height,
	const Constants::vec4& color, const Shader::Attrib& attribConfig,
	const Mesh& mesh)
	: m_x{ x }, m_y{ y }, m_width{ width }, m_height{ height },
	m_color{ color }, m_attribConfig{ attribConfig }, m_mesh{ mesh }
{
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::object_cpp, &mS_objectsCount);
	if (m_width == 0) {
		debugMessage("OBJECT WIDTH IS EQUAL TO 0 \n");
	}
	if (m_height == 0) {
		debugMessage("OBJECT HEIGHT IS EQUAL TO 0 \n");
	}
#endif

}

Object::~Object() {
#ifdef _DEBUG
	if (m_debugDestructor) {
		DEBUG_DESTRUCTOR_OBJ(this, Source_Files::object_cpp);
		setDebugDestructor(false);
	}
#endif
}

float Object::transformX(const float& xCoord) const {
	float transformedX{ (xCoord * m_width + m_x) / Constants::widthStretch };
	return transformedX;
}

float Object::transformY(const float& yCoord) const {
	float transformedY{ (yCoord * m_height + m_y) / Constants::heightStretch };
	return transformedY;
}


Object& Object::setX(const float& x) {
	m_previousX = m_x;
	m_x = x;
	const int& stride{ m_attribConfig.stride() };
	const int& totalIndicesPerShape{ attribConfig().totalIndicesPerShape() };
	float xDistance{ (m_x - m_previousX) / Constants::widthStretch };
	const size_t& meshSize{ m_mesh.size() };
	for (int i{}; i < meshSize; i += totalIndicesPerShape) {
		m_mesh[i] += xDistance;
		m_mesh[i + stride] += xDistance;
		m_mesh[i + stride * 2] += xDistance;
	}

	return *this;
}

Object& Object::setY(const float& y) {
	m_previousY = m_y;
	m_y = y;
	const int& stride{ m_attribConfig.stride() };
	const int& totalIndicesPerShape{ attribConfig().totalIndicesPerShape() };
	float yDistance{ (m_y - m_previousY) / Constants::widthStretch };
	const size_t& meshSize{ m_mesh.size() };
	for (int i{}; i < meshSize; i += totalIndicesPerShape) {
		m_mesh[i + 1] += yDistance;
		m_mesh[i + 1 + stride] += yDistance;
		m_mesh[i + 1 + stride * 2] += yDistance;
	}
	return *this;
}


Object& Object::setWidth(const float& width) {
#ifdef _DEBUG
	if (width == 0) {
		debugMessage("OBJECT WIDTH IS EQUAL TO 0 \n");
	}
#endif
	m_width = width;

	return *this;
}

Object& Object::setHeight(const float& height) {
#ifdef _DEBUG
	if (height == 0) {
		debugMessage("OBJECT HEIGHT IS EQUAL TO 0 \n");
	}
#endif
	m_height = height;
	return *this;
}

Object& Object::setColor(const float& r, const float& g, const float& b, const float& a) {
	m_color.x = r;
	m_color.y = g;
	m_color.z = b;
	m_color.w = a;
	m_colorNormalized.x = normalizeColor(r);
	m_colorNormalized.y = normalizeColor(g);
	m_colorNormalized.z = normalizeColor(b);
	m_colorNormalized.w = normalizeColor(a);
	return *this;
}

Object& Object::setColor(const Constants::vec4& color) {
	m_color.x = color.x;
	m_color.y = color.y;
	m_color.z = color.z;
	m_color.w = color.w;
	m_colorNormalized.x = normalizeColor(color.x);
	m_colorNormalized.y = normalizeColor(color.y);
	m_colorNormalized.z = normalizeColor(color.z);
	m_colorNormalized.w = normalizeColor(color.w);
	return *this;
}