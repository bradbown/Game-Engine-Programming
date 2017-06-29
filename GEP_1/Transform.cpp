#include "Transform.h"

namespace engine
{

	Transform::Transform()
	{
		_position = glm::vec3(0, 0, 0);
		_scale = glm::vec3(1);
		_rotation = glm::vec3(0, 0, 0);
	}


	Transform::~Transform()
	{

	}

	glm::vec3 Transform::getPosition()
	{
		return _position;
	}

	glm::vec3 Transform::getRotation()
	{
		return _rotation;
	}

	glm::vec3 Transform::getScale()
	{
		return _scale;
	}

	void Transform::setPostion(glm::vec3 position)
	{
		_position = position;
	}

	void Transform::setRotation(glm::vec3 rotation)
	{
		_rotation = rotation;
	}

	void Transform::setScale(glm::vec3 scale)
	{
		_scale = scale;
	}

	void Transform::rotate()
	{

	}

	void Transform::translate(glm::vec3 translation) 
	{
		_position.x += translation.x;
		_position.y += translation.y;
		_position.z += translation.z;
	}
	void Transform::translate(glm::vec3* position, glm::vec3 translation)
	{
		position->x += translation.x;
		position->y += translation.y;
		position->z += translation.z;
	}
}