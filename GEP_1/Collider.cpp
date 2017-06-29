#include "Collider.h"

namespace engine
{

	Collider::Collider()
	{
	}


	Collider::~Collider()
	{
	}

	void Collider::createBounds(Mesh * mesh)
	{
	}
	
	float Collider::check(float p, float min, float max)
	{
		float out = 0;
		float v = p;
		if (v < min)
		{
			float tmp = min - v;
			out += tmp * tmp;
		}
		if (v > max)
		{
			float tmp = v - max;
			out += tmp * tmp;
		}

		return out;
	}

	float Collider::checkAABB(glm::vec3 pos, AABB aabb)
	{
		float out = 0;
		out += check(pos.x, aabb.min.x, aabb.max.x);
		out += check(pos.y, aabb.min.y, aabb.max.y);
		out += check(pos.z, aabb.min.z, aabb.max.z);

		return out;
	}
}