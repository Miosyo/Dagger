#include <Dagger\ShaderProgram.hpp>

namespace Dagger
{
	INTERNAL std::string stringFromFile(const std::string& filename)
	{
		std::ifstream file;
		file.open(filename.c_str(), std::ios::in | std::ios::binary);

		std::string output;
		std::string line;

		if (!file.is_open())
		{
			std::runtime_error(std::string("Failed to open file.") + filename);
		}
		else
		{
			while (file.good())
			{
				getline(file, line);
				output.append(line + "\n");
			}
		}


		file.close();
		return output;
	}

	ShaderProgram::ShaderProgram()
		:m_object(0), m_linked(false), m_errorlog()
	{
		m_object = glCreateProgram();
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_object);
	}

	bool ShaderProgram::attachShaderFromFile(ShaderType type, const std::string& filename)
	{
		std::string fileSource = stringFromFile(filename);
		return attachShaderFromMemory(type, fileSource);
	}

	bool ShaderProgram::attachShaderFromMemory(ShaderType type, const std::string& source)
	{
		const char* srcPtr = source.c_str();
		GLuint shader;
		switch (type)
		{
			case ShaderType::VERTEX:
			{
				shader = glCreateShader(GL_VERTEX_SHADER);
				break;
			}
			case ShaderType::FRAGMENT:
			{
				shader = glCreateShader(GL_FRAGMENT_SHADER);
				break;
			}
			case ShaderType::GEOMETRY:
			{
				shader = glCreateShader(GL_GEOMETRY_SHADER);
				break;
			}
			default:
			{
				return false;
				break;
			}
		}
		glShaderSource(shader, 1, &srcPtr, nullptr);
		glCompileShader(shader);
		glAttachShader(m_object, shader);
		return true;
	}

	void ShaderProgram::use() const
	{
		if (isInUse()) return;
		glUseProgram(m_object);
	}

	bool ShaderProgram::isInUse() const
	{
		GLint currentProgram = 0;
		glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

		return (currentProgram == (GLint)m_object);
	}

	void ShaderProgram::stopUsing() const
	{
		if (!isInUse()) return;
		glUseProgram(0);
	}

	bool ShaderProgram::link()
	{
		if (!m_linked)
		{
			glLinkProgram(m_object);
			m_linked = true;
		}
		return m_linked;
	}

	void ShaderProgram::bindAttribLocation(GLuint location, const char* name)
	{
		glBindAttribLocation(m_object, location, name);
	}

	GLint ShaderProgram::getAttributeLocation(const GLchar* name)
	{
		return glGetAttribLocation(m_object, name);
	}

	GLint ShaderProgram::getUniformLocation(const GLchar* name)
	{
		return glGetUniformLocation(m_object, name);
	}

	void ShaderProgram::setUniform(const GLchar* name, float x)
	{
		if (!isInUse())
			use();
		glUniform1f(getUniformLocation(name), x);
	}

	void ShaderProgram::setUniform(const GLchar* name, float x, float y)
	{
		if (!isInUse())
			use();
		glUniform2f(getUniformLocation(name), x, y);
	}

	void ShaderProgram::setUniform(const GLchar* name, float x, float y, float z)
	{
		if (!isInUse())
			use();
		glUniform3f(getUniformLocation(name), x, y, z);
	}

	void ShaderProgram::setUniform(const GLchar* name, float x, float y, float z, float w)
	{
		if (!isInUse())
			use();
		glUniform4f(getUniformLocation(name), x, y, z, w);
	}

	void ShaderProgram::setUniform(const GLchar* name, int x)
	{
		if (!isInUse())
			use();
		glUniform1i(getUniformLocation(name), x);
	}

	void ShaderProgram::setUniform(const GLchar* name, bool x)
	{
		if (!isInUse())
			use();
		glUniform1i(getUniformLocation(name), (int)x);
	}
}