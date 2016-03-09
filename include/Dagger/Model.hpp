#ifndef DAGGER_MODEL_HPP
#define DAGGER_MODEL_HPP

#include <vector>

#include <Dagger\Common.hpp>
#include <Dagger\Mesh.hpp>
#include <Dagger\Shader.hpp>

#include <glm\glm.hpp>

namespace Dagger
{
	class Model
	{
	public:
		Shader* shader;
		glm::mat4 matrix = glm::mat4(1.0f);
		std::vector<Mesh> meshes;
	public:
		Model();
		~Model();

		void attachMesh(Mesh& mesh);
		void attachShader(Shader& shader);

		void Render();
	};
}

#endif