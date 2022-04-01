#pragma once
#include "utils.h"
#include "shader.h"
#include "textureArray.h"
#include "camera.h"
#include "window.h"
#include <math.h>
#include <vector>


class Object {
private:
	float m_x; // bottom left corner
	float m_y; // bottom left corner
	float m_width; // scale x
	float m_height; // scale y
	Constants::vec4 m_color;
	const Shader::Attrib& m_attribConfig;
	Mesh m_mesh{};  
	bool m_isAffectedByCamera{ false };
	Constants::vec4 m_colorNormalized{normalizeColor(m_color)};

	bool m_removeFromVector{ false };
	bool m_useDeleteWhenRemoved{ false };

	Object& setUseDeleteWhenRemoved(const bool& value) {
		m_useDeleteWhenRemoved = value;
		return *this;
	}

	bool m_deleted{ false }; // this variable is for handler only if it is on stack and it is deleted then it is true
	const bool& isDeleted() const {
		return m_deleted;
	}

	Point m_bottomLeftBounds{}; // for map only
	Point m_topRightBounds{};   // for map only

	float m_previousX{ m_x }; // for updateGraphicsX() only
	float m_previousY{ m_y }; // for updateGraphicsY() only

	void updateGraphicsX();
	void updateGraphicsY();
	void updateGraphics();

protected:

	friend class Handler;
	friend class Map;
	friend class Zone;
	friend class Hud;

	float transformX(const float& xCoord) const;
	float transformY(const float& yCoord) const;

	Mesh& mesh() {
		return m_mesh;
	}

	const Mesh& mesh() const {
		return m_mesh;
	}

	const Constants::vec4& colorNormalized() {
		return m_colorNormalized;
	}

	// implement these functions in childs
	
	Object& setColor(const float& r, const float& g, const float& b, const float& a);
	Object& setColor(const Constants::vec4& color);

	Object& setColorR(const float& value) {
		m_color.x = value;
		m_colorNormalized.x = normalizeColor(value);
		return *this;
	}

	Object& setColorG(const float& value) {
		m_color.y = value;
		m_colorNormalized.y = normalizeColor(value);
		return *this;
	}

	Object& setColorB(const float& value) {
		m_color.z = value;
		m_colorNormalized.z = normalizeColor(value);
		return *this;
	}

	Object& setColorA(const float& value) {
		m_color.w = value;
		m_colorNormalized.w = normalizeColor(value);
		return *this;
	}

	//no implementation only sets width without modifying vertices
	Object& setHeight(const float& height);
	Object& setWidth(const float& width);
	 
	//

public:

	Object(const float& x, const float& y, const float& width, const float& height, const Constants::vec4& color,
		const Shader::Attrib& attribConfig, const bool& isAffectedByCamera, const Mesh& mesh = {});
	virtual ~Object();
	Object(const Object& other) = delete;
	Object& operator=(const Object& other) = delete;

	const float& width() const {
		return m_width;
	}

	const float& height() const {
		return m_height;
	}

	const float& x() const {
		return m_x;
	}

	const float& y() const {
		return m_y;
	}

	const Constants::vec4& color() {
		return m_color;
	}

	const float& colorR() const {
		return m_color.x;
	}

	const float& colorG() const {
		return m_color.y;
	}

	const float& colorB() const {
		return m_color.z;
	}

	const float& colorA() const {
		return m_color.w;
	}

	const Shader::Attrib& attribConfig() {
		return m_attribConfig;
	}

	float setX(const float& x);

	float setY(const float& y);

	const bool& isRemoveFromVector() const {
		return m_removeFromVector;
	}

	void setRemoveFromVector(const bool& value) {
		m_removeFromVector = value;
	}

	const bool& useDeleteWhenRemoved() const {
		return m_useDeleteWhenRemoved;
	}

	const Point& bottomLeftBounds() const {
		return m_bottomLeftBounds;
	}
	const Point& topRightBounds() const {
		return m_topRightBounds;
	}

	void setBottomLeftBounds(const int& x, const int& y) {
		m_bottomLeftBounds.x = x;
		m_bottomLeftBounds.y = y;
	}

	void setTopRightBounds(const int& x, const int& y) {
		m_topRightBounds.x = x;
		m_topRightBounds.y = y;
	}

	bool isInBounds() const;

	const bool& isAffectedByCamera()const {
		return m_isAffectedByCamera;
	}

	void setIsAffectedByCamera(const bool& value) {
		m_isAffectedByCamera = value;
	}

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
	bool m_debugDestructor{ true }; // no deletion twice

protected:
	Object& setDebugDestructor(const bool& value) {
		m_debugDestructor = value;
		return *this;
	}
	const bool& debugDestructor() const {
		return m_debugDestructor;
	}
#endif
};