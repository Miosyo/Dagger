#include <Dagger\Mesh.hpp>

namespace Dagger
{
	void Mesh::setupMesh()
	{
		//Gen the buffers
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ibo);

		glBindVertexArray(m_vao);

		//load data into vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
		//load data into the index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
		//set the attribute pointers
		//POSITION
		glEnableVertexAttribArray(ATTRIBUTE::POSITION);
		glVertexAttribPointer(ATTRIBUTE::POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Position));
		//NORMAL
		glEnableVertexAttribArray(ATTRIBUTE::NORMAL);
		glVertexAttribPointer(ATTRIBUTE::NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
		//UV
		glEnableVertexAttribArray(ATTRIBUTE::TEXCOORD);
		glVertexAttribPointer(ATTRIBUTE::TEXCOORD, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

		//unbind VAO
		glBindVertexArray(0);
	}

	Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> uvs, std::vector<GLuint> indices)
	{
		for (int i = 0; i < vertices.size(); i++)
		{
			if (vertices[i] != glm::vec3(0, 0, 0))
			this->vertices.push_back({{ vertices[i] }, {}, {}});
		}
		for (int i = 0; i < normals.size(); i++)
		{
			this->vertices[i] = Vertex({ { },{normals[i]},{} });
		}
		for (int i = 0; i < uvs.size(); i++)
		{
			this->vertices[i] = Vertex({ {},{ },{uvs[i]} });
		}

		this->indices = indices;
		setupMesh();
	}

	void Mesh::Draw(Shader & shader)
	{
		// Draw mesh
		glBindVertexArray(m_vao);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}