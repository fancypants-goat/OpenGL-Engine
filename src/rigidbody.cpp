//
// Created by michiel on 8/25/25.
//

#include <engine/rigidbody.h>
#include <engine/entity.h>
#include <engine/time.h>
#include <engine/box_collider.h>
#include <engine/component_factory.h>

namespace engine {
	Rigidbody::Rigidbody(float mass, float gravity)
			: mass(mass), gravity(gravity), velocity(0)
	{
	}
	
	Component *Rigidbody::create(const std::vector<std::string> args)
	{
		float mass = std::stof(args[0]);
		float gravity = std::stof(args[1]);
		return new Rigidbody(mass, gravity);
	}
	bool Rigidbody::registered = []{
		ComponentFactory::registerType("rigidbody", &Rigidbody::create);
		return true;
	}();
	
	
	void Rigidbody::update(GLFWwindow *window)
	{
		
		applyHalfGravity();
		
		if (requireComponent(boxCollider, true))
			boxCollider->resolveCollisions();
		
		translate(velocity * Time::physicsDeltaTime);
		applyHalfGravity();
	}
	
	void Rigidbody::applyHalfGravity()
	{
		velocity.y += gravity * Time::physicsDeltaTime / 2;
	}
	
	
	void Rigidbody::translate(glm::vec3 offset)
	{
		entity->transform.translate(offset);
	}
	
	void Rigidbody::translate(float x, float y, float z)
	{
		entity->transform.translate(x, y, z);
	}
	
	void Rigidbody::translate(float scale, glm::vec3 axis)
	{
		entity->transform.translate(scale, axis);
	}
	
	void Rigidbody::teleport(glm::vec3 offset)
	{
		entity->transform.teleport(offset);
	}
	
	void Rigidbody::teleport(float x, float y, float z)
	{
		entity->transform.teleport(x, y, z);
	}
	
	void Rigidbody::rotate(glm::vec3 rot)
	{
		entity->transform.rotate(rot);
	}
	
	void Rigidbody::rotate(float x, float y, float z)
	{
		entity->transform.rotate(x, y, z);
	}
	
	void Rigidbody::rotateTo(glm::vec3 rot)
	{
		entity->transform.rotateTo(rot);
	}
	
	void Rigidbody::rotateTo(float x, float y, float z)
	{
		entity->transform.rotateTo(x, y, z);
	}
	
	void Rigidbody::rotateAxis(float degrees, glm::vec3 axis)
	{
		entity->transform.rotateAxis(degrees, axis);
	}
	
	void Rigidbody::rotateToAxis(float degrees, glm::vec3 axis)
	{
		entity->transform.rotateToAxis(degrees, axis);
	}
	
	void Rigidbody::scale(glm::vec3 scale)
	{
		entity->transform.scale(scale);
	}
	
	void Rigidbody::scale(float x, float y, float z)
	{
		entity->transform.scale(x, y, z);
	}
	
	void Rigidbody::scale(float scale)
	{
		entity->transform.scale(scale);
	}
	
	void Rigidbody::scaleBy(glm::vec3 scale)
	{
		entity->transform.scaleBy(scale);
	}
	
	void Rigidbody::scaleBy(float x, float y, float z)
	{
		entity->transform.scaleBy(x, y, z);
	}
	
	void Rigidbody::scaleBy(float scale)
	{
		entity->transform.scaleBy(scale);
	}
	
	void Rigidbody::setVelocity(glm::vec3 v)
	{
		velocity = v;
	}
	
	void Rigidbody::setVelocity(float x, float y, float z)
	{
		velocity = glm::vec3(x, y, z);
	}
	
	void Rigidbody::setVelocity(float strength, glm::vec3 direction)
	{
		velocity = glm::normalize(direction) * strength;
	}
	
	void Rigidbody::addVelocity(glm::vec3 v)
	{
		velocity += v;
	}
	
	void Rigidbody::addVelocity(float x, float y, float z)
	{
		velocity += glm::vec3(x, y, z);
	}
	
	void Rigidbody::addVelocity(float strength, glm::vec3 direction)
	{
		velocity += glm::normalize(direction) * strength;
	}
	
	void Rigidbody::setVelocity(float scalar)
	{
		velocity = glm::vec3(scalar);
	}
} // engine