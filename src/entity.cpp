//
// Created by michiel on 8/23/25.
//

#include <engine/entity.h>

#include <iostream>
#include <engine/mesh_renderer.h>

namespace engine {
	Entity::Entity(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
			: transform(position, rotation, scale), renderer(nullptr)
	{
		transform.entity = this;
	}
	
	Entity::Entity(Transform transform)
			: transform(transform), renderer(nullptr)
	{
		this->transform.entity = this;
	}
	
	void Entity::setRenderer(MeshRenderer *newRenderer)
	{
		renderer = newRenderer;
		newRenderer->addEntitySilent(this);
	}
	
	void Entity::update()
	{
		for (auto &component : m_components)
		{
			component.update();
		}
		
		for (auto &child : transform.m_children)
		{
			child->entity->update();
		}
	}
}