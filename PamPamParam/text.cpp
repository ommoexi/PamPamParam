#include "text.h"

void Text::setShaderIsAffectByCamera(const int& index, Mesh& textMesh, const int& stride, const bool& value) {
	textMesh[index + 2] = static_cast<int>(value);
	textMesh[index + stride + 2] = static_cast<int>(value);
	textMesh[index + stride * 2 + 2] = static_cast<int>(value);
}

void Text::setShaderCoords(const int& index, Mesh& textMesh, const Mesh& fontCharMesh, const float& xCursor, 
		const float& yCursor, const int& stride) {
		//pos coords														
		//left down
		textMesh[index] = transformX(fontCharMesh[0]) + xCursor;
		textMesh[index + 1] = transformY(fontCharMesh[1]) + yCursor;

		//right down
		textMesh[index + stride] = transformX(fontCharMesh[6]) + xCursor;
		textMesh[index + stride + 1] = transformY(fontCharMesh[7]) + yCursor;

		//left up
		textMesh[index + stride * 2] = transformX(fontCharMesh[12]) + xCursor;
		textMesh[index + stride * 2 + 1] = transformY(fontCharMesh[13]) + yCursor;
	}

void Text::setShaderTextures(const int& index, Mesh& textMesh, const Mesh& fontCharMesh, const int& stride) {
	textMesh[index + 3] = fontCharMesh[3];
	textMesh[index + 4] = fontCharMesh[4];
	textMesh[index + 5] = fontCharMesh[5];

	textMesh[index + stride + 3] = fontCharMesh[9];
	textMesh[index + stride + 4] = fontCharMesh[10];
	textMesh[index + stride + 5] = fontCharMesh[11];

	textMesh[index + stride * 2 + 3] = fontCharMesh[15];
	textMesh[index + stride * 2 + 4] = fontCharMesh[16];
	textMesh[index + stride * 2 + 5] = fontCharMesh[17];
}

namespace {

	void setShaderColorR(const int& index, Mesh& textMesh, const Constants::vec4& colorNormalized,
		const int& stride) {
		textMesh[index + 6] = colorNormalized.x;
		textMesh[index + stride + 6] = colorNormalized.x;
		textMesh[index + stride * 2 + 6] = colorNormalized.x;
	}
	void setShaderColorG(const int& index, Mesh& textMesh, const Constants::vec4& colorNormalized,
		const int& stride) {
		textMesh[index + 7] = colorNormalized.y;
		textMesh[index + stride + 7] = colorNormalized.y;
		textMesh[index + stride * 2 + 7] = colorNormalized.y;
	}
	void setShaderColorB(const int& index, Mesh& textMesh, const Constants::vec4& colorNormalized,
		const int& stride) {
		textMesh[index + 8] = colorNormalized.z;
		textMesh[index + stride + 8] = colorNormalized.z;
		textMesh[index + stride * 2 + 8] = colorNormalized.z;
	}
	void setShaderColorA(const int& index, Mesh& textMesh, const Constants::vec4& colorNormalized,
		const int& stride) {
		textMesh[index + 9] = colorNormalized.w;
		textMesh[index + stride + 9] = colorNormalized.w;
		textMesh[index + stride * 2 + 9] = colorNormalized.w;
	}

	void setShaderColors(const int& index, Mesh& textMesh, const Constants::vec4& colorNormalized,
		const int& stride) {
		setShaderColorR(index, textMesh, colorNormalized, stride);
		setShaderColorG(index, textMesh, colorNormalized, stride);
		setShaderColorB(index, textMesh, colorNormalized, stride);
		setShaderColorA(index, textMesh, colorNormalized, stride);
	}
}

bool Text::moveCursor(float& xCursor, float& yCursor, const Character& fontCharacter,
	const float& maxCharacterHeight, const float& width, const float& height, const char& letter) {
	xCursor += normalizeX(fontCharacter.width * width + m_letterSpacingHorizontal);
	if (letter == '\n' || (xCursor * Constants::widthStretch > m_maxPixelWidth && letter == ' ')) {
		xCursor = 0;
		yCursor -= normalizeY(maxCharacterHeight * height + m_letterSpacingVertical);
		return true;
	}
	return false;
}

Text::~Text() {
#ifdef _DEBUG
	if (debugDestructor()) {
		DEBUG_DESTRUCTOR_OBJ(this, Source_Files::text_cpp);
		setDebugDestructor(false);
	}
#endif
}
Text::Text(const float& x, const float& y, const float& letterWidth, const float& letterHeight,
	const Constants::vec4& color, std::string_view content, const Font& font,const float& letterSpacingHorizontal, 
	const bool& isAffectedByCamera,const float& maxPixelWidth, const float& letterSpacingVertical) :
	Object{ x,y,letterWidth, letterHeight, color, Shader::charAttrib(), isAffectedByCamera }, m_content{ content }, m_font{ &font },
	m_letterSpacingHorizontal{ letterSpacingHorizontal }, m_maxPixelWidth{ maxPixelWidth },
	m_letterSpacingVertical{ letterSpacingVertical }
{

#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::text_cpp, &mS_objectsCount);
#endif
	setContent(m_content);
}

float Text::getPixelWidthFirstRow() const
{
	float totalWidth{};
	for (auto& c : m_content) {
		auto& character{ m_font->character(c) };
		totalWidth += (character.width * width() + m_letterSpacingHorizontal);
	}
	return totalWidth; 
}

float Text::getPixelHeightFirstRow() const {
	float totalHeight{};
	for (auto& c : m_content) {
		auto& character{ m_font->character(c) };
		float characterHeight{ character.height * height() };
		if(totalHeight < characterHeight){
			totalHeight = characterHeight;
		}
	}
	return totalHeight;
}

Text& Text::setContent(std::string_view value) {
	m_content = value;
	Mesh& _mesh{ mesh() };
	_mesh.clear();
	const int& totalIndicesPerShape{ attribConfig().totalIndicesPerShape() };
	const int verticeContentSize{ static_cast<int>(m_content.size()) * totalIndicesPerShape };
	_mesh.resize(verticeContentSize);
	float xCursor{ 0 };
	float yCursor{ 0 };

	const float& maxCharacterHeight{ m_font->maxCharacterHeight() };
	const float& _width{ width() };
	const float& _height{ height() };
	const Constants::vec4& _colorNormalized{ colorNormalized() };

	const int& stride{ attribConfig().stride() };

	int currentLine{ 1 };

	for (int i{}, c{}; i < verticeContentSize; i += totalIndicesPerShape, c++) {
		const char& letter{ m_content[c] };
		Character fontCharacter{ m_font->character(letter) };

		const Mesh& fontCharMesh{ fontCharacter.mesh };
		m_linesCharacterCount[currentLine] += 1;

		if (fontCharMesh.size() > 0 && letter != '\n') {
			setShaderCoords(i, _mesh, fontCharMesh, xCursor, yCursor, stride);
			setShaderTextures(i, _mesh, fontCharMesh, stride);
		    setShaderColors(i, _mesh, _colorNormalized, stride);
			setShaderIsAffectByCamera(i, _mesh, stride, isAffectedByCamera());
		}
		if (moveCursor(xCursor, yCursor, fontCharacter, maxCharacterHeight, _width, _height, letter)) {
			m_linesCharacterCount[++currentLine] = 0;
		}
	}

	return *this;
}

void Text::resize(const float& width, const float& height) {
	Mesh& _mesh{ mesh() };
	const int& totalIndicesPerShape{ attribConfig().totalIndicesPerShape() };
	const int verticeContentSize{ static_cast<int>(m_content.size()) * totalIndicesPerShape };
	float xCursor{ 0 };
	float yCursor{ 0 };

	const float& maxCharacterHeight{ m_font->maxCharacterHeight() };

	const int& stride{ attribConfig().stride() };

	for (int i{}, c{}; i < verticeContentSize; i += totalIndicesPerShape, c++) {
		const char& letter{ m_content[c] };
		Character fontCharacter{ m_font->character(letter) };

		const Mesh& fontCharMesh{ fontCharacter.mesh };

		if (fontCharMesh.size() > 0 && letter != '\n') {
			setShaderCoords(i, _mesh, fontCharMesh, xCursor, yCursor, stride);
		}
		moveCursor(xCursor, yCursor, fontCharacter, maxCharacterHeight, width, height, letter);
	}
}

Text& Text::setWidth(const float& width) {
	Object::setWidth(width);
	resize(width, height());
	return *this;
}

Text& Text::setHeight(const float& height) {
	Object::setHeight(height);
	resize(width(), height);
	return *this;
}

Text& Text::setSize(const float& width, const float& height) {
	Object::setWidth(width);
	Object::setHeight(height);
	resize(width, height);
	return *this;
}

Text& Text::setMaxPixelWidth(const float& value) {
	m_maxPixelWidth = value;
	resize(width(), height());
	return *this;
}

void Text::setColorBody(text::setShaderColorFunc* func) {
	Mesh& _mesh{ mesh() };
	const int& totalIndicesPerShape{ attribConfig().totalIndicesPerShape() };
	const int verticeContentSize{ static_cast<int>(m_content.size()) * totalIndicesPerShape };

	const Constants::vec4& _colorNormalized{ colorNormalized() };

	const int& stride{ attribConfig().stride() };

	for (int i{}, c{}; i < verticeContentSize; i += totalIndicesPerShape, c++) {
		const char& letter{ m_content[c] };
		Character fontCharacter{ m_font->character(letter) };
		const Mesh& fontCharMesh{ fontCharacter.mesh };

		if (fontCharMesh.size() > 0 && letter != '\n') {
			func(i, _mesh, _colorNormalized, stride);
		}
	}
}

Text& Text::setColor(const Constants::vec4& color) {
	Object::setColor(color);

	setColorBody(setShaderColors);

	return *this;
}

Text& Text::setColor(const float& r, const float& g, const float& b, const float& a) {
	Object::setColor(r, g, b, a);

	setColorBody(setShaderColors);

	return *this;
}

Text& Text::setColorR(const float& value) {
	Object::setColorR(value);
	setColorBody(setShaderColorR);

	return *this;

}
Text& Text::setColorG(const float& value) {
	Object::setColorG(value);

	setColorBody(setShaderColorG);

	return *this;
	}
Text& Text::setColorB(const float& value){
	Object::setColorB(value);

	setColorBody(setShaderColorB);

	return *this;
	}
Text& Text::setColorA(const float& value){
	Object::setColorA(value);

	setColorBody(setShaderColorA);

	return *this;
	}
