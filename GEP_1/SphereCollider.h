#pragma once

#include "Collider.h"

namespace engine
{

	class SphereCollider : public Collider
	{
	public:
		SphereCollider();
		~SphereCollider();

		float radius;

		bool VSSphere(SphereCollider* coll) override;
		bool VSCube(CubeCollider* coll) override;

		void createBounds(Mesh* mesh) override;
			
		float getScaledRadius();
	};

}