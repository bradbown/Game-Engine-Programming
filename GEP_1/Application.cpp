#include "Application.h"
namespace engine
{

	Application::Application()
	{
	}

	Application::Application(int width, int height)
	{
		Application::width = width;
		Application::height = height;
	}

	Application::~Application()
	{

	}

	bool Application::init()
	{
		SDL_Init(SDL_INIT_EVERYTHING);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		window = SDL_CreateWindow("Engine", 100, 100, width, height, SDL_WINDOW_OPENGL);
		context = SDL_GL_CreateContext(window);
		renderer = SDL_CreateRenderer(window, -1, 0);

		// Specify the colour to clear the framebuffer to
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		srand(time(NULL));

		glewExperimental = GL_TRUE;

		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			/* Problem: glewInit failed, something is seriously wrong. */
			std::cerr << "Error: GLEW failed to initialise with message: " << glewGetErrorString(err) << std::endl;
			return false;
		}
		std::cout << "INFO: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

		std::cout << "INFO: OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
		std::cout << "INFO: OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
		std::cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "INFO: OpenGL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		SDL_ShowCursor(true);
		input = new Input();

		currentState = new GameState();

		camera = new Camera();
		Mesh* m_sphere = new Mesh("sphere2.obj", 1);
		meshes.push_back(m_sphere);
		Mesh* m_cube = new Mesh("cube.obj", 2);
		meshes.push_back(m_cube);
		Mesh* m_level1 = new Mesh("level1.obj", 1);
		meshes.push_back(m_level1);
		Mesh* m_cone = new Mesh("cone.obj", 1);
		meshes.push_back(m_cone);
		Mesh* m_cylinder = new Mesh("cylinder.obj", 1);
		meshes.push_back(m_cylinder);

		for (size_t i = 0; i < 7; i++)
		{
			Texture* T;
			T = new Texture();

			switch (i)
			{
			case 0:
				T->TextureInit("red.jpg");
				textures.push_back(T);
				break;
			case 1:
				T->TextureInit("blue.jpg");
				textures.push_back(T);
				break;
			case 2:
				T->TextureInit("green.jpg");
				textures.push_back(T);
				break;
			case 3:
				T->TextureInit("brick_wall2-diff-512.jpg");
				textures.push_back(T);
				break;
			case 4:
				T->TextureInit("grey.jpg");
				textures.push_back(T);
				break;
			case 5:
				T->TextureInit("brick_wall2-spec-512.jpg");
				textures.push_back(T);
				break;
			case 6:
				T->TextureInit("yellow.jpg");
				textures.push_back(T);
				break;
			}
		}

		bool dynamic = false;

		for (size_t i = 0; i < 15; i++)
		{
			int r = rand() % 3;
			GameObject* Sphere = new GameObject("Sphere");
			MeshRenderer* m = Sphere->AddComponent<MeshRenderer>();
			m->loadMesh(m_sphere);
			m->setTexture(textures[r]->getTexture());
			Sphere->AddComponent<RigidBody>();
			Sphere->AddComponent<SphereCollider>()->createBounds(m_sphere);
			addGameObject(&scene_1, Sphere);
		}
		for (size_t i = 0; i < scene_1.size(); i++)
		{
			scene_1.at(i)->SetPosition((rand() % 20) - 10, (rand() % 20) - 10, (rand() % 20) - 10);
		}
		//static cubes
		for (size_t i = 0; i < 4; i++)
		{
			GameObject* Cube = new GameObject("Cube");
			MeshRenderer* m = Cube->AddComponent<MeshRenderer>();
			m->loadMesh(m_cube);
			m->setTexture(textures[3]->getTexture());
			m->setNormalTexture(textures[4]->getTexture());
			m->setSpecularTexture(textures[5]->getTexture());
			Cube->AddComponent<RigidBody>();
			Cube->GetComponent<RigidBody>()->setDynamic(dynamic);
			//Cube->GetComponent<RigidBody>()->setMovement(glm::vec3(rand() % 10 - 5) * glm::vec3(2));
			Cube->GetComponent<RigidBody>()->setMovement(glm::vec3(0));
			Cube->AddComponent<CubeCollider>()->createBounds(m_cube);
			Cube->transform.setPostion(glm::vec3(i * 3.5, 0, 0));
			addGameObject(&scene_1, Cube);
		}
		//dynamic cubes
		for (size_t i = 0; i < 4; i++)
		{
			GameObject* Cube = new GameObject("Cube");
			MeshRenderer* m = Cube->AddComponent<MeshRenderer>();
			m->loadMesh(m_cube);
			m->setTexture(textures[3]->getTexture());
			m->setNormalTexture(textures[4]->getTexture());
			m->setSpecularTexture(textures[5]->getTexture());
			Cube->AddComponent<RigidBody>();
			Cube->GetComponent<RigidBody>()->setMovement(glm::vec3(0, 2, 0) * glm::vec3(2));
			//Cube->GetComponent<RigidBody>()->setMovement(glm::vec3(0));
			Cube->AddComponent<CubeCollider>()->createBounds(m_cube);
			Cube->transform.setPostion(glm::vec3(i * 3.5, -10, 0));
			addGameObject(&scene_1, Cube);
		}


		//////////////////////level1
		for (size_t x = 0; x < 50; x++)
		{
			for (size_t y = 0; y < 50; y++)
			{
				GameObject* Level1 = new GameObject("Level");
				MeshRenderer* m = Level1->AddComponent<MeshRenderer>();
				m->loadMesh(m_cube);
				m->setTexture(textures[1]->getTexture());
				Level1->transform.setPostion(glm::vec3(x * 2, 0, y * 2));
				addGameObject(&scene_2, Level1);
			}
		}
		//Leprechaun
		GameObject* Leprechaun1 = new GameObject("Leprechaun");
		MeshRenderer* m = Leprechaun1->AddComponent<MeshRenderer>();
		m->loadMesh(m_cone);
		m->setTexture(textures[2]->getTexture());
		Leprechaun1->transform.setPostion(glm::vec3(10, -2, 10));
		Leprechaun1->transform.setRotation(glm::vec3(135, 0, 0));
		Leprechaun1->AddComponent<Leprechaun>();
		addGameObject(&scene_2, Leprechaun1);
		
		//Gold
		for (size_t i = 0; i < 4; i++)
		{
			GameObject* _Gold = new GameObject("Gold");
			m = _Gold->AddComponent<MeshRenderer>();
			m->loadMesh(m_cylinder);
			m->setTexture(textures[6]->getTexture());
			_Gold->transform.setPostion(glm::vec3((rand() % 100), -2, (rand() % 100)));
			_Gold->AddComponent<Gold>();
			addGameObject(&scene_2, _Gold);
		}

		//house
		GameObject* _House = new GameObject("House");
		m = _House->AddComponent<MeshRenderer>();
		m->loadMesh(m_cube);
		m->setTexture(textures[2]->getTexture());
		_House->transform.setPostion(glm::vec3((rand() % 100), -2, (rand() % 100)));
		_House->AddComponent<House>();
		addGameObject(&scene_2, _House);

		//wolf
		for (size_t i = 0; i < 4; i++)
		{
			GameObject* _Wolf = new GameObject("Wolf");
			m = _Wolf->AddComponent<MeshRenderer>();
			m->loadMesh(m_cube);
			m->setTexture(textures[4]->getTexture());
			_Wolf->transform.setPostion(glm::vec3((rand() % 100), -2, (rand() % 100)));
			_Wolf->transform.setScale(glm::vec3(0.5, 0.5, 1));
			_Wolf->AddComponent<Wolf>();
			addGameObject(&scene_2, _Wolf);
		}
	
		//patrol points
		for (size_t i = 0; i < 10; i++)
		{
			GameObject* PatrolPoint = new GameObject("PatrolPoint");
			PatrolPoint->transform.setPostion(glm::vec3((rand() % 100), -2, (rand() % 100)));
			PatrolPoint->AddComponent<PatrolPoints>();
			addGameObject(&scene_2, PatrolPoint);
		}

		for (size_t i = 0; i < 10; i++)
		{
			GameObject* _Bush = new GameObject("Bush");
			m = _Bush->AddComponent<MeshRenderer>();
			m->loadMesh(m_sphere);
			m->setTexture(textures[2]->getTexture());
			_Bush->transform.setPostion(glm::vec3((rand() % 100), -2, (rand() % 100)));
			_Bush->AddComponent<Bush>();
			addGameObject(&scene_2, _Bush);
		}

		glViewport(0, 0, width, height);
		pos = glm::vec3(0, -10, 0);
		running = true;

		return true;

	}

	void Application::run()
	{
		currentState->stateID = SCENE_1_ASSIGNMENT_1;
		currentState->nextStateID = SCENE_1_ASSIGNMENT_1;
		currentState->prevStateID = SCENE_1_ASSIGNMENT_1;

		unsigned int lastTime = SDL_GetTicks();
		while (currentState->stateID != STATE_EXIT)
		{
			unsigned int current = SDL_GetTicks();
			float dt = (float)(current - lastTime) / 1000.0f;
			lastTime = current;

			if (dt < (1.0f / 60.0f))
			{
				SDL_Delay((unsigned int)(((1.0f / 60.0f) - dt) * 1000.0f));
			}

			while (currentState->stateID != STATE_PAUSE)
			{
				unsigned int current = SDL_GetTicks();
				float dt = (float)(current - lastTime) / 1000.0f;
				lastTime = current;

				if (dt < (1.0f / 60.0f))
				{
					SDL_Delay((unsigned int)(((1.0f / 60.0f) - dt) * 1000.0f));
				}


				// reset buffer
				glClearColor(0.0f, 0.0f, 0.3f, 0.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				//Draw

				input->update();
				update(dt);
				currentState->changeState();
				draw();

				SDL_GL_SwapWindow(window);
			}
			//Input update
			input->update();
			//Update the scene
			currentState->inputs(*input);
			currentState->update(dt);
			//Change state if needed
			currentState->changeState();
		}
		for (size_t i = 0; i < gameObjects.size(); i++)
		{
			delete gameObjects[i];
		}
		for (size_t i = 0; i < textures.size(); i++)
		{
			delete textures[i];
		}
		for (size_t i = 0; i < meshes.size(); i++)
		{
			delete meshes[i];
		}
		for (size_t i = 0; i < scene_1.size(); i++)
		{
			delete scene_1[i];
		}
		for (size_t i = 0; i < scene_2.size(); i++)
		{
			delete scene_2[i];
		}
		gameObjects.clear();
		textures.clear();
		meshes.clear();

		SDL_DestroyWindow(window);
		SDL_GL_DeleteContext(context);
		SDL_DestroyRenderer(renderer);
	}


	void Application::setTitle(std::string title)
	{
		SDL_SetWindowTitle(window, title.c_str());
	}


	void Application::update(float dt)
	{
		//std::cout << currentState->stateID << std::endl;
		camera->Control(*input);
		camera->Update();

		currentState->inputs(*input);
		currentState->update(dt);

		switch (currentState->stateID)
		{
		case SCENE_1_ASSIGNMENT_1:

			for (size_t i = 0; i < scene_1.size(); i++)
			{
				scene_1.at(i)->update(dt, scene_1);
			}
			break;

		case SCENE_2:
			
			for (size_t i = 0; i < scene_2.size(); i++)
			{
				scene_2.at(i)->update(dt, scene_2);
				//if (scene_2.at(i)->GetComponent<Gold>()->deleteGold)
				//{
				//	removeGameObject(&scene_2, scene_2.at(i));
				//}
			}
			break;
		}
	}

	void Application::draw()
	{
		switch (currentState->stateID)
		{
		case SCENE_1_ASSIGNMENT_1:

			for (size_t i = 0; i < scene_1.size(); i++)
			{
				scene_1.at(i)->Render(camera->getViewMatrix(), camera->getProjectionMatrix(), pos);
			}
			break;

		case SCENE_2:

			for (size_t i = 0; i < scene_2.size(); i++)
			{
				scene_2.at(i)->Render(camera->getViewMatrix(), camera->getProjectionMatrix(), glm::vec3(50, -40, 50));
			}
			break;
		}

	}

	void Application::addGameObject(std::vector<GameObject*>* scene, GameObject* gameObject)
	{
		std::vector<GameObject*>::iterator it = std::find(scene->begin(), scene->end(), gameObject);
		if (it == scene->end())
		{
			scene->push_back(gameObject);
		}
	}

	void Application::removeGameObject(std::vector<GameObject*>* scene, GameObject* gameObject)
	{
		std::vector<GameObject*>::iterator it = std::find(scene->begin(), scene->end(), gameObject);
		if (it != scene->end())
		{
			scene->erase(it);
		}
	}
}