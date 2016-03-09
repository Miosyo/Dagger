#include <Game\DevScene.hpp>

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include <Dagger\Vertex.hpp>
#include <Dagger\Model.hpp>

using namespace Dagger;

namespace Game
{
	glm::mat4 model;
	Shader shader;

	Model m;

	float angle = 0;
	void DevScene::Init()
	{
		renderer = new Renderer();
		shader = ResourceManager::LoadShader("data/shaders/default.vert", "data/shaders/default.frag", nullptr, "default").Use();
		ResourceManager::LoadTexture("data/textures/uv.png", true, "uv").Bind();

		m = ResourceManager::LoadModel("data/models/dagger.obj");
		m.attachShader(shader);

		/*for (int i = 0; i < m.meshes[0].vertices.size(); i++)
		{
			std::cout << m.meshes[0].vertices[i].Position.x << ", " << m.meshes[0].vertices[i].Position.y << ", " << m.meshes[0].vertices[i].Position.z << std::endl;
		}*/

		glm::mat4 View;
		glm::mat4 Projection;
		glm::mat4 mvp;

		// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		Projection = glm::perspective(glm::radians(90.0f), (float)16 / (float)9, 0.1f, 500.0f);

		// Or, for an ortho camera :
	   //glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
	   // Camera matrix
		View = glm::lookAt(
			glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
			);

		// Model matrix : an identity matrix (model will be at the origin)
		model = glm::mat4(1.0f);
		// Our ModelViewProjection : multiplication of our 3 matrices

		shader.SetMatrix4("model", model);
		shader.SetMatrix4("view", View);
		shader.SetMatrix4("projection", Projection);

		std::cout << "init dev scene" << std::endl;
	}

	void DevScene::Destroy()
	{
		std::cout << "destroy dev scene" << std::endl;
	}

	void DevScene::OnUpdate(float dt)
	{
		//angle = dt * 0.5f;
		//model = glm::rotate(model, angle, glm::vec3(0, 1, 0));
		//shader.SetMatrix4("model", model);
	}

	void DevScene::OnRender()
	{
		renderer->Prepare();
		m.Render();
	}
}