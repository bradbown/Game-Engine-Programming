#include "Camera.h"

namespace engine 
{

	Camera::Camera()
	{
		position = glm::vec3(-9, 0, -12);
		horizontalAngle = 3.14f;
		verticalAngle = 0.0f;

		speed = 1.1f;
		mouseSpeed = 0.005f;

		oldMousePosition = glm::vec2(0);

		transform = new Transform();
	}


	Camera::~Camera()
	{

	}

	void Camera::lockCamera()
	{
		if (verticalAngle > 90)
		{
			verticalAngle = 90;
		}
		if (verticalAngle < -90)
		{
			verticalAngle = -90;
		}

		if (horizontalAngle < 0.0)
		{
			horizontalAngle += 360.0;
		}
		if (horizontalAngle > 360.0)
		{
			horizontalAngle -= 360;
		}
	}

	void Camera::Control(Input Input)
	{
		int Mid_X = 400;
		int Mid_Y = 300;
		/// move the mouse back to the middle of the screen each frame
		SDL_WarpMouseInWindow(NULL, 400, 300);
		/// get the current position of the cursor
		SDL_GetMouseState(&posx, &posy);

		float diff_x = Mid_X - oldMousePosition.x;
		float diff_y = Mid_Y - oldMousePosition.y;

		horizontalAngle -= mouseSpeed * (posx - oldMousePosition.x + diff_x);
		verticalAngle += mouseSpeed * (posy - oldMousePosition.y + diff_y);
		oldMousePosition = glm::vec2(posx, posy);


		glm::vec3 direction(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));
		glm::vec3 right = glm::vec3(sin(horizontalAngle - 3.14f / 2.0f), 0, cos(horizontalAngle - 3.14f / 2.0f));
		glm::vec3 up = glm::cross(right, direction);

		//lockCamera();

		/// Move camera in a direction
		if (Input.cmd_w)
		{
			translation = direction * speed;
			transform->translate(&position, translation);
		}
		else if (Input.cmd_s)
		{
			translation = -(direction * speed);
			transform->translate(&position, translation);
		}
		if (Input.cmd_a)
		{
			translation = -(right * speed);
			transform->translate(&position, translation);
		}
		else if (Input.cmd_d)
		{
			translation = right * speed;
			transform->translate(&position, translation);
		}
		if (Input.cmd_space)
		{
			float rad = (verticalAngle - 135)*M_PI / 180.0;
			position.y += sin(rad) * speed;
		}
		if (Input.cmd_q)
		{
			float rad = (verticalAngle - 135)*M_PI / 180.0;
			position.y -= sin(rad) * speed;
		}

		/// the matrices used to see the models are changed.
		projMatrix = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 10000.0f);
		viewMatrix = glm::lookAt(position, position + direction, up);
	}

	void Camera::Update()
	{
		glTranslatef(-position.x, -position.y, -position.z);
		glRotatef(-verticalAngle * 2, 1.0, 0.0, 0.0);
		glRotatef(horizontalAngle * 2, 0.0, 1.0, 0.0);
	}

}