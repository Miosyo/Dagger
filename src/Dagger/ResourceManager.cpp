#include <Dagger\ResourceManager.hpp>


namespace Dagger
{
	// Instantiate static variables
	std::map<std::string, Texture2D> ResourceManager::Textures;
	std::map<std::string, Shader> ResourceManager::Shaders;
	std::map<std::string, Model> ResourceManager::Models;

	Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name)
	{
		Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
		return Shaders[name];
	}

	Shader ResourceManager::GetShader(std::string name)
	{
		return Shaders[name];
	}

	Texture2D ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name)
	{
		Textures[name] = loadTextureFromFile(file, alpha);
		return Textures[name];
	}

	Texture2D ResourceManager::GetTexture(std::string name)
	{
		return Textures[name];
	}

	Model ResourceManager::LoadModel(std::string name)
	{
		Mesh mesh = LoadMeshFromFile(name.c_str());
		Models[name] = Model();
		Models[name].attachMesh(mesh);
		return Models[name];
	}

	Model ResourceManager::GetModel(std::string name)
	{
		return Models[name];
	}

	void ResourceManager::Clear()
	{
		// (Properly) delete all shaders	
		for (auto iter : Shaders)
			glDeleteProgram(iter.second.ID);
		// (Properly) delete all textures
		for (auto iter : Textures)
			glDeleteTextures(1, &iter.second.ID);
	}

	Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
	{
		// 1. Retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;
		try
		{
			// Open files
			std::ifstream vertexShaderFile(vShaderFile);
			std::ifstream fragmentShaderFile(fShaderFile);
			std::stringstream vShaderStream, fShaderStream;
			// Read file's buffer contents into streams
			vShaderStream << vertexShaderFile.rdbuf();
			fShaderStream << fragmentShaderFile.rdbuf();
			// close file handlers
			vertexShaderFile.close();
			fragmentShaderFile.close();
			// Convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
			// If geometry shader path is present, also load a geometry shader
			if (gShaderFile != nullptr)
			{
				std::ifstream geometryShaderFile(gShaderFile);
				std::stringstream gShaderStream;
				gShaderStream << geometryShaderFile.rdbuf();
				geometryShaderFile.close();
				geometryCode = gShaderStream.str();
			}
		}
		catch (std::exception e)
		{
			std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
		}
		const GLchar *vShaderCode = vertexCode.c_str();
		const GLchar *fShaderCode = fragmentCode.c_str();
		const GLchar *gShaderCode = geometryCode.c_str();
		// 2. Now create shader object from source code
		Shader shader;
		shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
		return shader;
	}

	Texture2D ResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha)
	{
		// Create Texture object
		Texture2D texture;
		if (alpha)
		{
			texture.Internal_Format = GL_RGBA;
			texture.Image_Format = GL_RGBA;
		}
		// Load image
		int width, height;
		unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
		// Now generate texture
		texture.Generate(width, height, image);
		// And finally free image data
		SOIL_free_image_data(image);
		return texture;
	}

	Mesh ResourceManager::LoadMeshFromFile(const GLchar *file)
	{
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> uvs;
		std::vector<GLuint> indices;
		std::ifstream f(file);
		std::string line;
		std::string name;
		while (std::getline(f, line))
		{
			if (line == "" || line[0] == '#')
			{
				
			}
			else
			{
				std::istringstream lineStream(line);
				lineStream >> name;

				if (name[0] == 'v')//vertex
				{
					glm::vec3 vertex;
					sscanf(line.c_str(), "%*s %f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
					vertices.push_back(vertex);
				}
				else if (name[0] == 'vt')//uvs
				{
					glm::vec2 uv;
					sscanf(line.c_str(), "%*s %f %f\n", &uv.x, &uv.y);
					uvs.push_back(uv);
				}
				else if (name[0] == 'f')//indices
				{
					GLuint vertexIndex[3];
					GLuint normalIndex[3];
					GLuint uvIndex[3];
					sscanf(line.c_str(), "%*s %d/%d/%d  %d/%d/%d  %d/%d/%d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2],
						&normalIndex[0], &normalIndex[1], &normalIndex[2],
						&uvIndex[0], &uvIndex[1], &uvIndex[2]);

					indices.push_back(vertexIndex[0]);
					indices.push_back(vertexIndex[1]);
					indices.push_back(vertexIndex[2]);
				}
			}
		}
		f.close();
		return Mesh(vertices, normals, uvs, indices);
	}
}