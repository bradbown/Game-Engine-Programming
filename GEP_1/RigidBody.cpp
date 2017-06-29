#include "RigidBody.h"
#include <iostream>

namespace engine
{

	RigidBody::RigidBody()
	{
		movement = glm::vec3(rand() % 10 - 5) * glm::vec3(2);
		dynamic = true;
	}


	RigidBody::~RigidBody()
	{
	}

	void RigidBody::Awake()
	{
		m = 1; // ((rand() % 10) + 1) * 0.1f;
		gameObject->transform.setScale(glm::vec3(m));
	}

	void RigidBody::update(float dt)
	{
		gameObject->transform.translate(glm::vec3(0, 1, 0) * dt);
	}

	void RigidBody::update(float dt, std::vector<GameObject*> objects)
	{
		for (size_t i = gameObject->ID; i < objects.size(); i++)
		{
			if (gameObject->ID == objects[i]->ID)
				continue;
			if (hasCollider()) 
			{
				Collider* c = gameObject->GetComponent<SphereCollider>();
				if (c == nullptr)
					c = gameObject->GetComponent<CubeCollider>();
				if (objects[i]->GetComponent<RigidBody>()->hasCollider())
				{
					if ((objects[i]->GetComponent<SphereCollider>()) != nullptr)
					{
						if (c->VSSphere(objects[i]->GetComponent<SphereCollider>()))
						{
							glm::vec3 direction = objects[i]->getTransform()->getPosition() - gameObject->getTransform()->getPosition();
							//std::cout << direction.x << " , " << direction.y << " , " << direction.z << std::endl;
							glm::normalize(direction);
							//float diff = (objects[i]->GetComponent<SphereCollider>()->radius + gameObject->GetComponent<SphereCollider>()->radius) - glm::distance(objects[i]->getTransform()->getPosition(), gameObject->getTransform()->getPosition());
							//objects[i]->transform.translate((direction * diff) * 0.5f);
							//gameObject->transform.translate((-direction * diff) * 0.5f);
							if(gameObject->GetComponent<RigidBody>()->dynamic)
							{
								movement = gameObject->transform.getPosition() - objects[i]->transform.getPosition();
							}
							if(objects[i]->GetComponent<RigidBody>()->dynamic)
							{
								objects[i]->GetComponent<RigidBody>()->movement = objects[i]->transform.getPosition() - gameObject->transform.getPosition();
							}
						}
					}
					else
					{
						if (c->VSCube(objects[i]->GetComponent<CubeCollider>()))
						{
							if(gameObject->GetComponent<RigidBody>()->dynamic)
							{
								movement = gameObject->transform.getPosition() - objects[i]->transform.getPosition();
							}
							if(objects[i]->GetComponent<RigidBody>()->dynamic)
							{ 
								objects[i]->GetComponent<RigidBody>()->movement = objects[i]->transform.getPosition() - gameObject->transform.getPosition();
							}
						}
					}
				}
			}
			
		}
		if (glm::distance(gameObject->transform.getPosition(), glm::vec3(1)) > 20)
		{
			movement += glm::normalize(-(gameObject->transform.getPosition()));
		}

		gameObject->transform.translate(movement * dt);
	}

	bool RigidBody::hasCollider()
	{
		if (gameObject->GetComponent<Collider>() != nullptr)
		{
			return true;
		}
		return false;
	}
}