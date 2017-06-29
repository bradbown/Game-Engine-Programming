#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

#pragma once

#include <SDL.h>
#include <GL/glew.h>
#include "ref.h"

#include "Input.h"
#include "Object.h"
#include "GameObject.h"
#include "Shader.h"

#include "Camera.h"
#include "Mesh.h"
#include "RigidBody.h"
#include "SphereCollider.h"
#include "MeshRenderer.h"
#include "Texture.h"
#include "CubeCollider.h"
#include "GameState.h"
#include "Leprechaun.h"
#include "Gold.h"
#include "House.h"
#include "Wolf.h"
#include "PatrolPoints.h"
#include "Bush.h"

#include <string>
#include <time.h>


namespace engine
{
	class RigidBody;
	class MeshRenderer;

	class Application : public GameState
	{
	public:
		Application();
		Application(int width, int height);
		~Application();

		bool init();
		void destroy();
		void run();
		void quit();
		void setTitle(std::string title);

		Shader* shader;

		std::vector<GameObject*> gameObjects;
		std::vector<Texture*> textures;
		std::vector<Mesh*> meshes;

		GLuint sphere_vao;

		void addGameObject(std::vector<GameObject*>*, GameObject* gameObject);
		void removeGameObject(std::vector<GameObject*>*, GameObject* gameObject);

		std::vector<GameObject*> scene_1;
		std::vector<GameObject*> scene_2;
		GameState* currentState = NULL;

	protected:

		SDL_Window* window;
		SDL_GLContext context;
		SDL_Renderer* renderer;

		Input* input;
		Camera* camera;

		int width, height;

	private:

		bool running;

		void reshape(int width, int height);
		void display();

		void update(float dt);
		void draw();

		glm::vec3 pos;
	};

}
#endif

