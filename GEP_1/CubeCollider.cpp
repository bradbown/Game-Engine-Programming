#include "CubeCollider.h"
#include "GameObject.h"

namespace engine
{

	CubeCollider::CubeCollider()
	{
		boundingBox.max = glm::vec3(-100);
		boundingBox.min = glm::vec3(100);
	}


	CubeCollider::~CubeCollider()
	{

	}

	void CubeCollider::createBounds(Mesh * mesh)
	{
		std::vector<glm::vec3> verts = mesh->getMeshVerticies();

		for (size_t i = 0; i < verts.size(); i++)
		{
			if (boundingBox.max.x < verts[i].x)
				boundingBox.max.x = verts[i].x;
			if (boundingBox.max.y < verts[i].y)
				boundingBox.max.y = verts[i].y;
			if (boundingBox.max.z < verts[i].z)
				boundingBox.max.z = verts[i].z;

			if (boundingBox.min.x > verts[i].x)
				boundingBox.min.x = verts[i].x;
			if (boundingBox.min.y > verts[i].y)
				boundingBox.min.y = verts[i].y;
			if (boundingBox.min.z > verts[i].z)
				boundingBox.min.z = verts[i].z;
		}
		float s = gameObject->GetComponent<RigidBody>()->m;
		static int i = 0;
		//std::cout << s << std::endl;
		boundingBox.max *= s;
		boundingBox.min *= s;
		//std::cout << radius << std::endl;

	}

	bool CubeCollider::VSCube(CubeCollider* coll)
	{
		glm::vec3 pos1;
		glm::vec3 pos2;

		pos1 = this->gameObject->transform.getPosition();
		pos2 = coll->gameObject->transform.getPosition();

		if (pos1.x + this->boundingBox.max.x < pos2.x + coll->boundingBox.min.x || pos1.x + this->boundingBox.min.x > pos2.x + coll->boundingBox.max.x)
		{
			return false;
		}
		if (pos1.y + this->boundingBox.max.y < pos2.y + coll->boundingBox.min.y || pos1.y + this->boundingBox.min.y > pos2.y + coll->boundingBox.max.y)
		{
			return false;
		}
		if (pos1.z + this->boundingBox.max.z < pos2.z + coll->boundingBox.min.z || pos1.z + this->boundingBox.min.z > pos2.z + coll->boundingBox.max.z)
		{
			return false;
		}
		return true;
	}
	bool CubeCollider::VSSphere(SphereCollider* coll)
	{
		glm::vec3 sphere;
		glm::vec3 cube;

		cube = this->gameObject->transform.getPosition();
		sphere = coll->gameObject->transform.getPosition();


		glm::vec3 direction = cube - sphere;
		//glm::normalize(direction);
		
		//direction *= coll->radius;
		//direction += sphere;

		//glm::vec3 point = sphere + (direction * coll->radius);
		//
		//if (point.x < cube.x + getAABB().max.x && point.x > cube.x + getAABB().min.x &&
		//	point.y < cube.y + getAABB().max.y && point.y > cube.y + getAABB().min.y &&
		//	point.z < cube.z + getAABB().max.z && point.z > cube.z + getAABB().min.z)
		//	return true;

		float d = glm::distance(sphere, cube);
		//glm::normalize(d);
		if (d < coll->radius + ((cube.x + getAABB().max.x) * 0.5) && d > coll->radius + ((cube.x + getAABB().min.x) * 0.5))
			return true;
		if (d < coll->radius + ((cube.y + getAABB().max.y) * 0.5) && d > coll->radius + ((cube.y + getAABB().min.y) * 0.5))
			return true;
		if (d < coll->radius + ((cube.z + getAABB().max.z) * 0.5) && d > coll->radius + ((cube.z + getAABB().min.z) * 0.5))
			return true;

		return false;
	}

}