#pragma once

#include "glm.hpp"
#include "FiniteStateMachine.h"
#include "Component.h"
#include "GameObject.h"

#include <time.h>

namespace engine
{

	class Wolf : public Component
	{
	public:
		Wolf();
		~Wolf();

		FiniteStateMachine brain;

		virtual void update(float dt, std::vector<GameObject*> objects) override;

		void chaseLeprechaun(std::vector<GameObject*> objects, float dt);
		void attack(std::vector<GameObject*> objects, float dt);
		void patrol(std::vector<GameObject*> objects, float dt);

		bool chasingLep;

	private:

		glm::vec3 position;
		glm::vec3 lepPosition;

		std::vector<GameObject*> patPoints;
		GameObject* patPoint1;
		GameObject* patPoint2;
		GameObject* leprechaun;
		int lepI;

		bool reachedP1, reachedP2;

		float speed;

		bool first, choosePatPoints;

		//Wolf
		enum states
		{
			STATE_NULL,
			IDLE,
			CHASELEPRECHAUN,
			ATTACKLEPRECHAUN,
			PATROL
		};

	};

}