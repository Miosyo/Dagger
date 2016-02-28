#ifndef DAGGER_SHADERPROGRAM_HPP
#define DAGGER_SHADERPROGRAM_HPP

#include <Dagger\Common.hpp>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <fstream>
#include <string>

namespace Dagger
{
	enum class ShaderType
	{
		VERTEX,
		FRAGMENT,
		GEOMETRY
	};

	class ShaderProgram
	{
	public:
		ShaderProgram();
		virtual ~ShaderProgram();

		bool attachShaderFromFile(ShaderType type, const std::string& filename);
		bool attachShaderFromMemory(ShaderType type, const std::string& data);

		void use() const;
		bool isInUse() const;
		void stopUsing() const;

		bool link();
		inline bool isLinked() { return m_linked; }

		void bindAttribLocation(GLuint location, const char* name);

		GLint getAttributeLocation(const GLchar* name);
		GLint getUniformLocation(const GLchar* name);

		void setUniform(const GLchar* name, float x);
		void setUniform(const GLchar* name, float x, float y);
		void setUniform(const GLchar* name, float x, float y, float z);
		void setUniform(const GLchar* name, float x, float y, float z, float w);
		void setUniform(const GLchar* name, int x);
		void setUniform(const GLchar* name, bool x);

		inline GLuint object() const { return m_object; }
		inline const std::string& errorlog() const { return m_errorlog; }
	private:
		GLuint m_object;
		bool m_linked;
		std::string m_errorlog;
	};
}

#endif