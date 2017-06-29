#include "Leprechaun.h"

namespace engine
{

	Leprechaun::Leprechaun()
	{
		brain.setState(IDLE);
		closestGoldIndex = closestWolfDistance = closestBushDistance = closestBushIndex = 1000;
		gold = 0;
		speed = 0.5;
	}


	Leprechaun::~Leprechaun()
	{
	}

	void Leprechaun::findGold(std::vector<GameObject*> gameObjects, float dt)
	{
		speed = 0.5;
		closestGoldDistance = 1000;

		for (size_t i = 0; i < gameObjects.size(); i++)
		{
			if (gameObjects.at(i)->GetComponent<Gold>())
			{
				if (closestGoldDistance > glm::distance(position, gameObjects.at(i)->transform.getPosition()) && !gameObjects.at(i)->GetComponent<Gold>()->pickedUp)
				{
					closestGoldIndex = i;
					closestGoldDistance = glm::distance(position, gameObjects.at(i)->transform.getPosition());
				}
			}
		}
		glm::vec3 direction = gameObjects.at(closestGoldIndex)->transform.getPosition() - position;
		if (glm::distance(position, gameObjects.at(closestGoldIndex)->transform.getPosition()) > 1 && !gameObjects.at(closestGoldIndex)->GetComponent<Gold>()->pickedUp)
		{
			glm::vec3 vel = ((direction * speed) * dt);
			gameObject->transform.translate(vel);
		}
		else
		{
			gold += 50;
			gameObjects.at(closestGoldIndex)->GetComponent<Gold>()->pickedUp = true;
			gameObjects.at(closestGoldIndex)->transform.setPostion(glm::vec3(gameObjects.at(closestGoldIndex)->transform.getPosition().x, 10, gameObjects.at(closestGoldIndex)->transform.getPosition().z));
		}
	}

	void Leprechaun::storeGold(std::vector<GameObject*> gameObjects, float dt)
	{
		speed = 0.5;
		glm::vec3 direction;
		int houseIndex;

		for (size_t i = 0; i < gameObjects.size(); i++)
		{
			if (gameObjects.at(i)->GetComponent<House>())
			{
				houseIndex = i;
				housePosition = gameObjects.at(i)->transform.getPosition();
				direction = housePosition - position;
			}
		}
		if (glm::distance(position, housePosition) > 1)
		{
			gameObject->transform.translate((direction * speed) * dt);
		}
		else
		{
			gameObjects.at(houseIndex)->GetComponent<House>()->storedGold += gold;
			gold = 0;
		}
	}

	void Leprechaun::runAway(std::vector<GameObject*> gameObjects, float dt)
	{
		//run to nearest bush
		speed = 0.7;
		closestBushDistance = 1000;
		for (size_t i = 0; i < gameObjects.size(); i++)
		{
			if (gameObjects.at(i)->GetComponent<Bush>())
			{
				if (closestBushDistance > glm::distance(position, gameObjects.at(i)->transform.getPosition()))
				{
					closestBushIndex = i;
					closestBushDistance = glm::distance(position, gameObjects.at(i)->transform.getPosition());
				}
			}
		}
		glm::vec3 direction = gameObjects.at(closestBushIndex)->transform.getPosition() - position;
		if (glm::distance(position, gameObjects.at(closestBushIndex)->transform.getPosition()) > 1)
		{
			glm::vec3 vel = ((direction * speed) * dt);
			gameObject->transform.translate(vel);
		}
		else
		{
			inBush = true;
		}
	}

	void Leprechaun::update(float dt, std::vector<GameObject*> objects)
	{
		position = gameObject->transform.getPosition();
		float houseDistance = glm::distance(position, housePosition);

		for (size_t i = 0; i < objects.size(); i++)
		{
			if (objects.at(i)->GetComponent<Gold>())
			{
				if (closestGoldDistance > glm::distance(position, objects.at(i)->transform.getPosition()))
				{
					closestGoldDistance = glm::distance(position, objects.at(i)->transform.getPosition());
				}
			}
		}

		for (size_t i = 0; i < objects.size(); i++)
		{
			if (objects.at(i)->GetComponent<Wolf>())
			{
				if (closestWolfDistance > glm::distance(position, objects.at(i)->transform.getPosition()))
				{
					closestWolfDistance = glm::distance(position, objects.at(i)->transform.getPosition());
					closestWolf = objects.at(i);
				}
			}
		}

		if (gold == 0)
		{
			brain.setNextState(FINDGOLD);
			inBush = false;
		}
		if (gold >= 100 || gold >= 30 && houseDistance < closestGoldDistance)
		{
			brain.setNextState(STOREGOLD);
			inBush = false;
		}
		if (glm::distance(position, closestWolf->transform.getPosition()) < 5)
		{
			brain.setNextState(RUNAWAY);
		}
		if (glm::distance(position, closestWolf->transform.getPosition()) > 80 && inBush)
		{
			brain.setNextState(FINDGOLD);
			inBush = false;
		}
		brain.changeState();
		std::cout << brain.activeState << std::endl;
		switch (brain.activeState)
		{
		case STATE_NULL:
			break;

		case IDLE:

			break;

		case FINDGOLD:
			findGold(objects, dt);
			break;

		case STOREGOLD:
			storeGold(objects, dt);
			break;

		case RUNAWAY:
			runAway(objects, dt);
			break;
		}
	}

}