//
// Created by michiel on 8/16/25.
//

#include <engine/transform.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <engine/entity.h>
#include <iostream>

namespace engine {
	Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 size)
			: position(position), rotation(rotation), size(size), parent(nullptr)
	{
	}
	
	void Transform::translate(glm::vec3 offset)
	{
		position += offset;
	}
	
	void Transform::translate(float x, float y, float z)
	{
		position += glm::vec3(x, y, z);
	}
	
	void Transform::teleport(glm::vec3 offset)
	{
		position = offset;
	}
	
	void Transform::teleport(float x, float y, float z)
	{
		position = glm::vec3(x, y, z);
	}
	
	void Transform::rotate(glm::vec3 rot)
	{
		rotation += rot;
	}
	
	void Transform::rotate(float x, float y, float z)
	{
		rotation += glm::vec3(x, y, z);
	}
	
	void Transform::rotateTo(glm::vec3 rot)
	{
		rotation = rot;
	}
	
	void Transform::rotateTo(float x, float y, float z)
	{
		rotation = glm::vec3(x, y, z);
	}
	
	void Transform::rotateAxis(float degrees, glm::vec3 axis)
	{
		rotation += degrees * glm::normalize(axis);
	}
	
	void Transform::rotateToAxis(float degrees, glm::vec3 axis)
	{
		rotation = degrees * glm::normalize(axis);
	}
	
	void Transform::scale(glm::vec3 scale)
	{
		size = scale;
	}
	
	void Transform::scale(float x, float y, float z)
	{
		size = glm::vec3(x, y, z);
	}
	
	void Transform::scale(float scale)
	{
		size = glm::vec3(scale);
	}
	
	void Transform::scaleBy(glm::vec3 scale)
	{
		size *= scale;
	}
	
	void Transform::scaleBy(float x, float y, float z)
	{
		size *= glm::vec3(x, y, z);
	}
	
	void Transform::scaleBy(float scale)
	{
		size *= glm::vec3(scale);
	}
	
	
	glm::mat4 Transform::positionMatrix() const
	{
		return glm::translate(glm::mat4(1), globalPosition());
	}
	
	glm::mat4 Transform::rotationMatrix() const
	{
		glm::mat4 rot (1);
		rot = glm::rotate(rot, glm::radians(globalRotation().x), glm::vec3(1, 0, 0));
		rot = glm::rotate(rot, glm::radians(globalRotation().y), glm::vec3(0, 1, 0));
		rot = glm::rotate(rot, glm::radians(globalRotation().z), glm::vec3(0, 0, 1));
		return rot;
	}
	
	glm::mat4 Transform::scaleMatrix() const
	{
		return glm::scale(glm::mat4(1), globalScale());
	}
	
	glm::mat4 Transform::modelMatrix() const
	{
		return positionMatrix() * rotationMatrix() * scaleMatrix();
	}
	
	glm::mat4 Transform::localPositionMatrix() const
	{
		return glm::translate(glm::mat4(1), position);
	}
	
	glm::mat4 Transform::localRotationMatrix() const
	{
		glm::mat4 rot;
		rot = glm::rotate(rot, glm::radians(rotation.x), glm::vec3(1, 0, 0));
		rot = glm::rotate(rot, glm::radians(rotation.y), glm::vec3(0, 1, 0));
		rot = glm::rotate(rot, glm::radians(rotation.z), glm::vec3(0, 0, 1));
		return rot;
	}
	
	glm::mat4 Transform::localScaleMatrix() const
	{
		return glm::scale(glm::mat4(1), size);
	}
	
	glm::vec3 Transform::globalPosition() const
	{
		if (parent == nullptr)
			return position;
		else
			return position + parent->globalPosition();
	}
	
	glm::vec3 Transform::globalRotation() const
	{
		if (parent == nullptr)
			return rotation;
		else
			return rotation + parent->globalRotation();
	}
	
	glm::vec3 Transform::globalScale() const
	{
		if (parent == nullptr)
			return size;
		else
			return size * parent->globalScale();
	}
	
	void Transform::set_parent(Transform *p)
	{
		parent = p;
		p->m_children.push_back(this);
	}
	
	void Transform::set_parent(Entity *p)
	{
		parent = &(p->transform);
		p->transform.m_children.push_back(this);
	}
} // engine
