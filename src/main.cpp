#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <Dagger\Common.hpp>

GLOBAL const int g_windowWidth = 854;
GLOBAL const int g_windowHeight = 480;

void glfwHints()
{
	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
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

	float vertices[] = {
		0.0f, 0.5f,
		-0.5f, -0.5f,
		0.5f, -0.5f
	};

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	const char* vertexSource = {
		"#version 120\n"
		"\n"
		"attribute vec2 position;"
		"void main()"
		"{"
		"gl_Position = vec4(position, 0, 1.0);"
		"}"
	};

	const char* fragmentSource = {
		"#version 120\n"
		"\n"
		"void main()"
		"{"
		"gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);"
		"}"
	};

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glBindAttribLocation(shaderProgram, 0, "position");

	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	while (isRunning)
	{
		glClearColor(0.2f, 0.2f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//DRAW
		{
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glDisableVertexAttribArray(0);
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