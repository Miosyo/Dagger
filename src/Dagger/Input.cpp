#include <Dagger/Input.hpp>

namespace Dagger
{
	bool Input::keys[1024];

	bool Input::isKeyDown(int keyCode)
	{
		return keys[keyCode];
	}

	bool Input::isKeyUp(int keyCode)
	{
		return !keys[keyCode];
	}

	void Input::keyCallback(int key, int scancode, int action, int mode)
	{
		if (key >= 0 && key < 1024)
		{
			if (action == GLFW_PRESS)
				keys[key] = GL_TRUE;
			else if (action == GLFW_RELEASE)
				keys[key] = GL_FALSE;
		}
	}
}