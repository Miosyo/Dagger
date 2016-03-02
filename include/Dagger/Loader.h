//#ifndef DAGGER_LOADER_HPP
//#define DAGGER_LOADER_HPP
//
//#include <GL\glew.h>
//
//#include <Dagger\RawModel.hpp>
//
//#include <vector>
//
//namespace Dagger
//{
//	class Loader
//	{
//	public:
//		std::vector<GLuint> VAOS;
//		std::vector<GLuint> VBOS;
//
//		Loader()
//		{
//			VAOS = std::vector<GLuint>();
//			VBOS = std::vector<GLuint>();
//		}
//
//		~Loader()
//		{
//
//		}
//
//		RawModel LoadModel(GLfloat positions[])
//		{
//			GLuint vaoID = createVAO();
//			storeDataInAttributeList(0, positions);
//			unbindVAO();
//			return RawModel(vaoID, 3);
//		}
//
//		GLuint createVAO()
//		{
//			GLuint vaoID;
//			VAOS.push_back(vaoID);
//			glGenVertexArrays(1, &vaoID);
//			glBindVertexArray(vaoID);
//			return vaoID;
//		}
//
//		void storeDataInAttributeList(int attributeNumber, GLfloat data[])
//		{
//			GLuint vboID;
//			VBOS.push_back(vboID);
//			glGenBuffers(1, &vboID);
//			glBindBuffer(GL_ARRAY_BUFFER, vboID);
//			glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
//			glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), nullptr);
//			glBindBuffer(GL_ARRAY_BUFFER, 0);
//			unbindVAO();
//		}
//
//		void unbindVAO()
//		{
//			glBindVertexArray(0);
//		}
//	};
//}
//
//#endif