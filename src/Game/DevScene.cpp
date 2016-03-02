#include <Game\DevScene.hpp>

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include <Dagger\Vertex.hpp>
#include <Dagger\Mesh.hpp>

using namespace Dagger;

GLOBAL Mesh* g_spriteMesh;

namespace Game
{
	Shader shader;
	GLuint VertexArrayID;
	void DevScene::Init()
	{
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		renderer = new Renderer();
		shader = ResourceManager::LoadShader("data/shaders/default.vert", "data/shaders/default.frag", nullptr, "default").Use();
		ResourceManager::LoadTexture("data/textures/face.png", true, "uv").Bind();

		Vertex vertices[]{
			{ -0.5f, +0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f , 0.0f, 0.0f },
			{ -0.5f, -0.5f, 0.0f , 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f },
			{ +0.5f, -0.5f, 0.0f , 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
			{ +0.5f, +0.5f, 0.0f , 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f },
		};

		GLuint indices[] = {
			0, 1, 3, 3, 1, 2
		};

		Mesh::Data meshData;
		meshData.vertices.push_back({ -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f , 0.0f, 0.0f });
		meshData.vertices.push_back({ +0.5f, -0.5f, 0.0f , 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f });
		meshData.vertices.push_back({ +0.5f, +0.5f, 0.0f , 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f });
		meshData.vertices.push_back({ -0.5f, +0.5f, 0.0f , 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f });

		meshData.indices.push_back(0);
		meshData.indices.push_back(3);
		meshData.indices.push_back(2);
		meshData.indices.push_back(2);
		meshData.indices.push_back(1);
		meshData.indices.push_back(0);

		g_spriteMesh = new Mesh(meshData);
		g_spriteMesh->addData(meshData);

		std::cout << "init dev scene" << std::endl;
	}

	void DevScene::Destroy()
	{
		std::cout << "destroy dev scene" << std::endl;
	}

	void DevScene::OnUpdate(float dt)
	{

	}

	void DevScene::OnRender()
	{
		renderer->Prepare();
		g_spriteMesh->draw();
	}
}