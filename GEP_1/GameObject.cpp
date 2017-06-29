#include "GameObject.h"

namespace engine
{
	//access static member
	int GameObject::GlobalID;

	GameObject::GameObject(std::string name)
	{
		setName(name);
		//addComponent<Transform>(); // Add a transform component to all GameObjects
		//Application::getGameObjects().push_back(shared<GameObject>(this)); // Add shared_ptr to created GameObject to vector in Application
		activeSelf = true; // Start active                                   // allowing easy update/rendering/etc of all GameObjects at once
		layer = 1 << 0;    // Default layer
		ID = GlobalID++;
	}

	GameObject::GameObject()
	{
		// As above, but without specified name
		activeSelf = true;
		layer = 1 << 0;
	}


	GameObject::~GameObject()
	{
		//for (size_t i = 0; i < components.size(); i++)
		//{
		//	delete components[i];
		//}
		//components.clear();
	}

	ref<GameObject> GameObject::create(std::string name)
	{
		ref<GameObject> rtn = create();
		rtn->name = name;

		return rtn;
	}

	ref<GameObject> GameObject::create()
	{
		ref<GameObject> rtn;

		rtn = new GameObject();

		return rtn;
	}

	void GameObject::Awake()
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			components.at(i)->awake();
		}
	}

	void GameObject::update(float dt)
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			components.at(i)->update(dt);

		}
	}

	void GameObject::update(float dt, std::vector<GameObject*> objects)
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			components.at(i)->update(dt, objects);
		}
	}

	void GameObject::Render(glm::mat4& viewMatrix, glm::mat4& projMatrix)
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			components.at(i)->Render(viewMatrix, projMatrix);
		}
	}

	void GameObject::Render(glm::mat4& viewMatrix, glm::mat4& projMatrix, glm::vec3 LightPos)
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			components.at(i)->Render(viewMatrix, projMatrix, LightPos);
		}
	}

	void GameObject::SetPosition(float posX, float posY, float posZ)
	{
		transform.setPostion(glm::vec3(posX, posY, posZ));
	}

	void GameObject::addComponent(Component* component)
	{
		component->gameObject = this;
		std::vector<Component*>::iterator it = std::find(this->components.begin(), this->components.end(), component);
		if (it == this->components.end())
		{
			this->components.push_back(component);
		}
		component->Awake();
	}

	void GameObject::removeComponent(Component* component)
	{
		std::vector<Component*>::iterator it = std::find(this->components.begin(), this->components.end(), component);
		if (it != this->components.end())
		{
			this->components.erase(it);
		}
	}

	Transform* GameObject::getTransform()
	{
		return &transform;
	}
}