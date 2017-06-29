#include "Wolf.h"

namespace engine
{

	Wolf::Wolf()
	{
		brain.setState(PATROL);
		chasingLep = false;
		first = choosePatPoints = true;
		reachedP1 = reachedP2 = false;

		srand(time(NULL));
	}


	Wolf::~Wolf()
	{
	}

	void Wolf::update(float dt, std::vector<GameObject*> objects)
	{
		if (first)
		{
			for (size_t i = 0; i < objects.size(); i++)
			{
				if (objects.at(i)->GetComponent<PatrolPoints>())
				{
					patPoints.push_back(objects.at(i));
				}
				else if (objects.at(i)->GetComponent<Leprechaun>())
				{
					leprechaun = objects.at(i);
					lepI = i;
				}
			}
			first = false;
		}
		position = gameObject->transform.getPosition();

		//for (size_t i = 0; i < objects.size(); i++)
		//{
		//	if (objects.at(i)->GetComponent<Leprechaun>())
		//	{
		//		leprechaun = objects.at(i);
		//		lepPosition = objects.at(i)->transform.getPosition();
		//		lepI = i;
		//	}
		//}

		if (!objects.at(lepI)->GetComponent<Leprechaun>()->inBush && (glm::distance(objects.at(lepI)->transform.getPosition(), position) < 20))
		{
			chasingLep = true;
			brain.setNextState(CHASELEPRECHAUN);
		}
		else if(objects.at(lepI)->GetComponent<Leprechaun>()->inBush)
		{
			chasingLep = false;
		}

		if (!chasingLep)
		{
			brain.setNextState(PATROL);
		}
		brain.changeState();

		switch (brain.activeState)
		{
		case STATE_NULL:
			break;

		case IDLE:
			break;

		case CHASELEPRECHAUN:
			chaseLeprechaun(objects, dt);
			break;

		case ATTACKLEPRECHAUN:
			attack(objects, dt);
			break;

		case PATROL:
			patrol(objects, dt);
			break;

		}
	}

	void Wolf::chaseLeprechaun(std::vector<GameObject*> objects, float dt)
	{
		speed = 0.4;
		if (glm::distance(position, objects.at(lepI)->transform.getPosition()) > 1)
		{
			glm::vec3 direction = objects.at(lepI)->transform.getPosition() - position;
			gameObject->transform.translate((direction * speed) * dt);
		}
		reachedP1 = reachedP2 = true;
	}

	void Wolf::attack(std::vector<GameObject*> objects, float dt)
	{
	}

	void Wolf::patrol(std::vector<GameObject*> objects, float dt)
	{
		glm::vec3 direction;
		speed = 0.3;

		if (reachedP1 && reachedP2)
		{
			choosePatPoints = true;
			reachedP1 = reachedP2 = false;
		}

		//patrol between 2 randomly chosen patrol points on the map
		if (choosePatPoints)
		{
			patPoint1 = patPoints.at(rand() % 10);
			patPoint2 = patPoints.at(rand() % 10);
			choosePatPoints = false;
		}
		if (glm::distance(position, patPoint1->transform.getPosition()) > 1 && !reachedP1)
		{
			direction = patPoint1->transform.getPosition() - position;
			gameObject->transform.translate((direction * speed) * dt);
		}
		else if (glm::distance(position, patPoint1->transform.getPosition()) < 1 && !reachedP1)
		{
			reachedP1 = true;
		}
		else if (glm::distance(position, patPoint2->transform.getPosition()) > 1 && !reachedP2)
		{
			direction = patPoint2->transform.getPosition() - position;
			gameObject->transform.translate((direction * speed) * dt);
		}
		else if (glm::distance(position, patPoint2->transform.getPosition()) < 1 && !reachedP2)
		{
			reachedP2 = true;
		}
	}
}