#pragma once

#include "glm.hpp"
#include "FiniteStateMachine.h"
#include "Component.h"
#include "GameObject.h"

namespace engine 
{

	class Leprechaun : public Component
	{
	public:
		Leprechaun();
		~Leprechaun();

		FiniteStateMachine brain;

		void findGold(std::vector<GameObject*> objects, float dt);

		void storeGold(std::vector<GameObject*> gameObjects, float dt);

		void runAway(std::vector<GameObject*> gameObjects, float dt);

		virtual void update(float dt, std::vector<GameObject*> objects) override;

		bool removeGold = false;
		bool runningAway = false;
		bool inBush = false;

		int gold;

		float speed;


	private:

		glm::vec3 position;
		glm::vec3 housePosition;

		float closestGoldDistance, closestWolfDistance, closestBushDistance;
		float closestGoldIndex, closestBushIndex;

		GameObject* closestWolf;

		//Leprechaun
		enum states
		{
			STATE_NULL,
			IDLE,
			FINDGOLD,
			STOREGOLD,
			HIDE,
			RUNAWAY
		};
	};

}