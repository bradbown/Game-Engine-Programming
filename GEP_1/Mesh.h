#pragma once

#include "Object.h"
#include <GL/glew.h>
#include "glm.hpp"
#include "ObjLoader.h"
#include "Shader.h"
#include "Component.h"
#include "Shader.h"

namespace engine
{

	class Mesh
	{
	public:

		Mesh();
		Mesh(std::string objFileName, std::string textureName, int light);
		Mesh(std::string objFileName, int shaderID);
		~Mesh();

		Shader* _shader;
		
		std::vector<glm::vec3>& getMeshVerticies() { return vertices; }

		GLuint InitialiseVAO(GLuint _VAO);

		void Render(glm::mat4& _modelMatrix, glm::mat4& viewMatrix, glm::mat4& projMatrix);
		void Render(glm::mat4& _modelmatrix, glm::mat4& viewMatrix, glm::mat4& projMatrix, glm::vec3 LightPos);
		void update(float dt);
		
		void setTexture(GLuint texture) { diffuseTexID = texture; }
		void setNormalTexture(GLuint texture) { normalTexID = texture; }
		void setSpecularTexture(GLuint texture) { specularTexID = texture; }

	protected:

		/// Vertex Array Object for model in OpenGL
		GLuint _VAO;

		/// Shader program
		GLuint shader;

		/// Uniform locations
		GLint _shaderModelMatLocation, _shaderViewMatLocation, _shaderProjMatLocation;

		/// Number of vertices in the model
		unsigned int _numVertices;

		GLuint diffuseTexID;
		GLuint normalTexID;
		GLuint specularTexID;

	private:

		/// Loads object model into OpenGL
		void InitialiseVAO();

		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> texcoords;
		std::vector<glm::vec3> meshTangets;
		std::vector<glm::vec3> meshBiTangents;

		GLuint positionBuffer;
		GLuint normalBuffer;
		GLuint texCoordBuffer;
		GLuint tangentBuffer;
		GLuint bitangentBuffer;

	};

}
