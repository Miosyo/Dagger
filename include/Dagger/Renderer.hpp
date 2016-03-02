#ifndef DAGGER_RENDERER_HPP
#define DAGGER_RENDERER_HPP

#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace Dagger
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void Prepare();
		void Render();
	private:
	};
}

#endif