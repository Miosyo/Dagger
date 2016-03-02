#ifndef DAGGER_INPUTMANAGER_HPP
#define DAGGER_INPUTMANAGER_HPP

#include <GLFW\glfw3.h>

namespace Dagger
{
	class Input
	{
	public:
		static bool keys[1024];

		static void keyCallback(int key, int scancode, int action, int mode);

		static bool isKeyDown(int keyCode);
		static bool isKeyUp(int keyCode);
	private:
		Input() { }
	};
}

#endif