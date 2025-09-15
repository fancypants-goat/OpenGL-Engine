//
// Created by michiel on 8/16/25.
//

#include <engine/transform.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <engine/entity.h>
#include <iostream>

#include "engine/math/math.h"

namespace engine {
	Transform::Transform(math::vec3 position, math::vec3 rotation, math::vec3 size)
			: position(position), rotation(rotation), size(size)
	{
	}
	
	void Transform::translate(const math::vec3& offset)
	{
		position += offset;
	}
	
	void Transform::translate(const float x, const float y, const float z)
	{
		position += math::vec3(x, y, z);
	}
	
	void Transform::translate(float scale, math::vec3 axis)
	{
		position += axis * scale;
	}
	
	void Transform::teleport(math::vec3 offset)
	{
		position = offset;
	}

	void Transform::teleport(float x, float y, float z)
	{
		position = math::vec3(x, y, z);
	}
	
	void Transform::rotate(math::vec3 rot)
	{
		rotation += rot;
	}
	
	void Transform::rotate(float x, float y, float z)
	{
		rotation += math::vec3(x, y, z);
	}
	
	void Transform::rotateTo(math::vec3 rot)
	{
		rotation = rot;
	}
	
	void Transform::rotateTo(float x, float y, float z)
	{
		rotation = math::vec3(x, y, z);
	}
	
	void Transform::rotateAxis(float degrees, math::vec3 axis)
	{
		rotation += axis.normalized() * degrees;
	}
	
	void Transform::rotateToAxis(float degrees, math::vec3 axis)
	{
		rotation = axis.normalized() * degrees;
	}
	
	void Transform::scale(math::vec3 scale)
	{
		size = scale;
	}
	
	void Transform::scale(float x, float y, float z)
	{
		size = math::vec3(x, y, z);
	}
	
	void Transform::scale(float scale)
	{
		size = math::vec3(scale);
	}
	
	void Transform::scaleBy(math::vec3 scale)
	{
		size *= scale;
	}
	
	void Transform::scaleBy(float x, float y, float z)
	{
		size *= math::vec3(x, y, z);
	}
	
	void Transform::scaleBy(float scale)
	{
		size *= math::vec3(scale);
	}
	
	
	glm::mat4 Transform::positionMatrix() const
	{
		return glm::translate(glm::mat4(1), globalPosition().toGLM());
	}
	
	glm::mat4 Transform::rotationMatrix() const
	{
		glm::mat4 rot (1);
		rot = glm::rotate(rot, math::radians(globalRotation().x), math::vec3(1, 0, 0).toGLM());
		rot = glm::rotate(rot, math::radians(globalRotation().y), math::vec3(0, 1, 0).toGLM());
		rot = glm::rotate(rot, math::radians(globalRotation().z), math::vec3(0, 0, 1).toGLM());
		return rot;
	}
	
	glm::mat4 Transform::scaleMatrix() const
	{
		return glm::scale(glm::mat4(1), (globalSize() / 2.f).toGLM());
	}
	
	glm::mat4 Transform::modelMatrix() const
	{
		return positionMatrix() * rotationMatrix() * scaleMatrix();
	}
	
	glm::mat4 Transform::localPositionMatrix() const
	{
		return glm::translate(glm::mat4(1), position.toGLM());
	}
	
	glm::mat4 Transform::localRotationMatrix() const
	{
		glm::mat4 rot;
		rot = glm::rotate(rot, math::radians(rotation.x), math::vec3(1, 0, 0).toGLM());
		rot = glm::rotate(rot, math::radians(rotation.y), math::vec3(0, 1, 0).toGLM());
		rot = glm::rotate(rot, math::radians(rotation.z), math::vec3(0, 0, 1).toGLM());
		return rot;
	}
	
	glm::mat4 Transform::localScaleMatrix() const
	{
		return glm::scale(glm::mat4(1), (size / 2.f).toGLM());
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
	
	math::vec3 Transform::globalPosition() const
	{
		return parent == nullptr? position : position + parent->globalPosition();
	}
	
	math::vec3 Transform::globalRotation() const
	{
		return parent == nullptr? rotation : rotation + parent->globalRotation();
	}
	
	math::vec3 Transform::globalSize() const
	{
		return parent == nullptr? size : size * parent->globalSize();
	}
} // engine
