#pragma once

#include "Component.h"
#include "Application.h"
#include "Transform.h"

namespace engine
{

	class Component;

	class GameObject : public Object
	{
		friend class engine::Application;

	public:

		GameObject();
		GameObject(std::string name);
		~GameObject();

		static ref<GameObject> create();
		static ref<GameObject> create(std::string name);

		virtual void Render(glm::mat4& viewMatrix, glm::mat4& projMatrix);
		virtual void Render(glm::mat4& viewMatrix, glm::mat4& projMatrix, glm::vec3 LightPos);
		virtual void SetPosition(float posX, float posY, float posZ);

		Transform* getTransform();

		void Awake();
		virtual void update(float dt);
		virtual void update(float dt, std::vector<GameObject*> objects);
		
		template<class T>
		T* AddComponent()
		{
			T* c(new T());

			c->gameObject = this;
			components.push_back(c);
			c->Awake();

			return c;
		}
		template<class T>
		T* GetComponent()
		{
			for (unsigned int i = 0; i < components.size(); i++)
			{
				if (T* c = dynamic_cast<T*>(components[i]))
				{
					return c;
				}
			}
			return nullptr;
		}

		void addComponent(Component* component);
		void removeComponent(Component* component);

		Transform transform;

		int ID;

	private:

		std::vector<Component*> components;
		bool activeSelf;
		int layer;
		std::string tag;

		static int GlobalID;
	};
}