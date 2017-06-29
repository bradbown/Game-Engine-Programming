#include "SphereCollider.h"
#include "GameObject.h"

namespace engine
{

	SphereCollider::SphereCollider()
	{

	}


	SphereCollider::~SphereCollider()
	{

	}

	bool SphereCollider::VSSphere(SphereCollider* coll)
	{
		float d = glm::distance(gameObject->transform.getPosition(), coll->gameObject->transform.getPosition());

		if (d < radius + coll->radius)
		{
			return true;
		}
		return false;
	}
	bool SphereCollider::VSCube(CubeCollider* coll)
	{
		glm::vec3 sphere;
		glm::vec3 cube;

		sphere = this->gameObject->transform.getPosition();
		cube = coll->gameObject->transform.getPosition();

		glm::vec3 direction = cube - sphere;
		//glm::normalize(direction);
		
		//direction *= radius;
		//direction += sphere;

		//glm::vec3 point = sphere + (direction * radius);
		//
		//if (point.x < cube.x + coll->getAABB().max.x && point.x > cube.x + coll->getAABB().min.x &&
		//	point.y < cube.y + coll->getAABB().max.y && point.y > cube.y + coll->getAABB().min.y &&
		//	point.z < cube.z + coll->getAABB().max.z && point.z > cube.z + coll->getAABB().min.z)
		//	return true;

		float d = glm::distance(sphere, cube);
		//glm::normalize(d);
		if (d < radius + ((cube.x + coll->getAABB().max.x) * 0.5) && d > radius + ((cube.x + coll->getAABB().min.x) * 0.5))
			return true;
		if (d < radius + ((cube.y + coll->getAABB().max.y) * 0.5) && d > radius + ((cube.y + coll->getAABB().min.y) * 0.5))
			return true;
		if (d < radius + ((cube.z + coll->getAABB().max.z) * 0.5) && d > radius + ((cube.z + coll->getAABB().min.z) * 0.5))
			return true;

		return false;
	}

	void SphereCollider::createBounds(Mesh* mesh)
	{
		float max = -100;
		float min = 100;

		std::vector<glm::vec3> verts = mesh->getMeshVerticies();

		for (size_t i = 0; i < verts.size(); i++)
		{
			if (max < verts[i].x)
			{
				max = verts[i].x;
			}


			if (min > verts[i].x)
			{
				min = verts[i].x;
			}
		}
		float s = gameObject->GetComponent<RigidBody>()->m;
		static int i = 0;
		//std::cout << s << std::endl;
		radius = ((max * s) - (min * s)) / 2;
		//std::cout << radius << std::endl;
	}

	float SphereCollider::getScaledRadius()
	{
		return radius * gameObject->getTransform()->getScale().x;
	}
}