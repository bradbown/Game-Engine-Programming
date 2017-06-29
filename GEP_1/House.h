#pragma once

#include "Component.h"

namespace engine
{

	class House : public Component
	{
	public:
		House();
		~House();

		int storedGold;

	};
}
