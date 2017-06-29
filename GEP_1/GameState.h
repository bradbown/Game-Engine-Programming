#pragma once

#include "glm.hpp"
#include "Input.h"
#include "Camera.h"

namespace engine
{
	class GameState
	{
	public:
		GameState();
		~GameState();

		enum GameStates
		{
			STATE_NULL,
			SCENE_1_ASSIGNMENT_1,
			SCENE_2,
			STATE_EXIT,
			STATE_PAUSE
		};

		virtual void update(float dt);
		virtual void Render(glm::mat4& viewMatrix, glm::mat4& projMatrix, glm::vec3 LightPos);

		int stateID;
		int nextStateID;
		int prevStateID;

		//State status manager
		void setNextState(int newState);

		void inputs(Input input);

		//State changer
		void changeState();

	};
}