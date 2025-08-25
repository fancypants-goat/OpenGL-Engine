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
		translate(velocity);
		applyHalfGravity();
	}
	
	void Rigidbody::applyHalfGravity()
	{
		velocity.y += gravity * Time::deltaTime / 2;
	}
	
	
	
	void Rigidbody::translate(glm::vec3 offset)
	{
		parent->transform.translate(offset);
	}
	
	void Rigidbody::translate(float x, float y, float z)
	{
		parent->transform.translate(x, y, z);
	}
	
	void Rigidbody::teleport(glm::vec3 offset)
	{
		parent->transform.teleport(offset);
	}
	
	void Rigidbody::teleport(float x, float y, float z)
	{
		parent->transform.teleport(x, y, z);
	}
	
	void Rigidbody::rotate(glm::vec3 rot)
	{
		parent->transform.rotate(rot);
	}
	
	void Rigidbody::rotate(float x, float y, float z)
	{
		parent->transform.rotate(x, y, z);
	}
	
	void Rigidbody::rotateTo(glm::vec3 rot)
	{
		parent->transform.rotateTo(rot);
	}
	
	void Rigidbody::rotateTo(float x, float y, float z)
	{
		parent->transform.rotateTo(x, y, z);
	}
	
	void Rigidbody::rotateAxis(float degrees, glm::vec3 axis)
	{
		parent->transform.rotateAxis(degrees, axis);
	}
	
	void Rigidbody::rotateToAxis(float degrees, glm::vec3 axis)
	{
		parent->transform.rotateToAxis(degrees, axis);
	}
	
	void Rigidbody::scale(glm::vec3 scale)
	{
		parent->transform.scale(scale);
	}
	
	void Rigidbody::scale(float x, float y, float z)
	{
		parent->transform.scale(x, y, z);
	}
	
	void Rigidbody::scale(float scale)
	{
		parent->transform.scale(scale);
	}
	
	void Rigidbody::scaleBy(glm::vec3 scale)
	{
		parent->transform.scaleBy(scale);
	}
	
	void Rigidbody::scaleBy(float x, float y, float z)
	{
		parent->transform.scaleBy(x, y, z);
	}
	
	void Rigidbody::scaleBy(float scale)
	{
		parent->transform.scaleBy(scale);
	}
} // engine