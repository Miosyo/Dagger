#include <Dagger\Game.hpp>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <Game\DevScene.hpp>

namespace Dagger
{
	namespace
	{
		GLFWwindow* window;
		std::string windowTitle = "Dagger";
		int windowWidth = 854;
		int windowHeight = 480;
		SceneManager* sceneManager;

	} //GLOBALS

	INTERNAL void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		Input::keyCallback(key, scancode, action, mode);
	}

	INTERNAL void glfwHints()
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	}

	bool Init()
	{
		if (!glfwInit())
		{
			std::cout << "GAME::INIT::FAILURE glfw failed to init" << std::endl;
			return false;
		}

		glfwHints();
		window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), nullptr, nullptr);

		if (!window)
		{
			glfwTerminate();
			std::cout << "GAME::INIT::FAILURE Window failed to create" << std::endl;
			return false;
		}

		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);

		glewInit();
		glGetError();

		glfwSetKeyCallback(window, key_callback);

		//glViewport(0, 0, windowWidth, windowHeight);
		//glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glDepthFunc(GL_LESS);
		std::cout << "GAME::GL::INIT::SUCCESS" << std::endl;

		//non gl inits
		sceneManager = new SceneManager();
		sceneManager->PushScene(new ::Game::DevScene());

		return true;
	}

	void Run()
	{
		// DeltaTime variables
		GLfloat deltaTime = 0.0f;
		GLfloat lastFrame = 0.0f;

		while (!glfwWindowShouldClose(window))
		{
			// Calculate delta time
			double currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			glfwPollEvents();

			// Manage user input
			//Enchantment.ProcessInput(deltaTime);
			sceneManager->UpdateScene(deltaTime);
			// Update Game state
			//Enchantment.Update(deltaTime);

			// Render
			//glClearColor(0.4f, 0.4f, 0.8f, 1.0f);
			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//Enchantment.Render();
			sceneManager->RenderScene();

			glfwSwapBuffers(window);
		}
		Cleanup();
	}

	void Cleanup()
	{
		sceneManager->~SceneManager();
		delete sceneManager;

		glfwDestroyWindow(window);
		// Delete all resources as loaded using the resource manager
		ResourceManager::Clear();

		glfwTerminate();
	}

	GLFWwindow* getGLFWWindow()
	{
		return window;
	}

	glm::vec2 getWindowSize()
	{
		return glm::vec2(windowWidth, windowHeight);
	}
}