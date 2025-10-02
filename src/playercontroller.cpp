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
		feetCollider = new BoxCollider(math::vec3(.8, .05, .8), math::vec3(0, -1, 0));
		feetCollider->isTrigger = true;
		feetCollider->collisionMode = BoxCollider::Advanced;
	}
	
	Component *PlayerController::create(const std::vector<std::string> &args)
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
		Camera::get_main()->transform.translate(0, 0.5, 0);

		transform->rotateToAxis(-Camera::get_main()->transform.rotation.y, math::vec3const::up);
	}
	
	void PlayerController::jump()
	{
		if (feetCollider->collidesWithFirst().collided)
		{
			transform->translate(0.1f, math::vec3const::up);
			getComponent<Rigidbody>()->setVelocity(jumpStrength, math::vec3(0, 1, 0));
		}
	}
}