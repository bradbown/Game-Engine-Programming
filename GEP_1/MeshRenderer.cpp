#include "MeshRenderer.h"
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

namespace engine 
{
	MeshRenderer::MeshRenderer()
	{

	}


	MeshRenderer::~MeshRenderer()
	{

	}

	void MeshRenderer::update(float dt)
	{
		// Build the model matrix!
		// First we start with an identity matrix
		// This is created with the command: glm::mat4(1.0f)
		//_modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(gameObject->GetComponent<RigidBody>()->m));
		_modelMatrix = glm::translate(glm::mat4(1.0f), gameObject->getTransform()->getPosition());
		_modelMatrix = glm::rotate(_modelMatrix, gameObject->getTransform()->getRotation().x, glm::vec3(1, 0, 0));
		_modelMatrix = glm::rotate(_modelMatrix, gameObject->getTransform()->getRotation().y, glm::vec3(0, 1, 0));
		_modelMatrix = glm::rotate(_modelMatrix, gameObject->getTransform()->getRotation().z, glm::vec3(0, 0, 1));
		_modelMatrix = glm::scale (_modelMatrix, gameObject->getTransform()->getScale());
	}

	void MeshRenderer::Render(glm::mat4& viewMatrix, glm::mat4& projMatrix)
	{

	}

	void MeshRenderer::Render(glm::mat4& viewMatrix, glm::mat4& projMatrix, glm::vec3 LightPos)
	{
		mesh->setTexture(texture);
		mesh->setNormalTexture(normalTexID);
		mesh->setSpecularTexture(specularTexID);
		mesh->Render(_modelMatrix, viewMatrix, projMatrix, LightPos);
	}
	
	void MeshRenderer::loadMesh(Mesh* mesh)
	{
		this->mesh = mesh;
	}

	void MeshRenderer::loadMesh(std::string filename, int light)
	{
		mesh = new Mesh(filename, light);
	}
}