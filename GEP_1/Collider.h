#pragma once

#include "Component.h"
#include "Mesh.h"

namespace engine
{
	class SphereCollider;
	class CubeCollider;

	struct AABB {
		glm::vec3 min;
		glm::vec3 max;
	};

	class Collider : public Component
	{
	public:
		Collider();
		~Collider();

		virtual void createBounds(Mesh* mesh);
		virtual bool VSSphere(SphereCollider* other) { return false; };
		virtual bool VSCube(CubeCollider* other) { return false; };

		float checkAABB(glm::vec3 pos, AABB aabb);
		float check(float p, float min, float max);
	};

}