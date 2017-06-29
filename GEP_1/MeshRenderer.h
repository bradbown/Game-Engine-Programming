#pragma once

#include "Component.h"
#include <GL/glew.h>
#include "glm.hpp"
#include "Mesh.h"
#include "GameObject.h"

namespace engine
{

	class MeshRenderer : public Component
	{
	public:

		MeshRenderer();
		~MeshRenderer();

		void update(float dt) override;
		void Render(glm::mat4& viewMatrix, glm::mat4& projMatrix) override;
		void Render(glm::mat4& viewMatrix, glm::mat4& projMatrix, glm::vec3 LightPos) override;

		void loadMesh(Mesh* mesh);
		void loadMesh(std::string filename, int light);

		void setTexture(GLuint Texture) { texture = Texture; }
		void setNormalTexture(GLuint texture) { normalTexID = texture; }
		void setSpecularTexture(GLuint texture) { specularTexID = texture; }

	protected:
		
		glm::mat4 _modelMatrix;
		Mesh* mesh;

		GLuint texture;
		GLuint normalTexID;
		GLuint specularTexID;
		
	private:



	};

}