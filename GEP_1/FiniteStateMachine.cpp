#include "FiniteStateMachine.h"

namespace engine
{

	FiniteStateMachine::FiniteStateMachine()
	{
	}


	FiniteStateMachine::~FiniteStateMachine()
	{
	}

	void FiniteStateMachine::update()
	{
	}

	void FiniteStateMachine::setNextState(int newState)
	{
		nextState = newState;
	}

	void FiniteStateMachine::changeState()
	{
		if (nextState != 0)
		{
			previousState = activeState;
			activeState = nextState;
		}
		nextState = 0;
	}

}