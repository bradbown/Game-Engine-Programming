#pragma once

#include "ref.h"

namespace engine
{
	class Application;
	class GameObject;

	class Object : public enable_ref
	{
	public:

		std::string name;

		static void dontDestroyOnLoad(ref<Object> object);
		static void dontDestroyOnLoad(ref<GameObject> object);
		static void destroy(ref<Object> object);
		static void destroy(ref<GameObject> object);

		friend class Application;
		friend class GameObject;

		Object();
		virtual ~Object();

		void setName(std::string name);
		std::string getName();

		virtual void awake();

	private:
		bool destroyOnLoad;
		bool destroyed;

		//virtual void start();
		//virtual void update();
		//virtual void render();
		//virtual void postRender();
		//virtual void destroy();
	};

}
