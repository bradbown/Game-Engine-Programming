#pragma once

#include "Object.h"
#include "glm.hpp"

namespace engine
{

	class GameObject;
	class Application;

	class Component : public Object
	{
		friend class GameObject;
		friend class Application;

	public:
		virtual ~Component();

		GameObject* gameObject;
		GameObject getGameObject();

		virtual void update(float dt);
		virtual void update(float dt, std::vector<GameObject*> objects) { update(dt); };

		virtual void Render(glm::mat4& viewMatrix, glm::mat4& projMatrix);
		virtual void Render(glm::mat4& viewMatrix, glm::mat4& projMatrix, glm::vec3 LightPos);
		virtual void Awake();
		virtual void SetPosition(float posX, float posY, float posZ);

	private:

	};

}


