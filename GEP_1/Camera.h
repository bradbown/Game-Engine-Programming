#pragma once

#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include "Input.h"
#include "glew.h"
#include <glm.hpp>
#include "Component.h"
#include "Transform.h"

namespace engine {

	class Camera : public Component
	{
	public:
		Camera(void);
		~Camera(void);

		void lockCamera();
		void Control(Input input);
		void Update();

		glm::mat4 getProjectionMatrix() { return projMatrix; }
		glm::mat4 getViewMatrix() { return viewMatrix; }

		inline void setPos(glm::vec3 pos) { position = pos; }

	protected:

	private:

		Transform* transform;

		glm::vec3 translation;
		glm::vec3 position;

		float horizontalAngle;
		float verticalAngle;

		float speed;
		float mouseSpeed;

		int posx, posy;
		glm::vec2 oldMousePosition;
		glm::mat4 viewMatrix;
		glm::mat4 projMatrix;

#ifndef M_PI
#define M_PI 3.1415926
#endif
	};


}