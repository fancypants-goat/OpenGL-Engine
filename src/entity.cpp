//
// Created by michiel on 8/23/25.
//

#include <engine/entity.h>

#include <iostream>
#include <engine/mesh_renderer.h>

namespace engine {
	Entity::Entity(math::vec3 position, math::vec3 rotation, math::vec3 scale)
			: transform(position, rotation, scale), name("")
	{
		transform.entity = this;
	}
	
	Entity::Entity(Transform transform)
			: transform(transform), name()
	{
		this->transform.entity = this;
	}
	
	void Entity::setRenderer(MeshRenderer *newRenderer)
	{
		renderer = newRenderer;
		newRenderer->addEntitySilent(this);
	}
	
	void Entity::update(GLFWwindow *window) const
	{
		if (!isActive) return;
		
		for (auto &component : m_components)
		{
			component->update(window);
		}
		
		for (auto &child : transform.m_children)
		{
			child->entity->update(window);
		}
	}
}