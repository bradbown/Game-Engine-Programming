#include "GameState.h"

namespace engine
{

	GameState::GameState()
	{
		int stateID = SCENE_1_ASSIGNMENT_1;
		int nextStateID = SCENE_1_ASSIGNMENT_1;
	}


	GameState::~GameState()
	{
	}

	void GameState::update(float dt)
	{

	}

	void GameState::Render(glm::mat4 & viewMatrix, glm::mat4 & projMatrix, glm::vec3 LightPos)
	{

	}

	void GameState::setNextState(int newState)
	{
		//Set the next state
		nextStateID = newState;
	}

	void GameState::inputs(Input input)
	{
		if (input.cmd_1)
		{
			setNextState(SCENE_1_ASSIGNMENT_1);
		}
		else if (input.cmd_2)
		{
			setNextState(SCENE_2);
		}
		else if (input.Quit)
		{
			if (stateID != STATE_PAUSE)
				setNextState(STATE_PAUSE);
			else
				setNextState(STATE_EXIT);
		}
		else if (input.cmd_x && stateID != STATE_PAUSE)
		{
			setNextState(STATE_PAUSE);
		}
		else if (input.cmd_c && stateID == STATE_PAUSE)
		{
			setNextState(prevStateID);
		}
	}

	void GameState::changeState()
	{

		if (nextStateID != STATE_NULL)
		{
			prevStateID = stateID;
			//Change the current state ID
			stateID = nextStateID;
		}

		//NULL the next state ID
		nextStateID = STATE_NULL;
	}

}