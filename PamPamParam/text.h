#pragma once
#include "utils.h"
#include <string>
#include <string_view>
#include "object.h"
#include "window.h"
#include "font.h"
#include <vector>

class Text : public Object {
private:
	std::string m_content;
	const Font* m_font;
	float m_letterSpacingHorizontal;
	float m_maxPixelWidth;
	float m_letterSpacingVertical;

	std::map<int, int> m_linesCharacterCount{ {1, 0} };

	Text(const Text& text) = default;
	Text& operator=(const Text& text);

	void resize(const float& width, const float& height);

	void setShaderCoords(const int& index, Mesh& textMesh, const Mesh& fontCharMesh, const float& xCursor,
		const float& yCursor, const int& stride);
	void setShaderTextures(const int& index, Mesh& textMesh, const Mesh& fontCharMesh, const int& stride);
	void setShaderColors(const int& index, Mesh& textMesh, const Constants::vec4& colorNormalized, 
		const int& stride);

	//returns true if new line
	bool moveCursor(float& xCursor, float& yCursor, const Character& fontCharacter,
		const float& maxCharacterHeight, const float& width, const float& height, const char& letter);

protected:

public:
	Text(const float& x, const float& y, const float& letterWidth, const float& letterHeight, 
		const Constants::vec4& color, std::string_view content,const Font& font,
		const float& letterSpacingHorizontal, const float& maxPixelWidth = std::numeric_limits<float>::max(),
		const float& letterSpacingVertical = 0);

	const std::string& content() const {
		return m_content;
	}

	const float& letterSpacingHorizontal() const {
		return m_letterSpacingHorizontal;
	}

	const float& letterSpacingVertical() const {
		return m_letterSpacingVertical;
	}

	float maxPixelWidth() const {
		return m_maxPixelWidth * Constants::widthStretch;
	}

	const Font* font() const {
		return m_font;
	}

	Text& setWidth(const float& width) override;
	Text& setHeight(const float& height) override;

	Text& setColor(const float& r, const float& g, const float& b, const float& a) override;

	float getPixelWidthFirstRow() const;
	float getPixelHeightFirstRow() const;

	Text& setContent(std::string_view value);

	Text& setLetterSpacingHorizontal(const float& value) {
		m_letterSpacingHorizontal = value;
		return *this;
	}

	Text& setLetterSpacingVertical(const float& value) {
		m_letterSpacingVertical = value;
		return *this;
	}

	Text& setMaxPixelWidth(const float& value) {
		m_maxPixelWidth = value;
		return *this;
	}



	virtual ~Text();

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};

#endif
};