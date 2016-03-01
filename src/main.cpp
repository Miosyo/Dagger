#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

#include <glm\glm.hpp>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <Dagger\Common.hpp>
#include <Dagger\ResourceManager.hpp>
#include <Dagger\Shader.hpp>

GLOBAL const int g_windowWidth = 854;
GLOBAL const int g_windowHeight = 480;

INTERNAL void glfwHints()
{
	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

int main()
{
	GLFWwindow* window;
	if (!glfwInit())
		return EXIT_FAILURE;

	glfwHints();
	window = glfwCreateWindow(g_windowWidth, g_windowHeight, "Dagger", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glewInit();

	bool isRunning = true;
	bool isFullscreen = false;

	//Dagger::Shader shader = Dagger::Shader();
	//shader.Compile("data/shaders/default.vert", "data/shaders/default.frag");
	//shader.Use();

	while (isRunning)
	{
		glClearColor(0.2f, 0.2f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//DRAW
		{

		}
		//

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwWindowShouldClose(window) || glfwGetKey(window, GLFW_KEY_ESCAPE)) isRunning = false;
		if (glfwGetKey(window, GLFW_KEY_F11))
		{
			isFullscreen = !isFullscreen;
			GLFWwindow* newWindow;

			glfwHints();
			if (isFullscreen)
			{
				int count;
				const GLFWvidmode* modes = glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);

				newWindow = glfwCreateWindow(modes[count-1].width, modes[count-1].height, "Dagger", glfwGetPrimaryMonitor(), window);
			}
			else
				newWindow = glfwCreateWindow(g_windowWidth, g_windowHeight, "Dagger", nullptr, window);

			glfwDestroyWindow(window);
			window = newWindow;
			glfwMakeContextCurrent(window);
		}
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}