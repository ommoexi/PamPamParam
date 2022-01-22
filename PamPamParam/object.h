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
	Mesh m_mesh{};  // shared	
	TextureArray* m_texture{}; // shared

	float m_previousX{ m_x };
	float m_previousY{ m_y };



	Constants::vec4 m_colorNormalized{normalizeColor(m_color)};

	Object(const Object& other) = default;
	Object& operator=(const Object& other);

	virtual void update() {};

protected:

	float transformX(const float& xCoord) const;
	float transformY(const float& yCoord) const;

	//no implementation only sets width without modifying vertices
	virtual Object& setHeight(const float& height);
	virtual Object& setWidth(const float& width);

	const Mesh& mesh() const {
		return m_mesh;
	}

	Mesh& mesh() {
		return m_mesh;
	}

	const Constants::vec4& colorNormalized() {
		return m_colorNormalized;
	}

	friend class Handler;

public:

	Object(const float& width, const float& height, const float& x, const float& y, const Constants::vec4& color,
		const Shader::Attrib& attribConfig, const Mesh& mesh = {}, TextureArray* texture = nullptr);
	virtual ~Object();

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

	const float& previousX() const {
		return m_previousX;
	}
	const float& previousY() const {
		return m_previousY;
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


	TextureArray* texture() const {
		return m_texture;
	}

	Object& setX(const float& x);

	Object& setY(const float& y);

	virtual Object& setColor(const float& r, const float& g, const float& b, const float& a);

	Object& setTexture(TextureArray* texture) {
		m_texture = texture;
		return *this;
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