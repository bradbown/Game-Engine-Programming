#include "Component.h"
#include "GameObject.h"

namespace engine 
{
	Component::~Component()
	{

	}

	GameObject Component::getGameObject()
	{
		return *gameObject;
	}

	void Component::Render(glm::mat4& viewMatrix, glm::mat4& projMatrix)
	{

	}

	void Component::Render(glm::mat4& viewMatrix, glm::mat4& projMatrix, glm::vec3 LightPos)
	{

	}

	void Component::Awake()
	{

	}

	void Component::SetPosition(float posX, float posY, float posZ)
	{

	}

	void Component::update(float dt)
	{

	}
}