#pragma once

namespace engine
{

	class FiniteStateMachine
	{
	public:

		FiniteStateMachine();
		~FiniteStateMachine();

		void setState(int state) { activeState = state; }
		void update();

		int activeState;
		int previousState;
		int nextState;

		void setNextState(int newState);
		void changeState();
		
	};

}