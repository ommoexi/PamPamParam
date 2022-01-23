#pragma once
#include "utils.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string_view>
#include <glad/glad.h>



class Shader
{
public:
	class Attrib {
	private:
		const int* m_sizePerAttrib;
		unsigned int m_sizePerAttrib_SIZE;
		unsigned int m_mode;
		int m_verticesPerMode;
		int m_stride{};
		int m_totalIndicesPerShape{};
	public:
		Attrib(const int* size, const unsigned int& attribSize, const unsigned int& mode, 
			const int& verticesPerMode) : 
			m_sizePerAttrib{ size }, m_sizePerAttrib_SIZE{ attribSize }, m_mode{ mode },
			m_verticesPerMode{ verticesPerMode }{
			for (unsigned int i{}; i < m_sizePerAttrib_SIZE; i++) {
				m_stride += m_sizePerAttrib[i];
			}
			m_totalIndicesPerShape = m_stride * m_verticesPerMode;
		}
		const int* sizePerAttrib() const {
			return m_sizePerAttrib;
		}
		const unsigned int& sizePerAttrib_SIZE() const {
			return m_sizePerAttrib_SIZE;
		}

		const unsigned int& mode() const {
			return m_mode;
		}

		const int& verticesPerMode() const {
			return m_verticesPerMode;
		}

		const int& stride() const {
			return m_stride;
		}

		const int& totalIndicesPerShape() const {
			return m_totalIndicesPerShape;
		}
	};
private:
	unsigned int m_id;
	unsigned int m_vertexId;
	unsigned int m_geometryId{};
	unsigned int m_fragmentId;
	const Attrib& m_attribShader;

	Shader(const Shader& shader);
	Shader& operator=(const Shader& shader);



	static inline const unsigned int mS_charSizePerAttribute_SIZE{ 3 };
	//2- pos; 3 - texture; 4 - color
	static inline const int mS_charSizePerAttribute[mS_charSizePerAttribute_SIZE]{ 2,3, 4 };
	static inline const Attrib mS_charAttrib{ mS_charSizePerAttribute, mS_charSizePerAttribute_SIZE, GL_TRIANGLES, 3 };

	static inline const unsigned int mS_basicSizePerAttribute_SIZE{ 3 };
	//2- pos; 3 - texture; 4 - color 
	static inline const int mS_basicSizePerAttribute[mS_basicSizePerAttribute_SIZE]{ 2,3,4 };

	static inline const Attrib mS_basicAttrib{ mS_basicSizePerAttribute, mS_basicSizePerAttribute_SIZE, GL_TRIANGLES, 3 };


protected:
public:
	Shader(const std::string& vertexFileName, const std::string& geometryFileName,
		const std::string& fragmentFileName, const Attrib& attribShader);
	virtual ~Shader();
	void bind() const;

	const unsigned int& id() const {
		return m_id;
	}

	float getFloat(std::string_view uniformName);

	void setFloat(std::string_view uniformName, const float& value) { //must bind to use
		int uniformLocation = glGetUniformLocation(m_id, uniformName.data());
		glUniform1f(uniformLocation, value);
	}

	void setUniformIndex(std::string_view uniformName, const int& index) {
		int uniformLocation = glGetUniformLocation(m_id, uniformName.data());
		glUniform1i(uniformLocation, index); // set it manually
	}

	void setMat3(std::string_view uniformName, const float* value) {
		int uniformLocation = glGetUniformLocation(m_id, uniformName.data());
		glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, value);
	}


	void setVector2(std::string_view uniformName, const float& x, const float& y) {
		int uniformLocation = glGetUniformLocation(m_id, uniformName.data());
		glUniform2f(uniformLocation, x, y);
	}
	void setVector4(std::string_view uniformName, const float& x, const float& y, const float& z, const float& w) {
		int uniformLocation = glGetUniformLocation(m_id, uniformName.data());
		glUniform4f(uniformLocation, x, y, z, w);
	}

	static const Attrib& charAttrib() {
		return mS_charAttrib;
	}

	static const Attrib& basicAttrib() {
		return mS_basicAttrib;
	}

	const Attrib& attribShader() const {
		return m_attribShader;
	}


#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};

#endif

};
