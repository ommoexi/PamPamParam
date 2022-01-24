#pragma once
#include "utils.h"
#include "shader.h"
#include "textureArray.h"


class Batch {
private:
	TextureArray* m_texture; 
	Shader* m_shader;
	unsigned int m_VAO;
	unsigned int m_VBO;
	int m_verticesSize{};

protected:
public:
	Batch(TextureArray* texture, Shader& shader);
	virtual ~Batch();

	const int& verticesSize() const {
		return m_verticesSize;
	}

	void setVBOSize(const int& shapes);

	// size is not in bytes
	void setVerticesSize(const int& size) {
		m_verticesSize = size;
	}

	// bind first
	void setSubData(const int& offset, const Mesh& mesh);

	void draw();

	// use this function before setSubData and outside iteration
	void bindBuffer() const;

	// DE MODIFICAT 
	void clearVerticesSize() {
		m_verticesSize = 0;
	}

	const Shader& shader() const {
		return *m_shader;
	}

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};

#endif
};