//
// Created by michiel on 8/29/25.
//

#include <engine/playercontroller.h>
#include <engine/utils.h>
#include <engine/camera.h>
#include <engine/physics.h>

namespace engine {
	
	PlayerController::PlayerController(float speed, float jumpStrength)
			: speed(speed), jumpStrength(jumpStrength)
	{
	
	}
	
	Component *PlayerController::create(std::vector<std::string> args)
	{
		float speed = std::stof(args[0]);
		float jumpStrength = std::stof(args[1]);
		return new PlayerController(speed, jumpStrength);
	}
	
	bool PlayerController::registered = [] {
		ComponentFactory::registerType("playercontroller", &PlayerController::create);
		return true;
	}();
	
	void PlayerController::update(GLFWwindow *window)
	{
		//  ----- MOVEMENT -----
		float toMove(speed * Time::physicsDeltaTime);
		
		if (Input::getKeyState(window, GLFW_KEY_LEFT_SHIFT) == KeyState::Hold)
			toMove *= 1.2;
		
		if (Input::getKeyState(window, GLFW_KEY_W) == KeyState::Hold)
			transform->translate(toMove * Camera::get_main()->get_forwards());
		if (Input::getKeyState(window, GLFW_KEY_S) == KeyState::Hold)
			transform->translate(-toMove * Camera::get_main()->get_forwards());
		if (Input::getKeyState(window, GLFW_KEY_A) == KeyState::Hold)
			transform->translate(-toMove * Camera::get_main()->get_right());
		if (Input::getKeyState(window, GLFW_KEY_D) == KeyState::Hold)
			transform->translate(toMove * Camera::get_main()->get_right());
		if (Input::getKeyState(window, GLFW_KEY_SPACE) == KeyState::Press)
			jump();
		
		Camera::get_main()->transform.teleport(transform->position);
	}
	
	void PlayerController::jump()
	{
		transform->translate(0.1f, glm::vec3(0, 1, 0));
		getComponent<Rigidbody>()->setVelocity(jumpStrength, glm::vec3(0, 1, 0));
		isJumping = true;
	}
}