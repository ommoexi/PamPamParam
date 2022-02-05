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
	unsigned int m_VBC;
	int m_verticesSize{};
	long long m_VBOByteSize{};

protected:
public:
	Batch(const Batch& batch) = delete;
	Batch& operator=(const Batch& batch) = delete;

	Batch(TextureArray* texture, Shader& shader, const int& shapes);
	virtual ~Batch();

	const int& verticesSize() const {
		return m_verticesSize;
	}

	void setVBOSize(const int& shapes);

	// bind first
	void setSubData(const int& offset, const Mesh& mesh);

	void draw() const;

	// use this function before setSubData and outside iteration
	void bindBuffer() const;

	const Shader& shader() const {
		return *m_shader;
	}

	void setAllDataVoid();

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};

#endif
};