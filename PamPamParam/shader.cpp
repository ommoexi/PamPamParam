#include "shader.h"

namespace {
	void CheckShaderError(unsigned int shader, unsigned int flag, bool isProgram, std::string errorMessage);
	std::string loadShader(std::string fileName);
	unsigned int createShader(std::string_view text, unsigned int shaderType);
}

Shader::Shader(const std::string& vertexFileName, const std::string& geometryFileName,
	const std::string& fragmentFileName, const Attrib& attribShader) : m_attribShader{ attribShader } {

#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::shader_cpp, &mS_objectsCount);
#endif

	m_id = glCreateProgram();
	m_vertexId = createShader(loadShader(vertexFileName), GL_VERTEX_SHADER);
	m_fragmentId = createShader(loadShader(fragmentFileName), GL_FRAGMENT_SHADER);

	glAttachShader(m_id, m_vertexId);
	if (!geometryFileName.empty()) {
		m_geometryId = createShader(loadShader(geometryFileName), GL_GEOMETRY_SHADER);
		glAttachShader(m_id, m_geometryId);
	}
	glAttachShader(m_id, m_fragmentId);

	glLinkProgram(m_id);
	CheckShaderError(m_id, GL_LINK_STATUS, true, "Error: Program linking failed: ");

	glValidateProgram(m_id);
	CheckShaderError(m_id, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");
}

Shader::~Shader() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::shader_cpp);
#endif

	glDetachShader(m_id, m_vertexId);
	if (m_geometryId) {
		glDetachShader(m_id, m_geometryId);
	}
	glDetachShader(m_id, m_fragmentId);


	glDeleteShader(m_vertexId);
	if (m_geometryId) {
		glDeleteShader(m_geometryId);
	}
	glDeleteShader(m_fragmentId);

	glDeleteProgram(m_id);
}

void Shader::bind() const {
	glUseProgram(m_id);
}

namespace {
	void CheckShaderError(unsigned int shader, unsigned int flag, bool isProgram, std::string errorMessage) {
		int success{ 0 };
		char error[1024]{};

		if (isProgram) {
			glGetProgramiv(shader, flag, &success);
		}
		else {
			glGetShaderiv(shader, flag, &success);
		}
		if (success == GL_FALSE) {
			if (isProgram) {
				glGetProgramInfoLog(shader, sizeof(error), NULL, error);
			}
			else {
				glGetShaderInfoLog(shader, sizeof(error), NULL, error);
			}
#ifdef _DEBUG
			debugMessage(errorMessage + ": '" + error + "'\n");
#endif
		}
	}

	std::string loadShader(std::string fileName) {
		std::ifstream file;
		file.open(fileName.data());

		std::string output;
		std::string line;


		if (file.is_open()) {
			while (file.good()) {
				getline(file, line);
				output.append(line + "\n");
			}
		}
		else {
#ifdef _DEBUG
			debugMessage("Unable to load shader: "  + fileName + '\n');
#endif
		}
		return output;
	}

	unsigned int createShader(std::string_view text, unsigned int shaderType) {
		unsigned int shader{ glCreateShader(shaderType) };

		if (shader == 0) {
#ifdef _DEBUG
			debugMessage("Error: Shader creation failed \n");
#endif
		}

		const char* shaderSourceStrings[1];
		int shaderSourceStringsLength[1];

		shaderSourceStrings[0] = text.data();
		shaderSourceStringsLength[0] = static_cast<int>(text.length());

		glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringsLength);
		glCompileShader(shader);

		CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

		return shader;
	}
}

float Shader::getFloat(std::string_view uniformName) {
	int uniformLocation = glGetUniformLocation(m_id, uniformName.data());
	float params;
	glGetUniformfv(m_id, uniformLocation, &params);
	return params;
}
