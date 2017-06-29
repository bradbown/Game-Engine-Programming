#pragma once

#include "Collider.h"

namespace engine
{
	class CubeCollider : public Collider
	{
	public:

		CubeCollider();
		~CubeCollider();

		AABB getAABB() { return boundingBox; }
		void createBounds(Mesh* mesh) override;
		bool VSCube(CubeCollider* coll) override;
		bool VSSphere(SphereCollider* coll) override;
		
	protected:

	private:

		AABB boundingBox;

	};

}