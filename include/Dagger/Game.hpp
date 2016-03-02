#ifndef DAGGER_GAME_GAME_HPP
#define DAGGER_GAME_GAME_HPP

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

#include <glm\glm.hpp>

#include <Dagger\Common.hpp>
#include <Dagger\ResourceManager.hpp>
#include <Dagger\Input.hpp>
#include <Dagger\SceneManager.hpp>

namespace Dagger
{
	bool Init();
	void Run();
	void Cleanup();
	GLFWwindow* getGLFWWindow();
	glm::vec2 getWindowSize();
}

#endif