#ifndef DAGGER_VERTEX_HPP
#define DAGGER_VERTEX_HPP

#include <GL\glew.h>

namespace Dagger
{
	struct Vertex
	{
		GLfloat x, y, z;
		GLfloat r, g, b, a;
		GLfloat t, v;
	};
}

#endif