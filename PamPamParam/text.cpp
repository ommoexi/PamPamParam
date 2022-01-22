#include "text.h"

void Text::setShaderCoords(const int& index, Mesh& textMesh, const Mesh& fontCharMesh, const float& xCursor, 
		const float& yCursor, const int& stride) {
		//pos coords														
		//left down
		textMesh[index] = transformX(fontCharMesh[0]) + xCursor;
		textMesh[index + 1] = transformY(fontCharMesh[1]) + yCursor;

		//right down
		textMesh[index + stride] = transformX(fontCharMesh[5]) + xCursor;
		textMesh[index + stride + 1] = transformY(fontCharMesh[6]) + yCursor;

		//left up
		textMesh[index + stride * 2] = transformX(fontCharMesh[10]) + xCursor;
		textMesh[index + stride * 2 + 1] = transformY(fontCharMesh[11]) + yCursor;
	}

void Text::setShaderTextures(const int& index, Mesh& textMesh, const Mesh& fontCharMesh, const int& stride) {
	textMesh[index + 2] = fontCharMesh[2];
	textMesh[index + 3] = fontCharMesh[3];
	textMesh[index + 4] = fontCharMesh[4];

	textMesh[index + stride + 2] = fontCharMesh[7];
	textMesh[index + stride + 3] = fontCharMesh[8];
	textMesh[index + stride + 4] = fontCharMesh[9];

	textMesh[index + stride * 2 + 2] = fontCharMesh[12];
	textMesh[index + stride * 2 + 3] = fontCharMesh[13];
	textMesh[index + stride * 2 + 4] = fontCharMesh[14];
}

void Text::setShaderColors(const int& index, Mesh& textMesh, const Constants::vec4& colorNormalized, 
	const int& stride) {
	textMesh[index + 5] = colorNormalized.x;
	textMesh[index + 6] = colorNormalized.y;
	textMesh[index + 7] = colorNormalized.z;
	textMesh[index + 8] = colorNormalized.w;

	textMesh[index + stride + 5] = colorNormalized.x;
	textMesh[index + stride + 6] = colorNormalized.y;
	textMesh[index + stride + 7] = colorNormalized.z;
	textMesh[index + stride + 8] = colorNormalized.w;

	textMesh[index + stride * 2 + 5] = colorNormalized.x;
	textMesh[index + stride * 2 + 6] = colorNormalized.y;
	textMesh[index + stride * 2 + 7] = colorNormalized.z;
	textMesh[index + stride * 2 + 8] = colorNormalized.w;
}

bool Text::moveCursor(float& xCursor, float& yCursor, const Character& fontCharacter,
	const float& maxCharacterHeight, const float& width, const float& height, const char& letter) {
	xCursor += (fontCharacter.width * width + m_letterSpacingHorizontal) / Constants::widthStretch;
	if (letter == '\n' || (xCursor * Constants::widthStretch > m_maxPixelWidth && letter == ' ')) {
		xCursor = 0;
		yCursor -= (maxCharacterHeight * height + m_letterSpacingVertical) / Constants::heightStretch;
		return true;
	}
	return false;
}

Text::~Text() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::text_cpp);
	setDebugDestructor(false);
#endif
}
Text::Text(const float& x, const float& y, const float& letterWidth, const float& letterHeight,
	const Constants::vec4& color, std::string_view content, const Font& font,
	const float& letterSpacingHorizontal, const float& maxPixelWidth, const float& letterSpacingVertical) :
	Object{ x,y,letterWidth, letterHeight, color, Shader::charAttrib() }, m_content{ content }, m_font{ &font },
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
		if(totalHeight > characterHeight){
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


Text& Text::setColor(const float& r, const float& g, const float& b, const float& a) {
	Object::setColor(r, g, b, a);

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
			setShaderColors(i, _mesh, _colorNormalized, stride);
		}
	}

	return *this;
}