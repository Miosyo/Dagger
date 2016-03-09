#ifndef DAGGER_MESH_HPP
#define DAGGER_MESH_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Dagger\Common.hpp>
#include <Dagger\Vertex.hpp>
#include <Dagger\Texture2D.hpp>
#include <Dagger\Shader.hpp>

namespace Dagger
{
	enum ATTRIBUTE : GLuint
	{
		POSITION = 0U,
		NORMAL = 1U,
		TEXCOORD = 2U
	};

	class Mesh
	{
	private:
		GLuint m_vao, m_vbo, m_ibo;
	private:
		void setupMesh();
	public:
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;

		Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> uvs, std::vector<GLuint> indices);
		void Draw(Shader& shader);
	};
}

#endif