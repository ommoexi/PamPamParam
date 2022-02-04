#pragma once
#include "utils.h"
#include "textureArray.h"
#include <map>
#include <string_view>
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "window.h"
#include "shader.h"

struct Character {
	float width; // not normalized by  windowWidth
	float height; // not normalized by windowHeight
	Mesh mesh;

};

// ascii font only
class Font {
private:

	unsigned int m_pixelWidth;
	unsigned int m_pixelHeight;
	TextureArray* m_atlas;
	std::map<char, Character> m_characters{}; // ascii
	float m_maxCharacterHeight{};

	void setCharacter(const Texture& texture, const char& textureName, const int& glyphTop);

protected:
public:
	//font width and height should be 64 max
	Font(std::string_view fontPath, const unsigned int& pixelWidth, const unsigned int& pixelHeight,
		const int& min_filter = GL_NEAREST, const int& mag_filter = GL_NEAREST,
		const int& wrap_s = GL_CLAMP_TO_EDGE, const int& wrap_t = GL_CLAMP_TO_EDGE);
	// deletes m_atlas
	virtual ~Font();
	Font(const Font& font) = delete;
	Font& operator=(const Font& font) = delete;

	const Character& character(const char& c) const {
		try {
			return m_characters.at(c);
		}
		catch (std::out_of_range) {
#ifdef _DEBUG
#ifdef _INFO
			debugMessage("FONT LOADS INVALID LETTER \n");
#endif
#endif
			return m_characters.at(' ');
		}
	}

	void bindAtlas() const {
		m_atlas->bind();
	}

	TextureArray* atlas() const {
		return m_atlas;
	}

	const float& maxCharacterHeight() const {
		return m_maxCharacterHeight;
	}

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};

#endif
};