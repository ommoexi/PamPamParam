#include "object.h"

Object::Object(const float& x, const float& y, const float& width, const float& height,
	const Constants::vec4& color, const Shader::Attrib& attribConfig, const bool& isAffectedByCamera, const Mesh& mesh)
	: m_x{ x }, m_y{ y }, m_width{ width }, m_height{ height },
	m_color{ color }, m_attribConfig{ attribConfig }, m_mesh{ mesh }, m_isAffectedByCamera{ isAffectedByCamera }
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
	float transformedX{ -1 + normalizeCoord(xCoord * m_width + m_x) };
	return transformedX;
}

float Object::transformY(const float& yCoord) const {
	float transformedY{ -1 + normalizeCoord(yCoord * m_height + m_y) };
	return transformedY;
}


float Object::setX(const float& x) {
	float previousX{ m_x };
	m_x = x;
	float xDistance{ (m_x - previousX) };	
	return xDistance;

}

float Object::setY(const float& y) {
	float previousY{ m_y };
	m_y = y;
	float yDistance{ (m_y - previousY) };
	return yDistance;
}


Object& Object::setWidth(const float& width) {
#ifdef _DEBUG
	if (width <= 0) {
		debugMessage("OBJECT WIDTH IS BELLOW 0. ERRORS WILL OCCUR \n");
	}
#endif
	m_width = width;

	return *this;
}

Object& Object::setHeight(const float& height) {
#ifdef _DEBUG
	if (height <= 0) {
		debugMessage("OBJECT HEIGHT IS BELLOW 0. ERRORS WILL OCCUR \n");
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

bool Object::isInBounds() const {
	return (m_x <= m_topRightBounds.x && m_x >= m_bottomLeftBounds.x && m_y <= m_topRightBounds.y && m_y >= m_bottomLeftBounds.y);
}


void Object::updateGraphicsX() {
	if (m_previousX != m_x) {
		const int& stride{ m_attribConfig.stride() };
		const int& totalIndicesPerShape{ attribConfig().totalIndicesPerShape() };
		float xDistance{ (m_x - m_previousX) };
		float xDistanceNormalized{ normalizeCoord(xDistance)  };
		const size_t& meshSize{ m_mesh.size() };
		for (int i{}; i < meshSize; i += totalIndicesPerShape) {
			m_mesh[i] += xDistanceNormalized;
			m_mesh[i + stride] += xDistanceNormalized;
			m_mesh[i + stride * 2] += xDistanceNormalized;
		}
		m_previousX = m_x;
	}
}
void Object::updateGraphicsY() {
	if (m_previousY != m_y) {
		const int& stride{ m_attribConfig.stride() };
		const int& totalIndicesPerShape{ attribConfig().totalIndicesPerShape() };
		float yDistance{ (m_y - m_previousY) };
		float yDistanceNormalized{ normalizeCoord(yDistance) };
		const size_t& meshSize{ m_mesh.size() };
		for (int i{}; i < meshSize; i += totalIndicesPerShape) {
			m_mesh[i + 1] += yDistanceNormalized;
			m_mesh[i + 1 + stride] += yDistanceNormalized;
			m_mesh[i + 1 + stride * 2] += yDistanceNormalized;
		}
		m_previousY = m_y;
	}
}

void Object::updateGraphics() {
	updateGraphicsX();
	updateGraphicsY();
}