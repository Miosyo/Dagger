#include <Dagger\Model.hpp>

namespace Dagger
{
	Model::Model()
	{
		shader = nullptr;
	}

	Model::~Model()
	{

	}

	void Model::attachMesh(Mesh& mesh)
	{
		meshes.push_back(mesh);
	}

	void Model::attachShader(Shader& shader)
	{
		this->shader = &shader;
	}

	void Model::Render()
	{
		if (shader == nullptr) return;
		for (Mesh m : meshes)
		{
			m.Draw(*shader);
		}
	}
}