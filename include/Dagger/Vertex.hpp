#ifndef DAGGER_VERTEX_HPP
#define DAGGER_VERTEX_HPP

#include <GL\glew.h>
#include <glm\glm.hpp>

namespace Dagger
{
	struct Vertex {
		// Position
		glm::vec3 Position;
		// Normal
		glm::vec3 Normal;
		// TexCoords
		glm::vec2 TexCoords;
	};
}

#endif