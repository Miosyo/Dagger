#include <Dagger\Mesh.hpp>

namespace Dagger
{
	Mesh::Mesh()
		:m_data(), m_generated(false), m_VBO(0),
		m_IBO(0), m_drawType(GL_TRIANGLES), m_drawCount(0)
	{
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_IBO);
	}

	Mesh::Mesh(const Data& data)
		:m_data(data), m_generated(false), m_VBO(0),
		m_IBO(0), m_drawType(data.drawType), m_drawCount(data.indices.size())
	{
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_IBO);
		generate();
	}

	void Mesh::addData(const Data& data)
	{
		m_data = data;
		m_drawType = data.drawType;
		m_drawCount = data.indices.size();
		m_generated = false;
	}

	void Mesh::generate()
	{
		if (m_generated) return;

		m_drawType = m_data.drawType;
		m_drawCount = m_data.indices.size();

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_data.vertices.size(), &m_data.vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * m_data.indices.size(), &m_data.indices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		m_generated = true;
	}

	void Mesh::draw()
	{
		if (!m_generated)
			generate();

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glEnableVertexAttribArray((GLuint)AttribLocation::POSITION);
		glEnableVertexAttribArray((GLuint)AttribLocation::COLOR);
		glEnableVertexAttribArray((GLuint)AttribLocation::TEXCOORD);

		glVertexAttribPointer((GLuint)AttribLocation::POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(GLfloat)*3));
		glVertexAttribPointer((GLuint)AttribLocation::COLOR, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (const GLvoid*)(sizeof(GLfloat)*4));
		glVertexAttribPointer((GLuint)AttribLocation::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(GLfloat)*2));

		glDrawElements(m_drawType, 6, GL_UNSIGNED_INT, (void*)0);

		glDisableVertexAttribArray((GLuint)AttribLocation::POSITION);
		glDisableVertexAttribArray((GLuint)AttribLocation::COLOR);
		glDisableVertexAttribArray((GLuint)AttribLocation::TEXCOORD);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}