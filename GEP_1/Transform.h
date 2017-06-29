#pragma once

#include "glm.hpp"
#include "Component.h"

namespace engine
{

	class Transform 
	{
	public:
		Transform();
		~Transform();

		glm::vec3 getPosition();
		glm::vec3 getRotation();
		glm::vec3 getScale();

		void setPostion(glm::vec3 position);
		void setRotation(glm::vec3 rotation);
		void setScale(glm::vec3 scale);

		void rotate();
		void translate(glm::vec3 translation);

		void translate(glm::vec3* position, glm::vec3 translation);

	private:
		// Object position vector
		glm::vec3 _position;
		// Euler angles for rotation
		glm::vec3 _rotation;
		// Scale vector
		glm::vec3 _scale;
	};


}