//
// Created by michiel on 8/25/25.
//

#include <engine/rigidbody.h>
#include <engine/entity.h>
#include <engine/time.h>

namespace engine {
	Rigidbody::Rigidbody(float mass, float gravity)
		: mass(mass), gravity(gravity)
	{
	}
	
	
	void Rigidbody::update()
	{
		applyHalfGravity();
		translate(velocity * Time::deltaTime);
		applyHalfGravity();
	}
	
	void Rigidbody::applyHalfGravity()
	{
		velocity.y += gravity * Time::deltaTime / 2;
	}
	
	
	
	void Rigidbody::translate(glm::vec3 offset)
	{
		entity->transform.translate(offset);
	}
	
	void Rigidbody::translate(float x, float y, float z)
	{
		entity->transform.translate(x, y, z);
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
} // engine