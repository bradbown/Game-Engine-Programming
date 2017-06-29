#pragma once

#include "Component.h"

namespace engine
{

	class Gold : public Component
	{
	public:
		Gold();
		~Gold();

		bool pickedUp;

	};
}
