#ifndef DAGGER_MESH_HPP
#define DAGGER_MESH_HPP

#include <GL\glew.h>
#include <glm\glm.hpp>

#include <vector>

#include <Dagger\Common.hpp>
#include <Dagger\Vertex.hpp>


namespace Dagger
{
	enum class AttribLocation : GLuint
	{
		POSITION = 0,
		COLOR = 1,
		TEXCOORD = 2
	};

	class Mesh
	{
	public:
		struct Data
		{
		public:
			GLenum drawType = GL_TRIANGLES;

			std::vector<Vertex> vertices;
			std::vector<GLint> indices;
		};
	private:
		GLuint m_VBO;
		GLuint m_IBO;
		Data m_data;
		GLenum m_drawType;
		GLint m_drawCount;
		bool m_generated;
	public:
		Mesh();
		Mesh(const Data& data);

		virtual ~Mesh() { destroy(); }

		void addData(const Data& data);

		void generate();
		void draw();

		inline Data& getData() { return m_data; }

		inline void destroy() const 
		{
			glDeleteBuffers(1, &m_VBO);
			glDeleteBuffers(1, &m_IBO);
		}
	};
}

#endif