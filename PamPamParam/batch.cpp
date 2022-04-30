#include "Batch.h"

Batch::Batch(TextureArray* texture, Shader& shader, const int& shapes) : m_texture{ texture },m_shader{ &shader } {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::batch_cpp, &mS_objectsCount);
#endif

	const Shader::Attrib& attribShader{ shader.attribShader() };

	int sizeOfFloat{ static_cast<int>(sizeof(float)) };
	
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	int stride{ attribShader.stride() * sizeOfFloat};

	glVertexAttribPointer(0, attribShader.sizePerAttrib()[0], GL_FLOAT, GL_FALSE,
		stride, (void*)0);
	glEnableVertexAttribArray(0);
	int start{ attribShader.sizePerAttrib()[0] * sizeOfFloat };
	for (unsigned int i{ 1 }; i < attribShader.sizePerAttrib_SIZE(); i++) {
		glVertexAttribPointer(i, attribShader.sizePerAttrib()[i], GL_FLOAT, GL_FALSE,
			stride, (void*)(start));
		glEnableVertexAttribArray(i);
		start += attribShader.sizePerAttrib()[i] * sizeOfFloat;
	}

	setVBOSize(shapes);
}

void Batch::setVBOSize(const int& shapes) {
	m_verticesSize = shapes * m_shader->attribShader().verticesPerMode();
	m_VBOByteSize = shapes * m_shader->attribShader().totalIndicesPerShape() * sizeof(float) ;
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_VBOByteSize, nullptr, GL_DYNAMIC_DRAW);

	glBufferData(GL_COPY_READ_BUFFER, m_VBOByteSize, nullptr, GL_DYNAMIC_DRAW);

}

void Batch::setSubData(const Mesh& mesh) {
	long long size{ static_cast<long long>(mesh.size() * sizeof(float)) };

	if (m_offset + size <= m_VBOByteSize) {
		glBufferSubData(GL_ARRAY_BUFFER, m_offset, size, mesh.data());
		m_offset += size;
		m_totalVertexPointsToBeDrawn += static_cast<int>(mesh.size() / m_shader->attribShader().stride());
	}
#ifdef _DEBUG
	else {
		debugMessage("BATCH NOT ENOUGH SPACE FOR SUBDATA\n");
	}
#endif
}

void Batch::bindBuffer() const{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
}

Batch::~Batch() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::batch_cpp);
#endif

	glDeleteBuffers(1, &m_VBO);
	glDeleteVertexArrays(1, &m_VAO);
}

void Batch::draw() const {
	m_texture->bind();
	m_shader->bind();

	glBindVertexArray(m_VAO);
	glDrawArrays(m_shader->attribShader().mode(), 0, m_totalVertexPointsToBeDrawn);
	m_offset = 0;
	m_totalVertexPointsToBeDrawn = 0;
}

