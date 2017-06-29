#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Application.h"

namespace engine 
{
	class RigidBody : public Component
	{
		friend class Application;

	public:
		RigidBody();
		~RigidBody();

		glm::vec3 movement;

		void Awake() override;
		void update(float dt) override;
		virtual void update(float dt, std::vector<GameObject*> objects) override;

		bool hasCollider();

		float m;
		float a;

		bool dynamic;

		void setDynamic(bool d) { dynamic = d; }
		void setMass(bool mass) { m = mass; }
		void setMovement(glm::vec3 m) { movement = m; }

	private:

		

	};

}